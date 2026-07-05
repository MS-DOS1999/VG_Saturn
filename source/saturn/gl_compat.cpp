#include "gl_dc.h"
#include "saturn_platform.h"

#include <math.h>
#include <string.h>

struct Mat3 {
    float m[9];
};

struct GLVertex {
    float x;
    float y;
    float z;
    float u;
    float v;
};

static Mat3 g_projection;
static Mat3 g_model;
static Mat3 g_projection_stack[16];
static Mat3 g_model_stack[32];
static int g_projection_top;
static int g_model_top;
static GLenum g_matrix_mode = GL_MODELVIEW;
static GLenum g_begin_mode;
static GLVertex g_vertices[8];
static int g_vertex_count;
static float g_current_u;
static float g_current_v;
static float g_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
static GLuint g_bound_texture;
static char g_pending_texture_path[256];
static bool g_frame_open;
static bool g_texture_2d_enabled = true;

static Mat3 *
current_matrix(void)
{
    return (g_matrix_mode == GL_PROJECTION) ? &g_projection : &g_model;
}

static void
mat_identity(Mat3 *mat)
{
    memset(mat->m, 0, sizeof(mat->m));
    mat->m[0] = 1.0f;
    mat->m[4] = 1.0f;
    mat->m[8] = 1.0f;
}

static Mat3
mat_mul(const Mat3 &a, const Mat3 &b)
{
    Mat3 out = {};
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            out.m[(y * 3) + x] =
                (a.m[(y * 3) + 0] * b.m[(0 * 3) + x]) +
                (a.m[(y * 3) + 1] * b.m[(1 * 3) + x]) +
                (a.m[(y * 3) + 2] * b.m[(2 * 3) + x]);
        }
    }
    return out;
}

static void
mat_apply(Mat3 *target, const Mat3 &rhs)
{
    *target = mat_mul(*target, rhs);
}

static void
transform_to_screen(const GLVertex &in, vg_saturn_vertex_t *out)
{
    const float mx = (g_model.m[0] * in.x) + (g_model.m[1] * in.y) + g_model.m[2];
    const float my = (g_model.m[3] * in.x) + (g_model.m[4] * in.y) + g_model.m[5];

    const float nx = (g_projection.m[0] * mx) + (g_projection.m[1] * my) + g_projection.m[2];
    const float ny = (g_projection.m[3] * mx) + (g_projection.m[4] * my) + g_projection.m[5];

    out->x = (nx + 1.0f) * (VG_SATURN_SCREEN_W * 0.5f);
    out->y = (1.0f - ny) * (VG_SATURN_SCREEN_H * 0.5f);
    out->u = in.u;
    out->v = in.v;
}

static void
ensure_frame_open(void)
{
    if (!g_frame_open) {
        vg_saturn_frame_begin();
        g_frame_open = true;
    }
}

static void
emit_quad_if_ready(void)
{
    if ((g_begin_mode != GL_QUADS) || (g_vertex_count < 4)) {
        return;
    }

    vg_saturn_vertex_t out[4];
    for (int i = 0; i < 4; i++) {
        transform_to_screen(g_vertices[i], &out[i]);
    }
    ensure_frame_open();
    if (g_texture_2d_enabled) {
        vg_saturn_draw_textured_quad(g_bound_texture, out, g_color[0],
                                     g_color[1], g_color[2], g_color[3]);
    } else {
        vg_saturn_draw_solid_quad(out, g_color[0], g_color[1], g_color[2],
                                  g_color[3]);
    }
    g_vertex_count = 0;
}

static void
emit_line_if_ready(void)
{
    if ((g_begin_mode != GL_LINES) || (g_vertex_count < 2)) {
        return;
    }

    vg_saturn_vertex_t a;
    vg_saturn_vertex_t b;
    transform_to_screen(g_vertices[0], &a);
    transform_to_screen(g_vertices[1], &b);
    ensure_frame_open();
    vg_saturn_draw_line(a.x, a.y, b.x, b.y, g_color[0], g_color[1], g_color[2],
                        g_color[3]);
    g_vertex_count = 0;
}

extern "C" void
glKosInit(void)
{
    mat_identity(&g_projection);
    mat_identity(&g_model);
    g_frame_open = false;
    vg_saturn_init();
}

extern "C" void
glKosSwapBuffers(void)
{
    ensure_frame_open();
    vg_saturn_frame_end();
    g_frame_open = false;
}

extern "C" void
glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    (void)x;
    (void)y;
    (void)width;
    (void)height;
}

extern "C" void
glMatrixMode(GLenum mode)
{
    g_matrix_mode = mode;
}

extern "C" void
glLoadIdentity(void)
{
    mat_identity(current_matrix());
}

extern "C" void
glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
        GLdouble near_val, GLdouble far_val)
{
    (void)near_val;
    (void)far_val;

    Mat3 ortho = {};
    ortho.m[0] = 2.0f / (float)(right - left);
    ortho.m[2] = -(float)(right + left) / (float)(right - left);
    ortho.m[4] = 2.0f / (float)(top - bottom);
    ortho.m[5] = -(float)(top + bottom) / (float)(top - bottom);
    ortho.m[8] = 1.0f;
    *current_matrix() = ortho;
}

extern "C" void
glPushMatrix(void)
{
    if (g_matrix_mode == GL_PROJECTION) {
        if (g_projection_top < 16) {
            g_projection_stack[g_projection_top++] = g_projection;
        }
    } else if (g_model_top < 32) {
        g_model_stack[g_model_top++] = g_model;
    }
}

extern "C" void
glPopMatrix(void)
{
    if (g_matrix_mode == GL_PROJECTION) {
        if (g_projection_top > 0) {
            g_projection = g_projection_stack[--g_projection_top];
        }
    } else if (g_model_top > 0) {
        g_model = g_model_stack[--g_model_top];
    }
}

extern "C" void
glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    (void)z;
    Mat3 t;
    mat_identity(&t);
    t.m[2] = x;
    t.m[5] = y;
    mat_apply(current_matrix(), t);
}

extern "C" void
glScalef(GLfloat x, GLfloat y, GLfloat z)
{
    (void)z;
    Mat3 s;
    mat_identity(&s);
    s.m[0] = x;
    s.m[4] = y;
    mat_apply(current_matrix(), s);
}

extern "C" void
glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    (void)x;
    (void)y;
    (void)z;

    const float rad = angle * 0.01745329252f;
    const float c = cosf(rad);
    const float s = sinf(rad);
    Mat3 r;
    mat_identity(&r);
    r.m[0] = c;
    r.m[1] = -s;
    r.m[3] = s;
    r.m[4] = c;
    mat_apply(current_matrix(), r);
}

extern "C" void
glBegin(GLenum mode)
{
    g_begin_mode = mode;
    g_vertex_count = 0;
}

extern "C" void
glEnd(void)
{
    emit_quad_if_ready();
    emit_line_if_ready();
    g_begin_mode = 0;
    g_vertex_count = 0;
}

extern "C" void
glTexCoord2f(GLfloat s, GLfloat t)
{
    g_current_u = s;
    g_current_v = t;
}

extern "C" void
glTexCoord2fv(const GLfloat *v)
{
    if (v != nullptr) {
        glTexCoord2f(v[0], v[1]);
    }
}

extern "C" void
glVertex2f(GLfloat x, GLfloat y)
{
    glVertex3f(x, y, 0.0f);
}

extern "C" void
glVertex2fv(const GLfloat *v)
{
    if (v != nullptr) {
        glVertex3f(v[0], v[1], 0.0f);
    }
}

extern "C" void
glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
    if (g_vertex_count >= 8) {
        g_vertex_count = 0;
    }

    GLVertex &v = g_vertices[g_vertex_count++];
    v.x = x;
    v.y = y;
    v.z = z;
    v.u = g_current_u;
    v.v = g_current_v;

    emit_quad_if_ready();
    emit_line_if_ready();
}

extern "C" void glNormal3f(GLfloat x, GLfloat y, GLfloat z) { (void)x; (void)y; (void)z; }

extern "C" void
glColor3f(GLfloat r, GLfloat g, GLfloat b)
{
    glColor4f(r, g, b, g_color[3]);
}

extern "C" void
glColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    g_color[0] = r;
    g_color[1] = g;
    g_color[2] = b;
    g_color[3] = a;
}

extern "C" void
glColor4fv(const GLfloat *v)
{
    if (v != nullptr) {
        glColor4f(v[0], v[1], v[2], v[3]);
    }
}

extern "C" void
glClear(GLbitfield mask)
{
    (void)mask;
    vg_saturn_frame_begin();
    g_frame_open = true;
}

extern "C" void glClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    (void)r; (void)g; (void)b; (void)a;
}

extern "C" void
glEnable(GLenum cap)
{
    if (cap == GL_TEXTURE_2D) {
        g_texture_2d_enabled = true;
    }
}

extern "C" void
glDisable(GLenum cap)
{
    if (cap == GL_TEXTURE_2D) {
        g_texture_2d_enabled = false;
    }
}
extern "C" void glBlendFunc(GLenum sfactor, GLenum dfactor) { (void)sfactor; (void)dfactor; }
extern "C" void glFogi(GLenum pname, GLint param) { (void)pname; (void)param; }
extern "C" void glFogf(GLenum pname, GLfloat param) { (void)pname; (void)param; }
extern "C" void glFogfv(GLenum pname, const GLfloat *params) { (void)pname; (void)params; }
extern "C" void glHint(GLenum target, GLenum mode) { (void)target; (void)mode; }
extern "C" void glShadeModel(GLenum mode) { (void)mode; }
extern "C" void glFlush(void) {}
extern "C" void glLineWidth(GLfloat width) { (void)width; }
extern "C" void glPointSize(GLfloat size) { (void)size; }

extern "C" void
glGenTextures(GLsizei n, GLuint *textures)
{
    for (GLsizei i = 0; i < n; i++) {
        textures[i] = vg_saturn_texture_create(16, 16, nullptr);
    }
}

extern "C" void
glDeleteTextures(GLsizei n, const GLuint *textures)
{
    for (GLsizei i = 0; i < n; i++) {
        vg_saturn_texture_destroy(textures[i]);
    }
}

extern "C" void
glBindTexture(GLenum target, GLuint texture)
{
    (void)target;
    g_bound_texture = texture;
}

extern "C" void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
    (void)target; (void)pname; (void)param;
}

extern "C" void
glTexImage2D(GLenum target, GLint level, GLint internalformat,
             GLsizei width, GLsizei height, GLint border, GLenum format,
             GLenum type, const GLvoid *pixels)
{
    (void)target; (void)level; (void)internalformat; (void)border;
    (void)format; (void)type;
    if (g_pending_texture_path[0] != '\0') {
        vg_saturn_texture_set_source_path(g_bound_texture, g_pending_texture_path);
        g_pending_texture_path[0] = '\0';
    }
    vg_saturn_texture_replace(g_bound_texture, width, height, pixels, 0);
}

extern "C" void
glCompressedTexImage2DARB(GLenum target, GLint level, GLenum internalformat,
                          GLsizei width, GLsizei height, GLint border,
                          GLsizei imageSize, const GLvoid *data)
{
    (void)target; (void)level; (void)internalformat; (void)border; (void)imageSize;
    if (g_pending_texture_path[0] != '\0') {
        vg_saturn_texture_set_source_path(g_bound_texture, g_pending_texture_path);
        g_pending_texture_path[0] = '\0';
    }
    vg_saturn_texture_replace(g_bound_texture, width, height, data,
                              (uint32_t)imageSize);
}

extern "C" const GLubyte *
glGetString(GLenum name)
{
    switch (name) {
    case GL_RENDERER:
        return reinterpret_cast<const GLubyte *>("Saturn VDP1/VDP2");
    case GL_VENDOR:
        return reinterpret_cast<const GLubyte *>("Yaul");
    case GL_VERSION:
        return reinterpret_cast<const GLubyte *>("VG Saturn compat 0.1");
    default:
        return reinterpret_cast<const GLubyte *>("");
    }
}

extern "C" void
glSaturnSetTextureSourcePath(const char *path)
{
    if (path == nullptr) {
        g_pending_texture_path[0] = '\0';
        return;
    }

    strncpy(g_pending_texture_path, path, sizeof(g_pending_texture_path) - 1);
    g_pending_texture_path[sizeof(g_pending_texture_path) - 1] = '\0';
}
