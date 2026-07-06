#include "saturn_fastdraw.h"

static void
quad_set(vg_saturn_vertex_t *vertices, float x, float y, float w, float h,
         float u0, float v0, float u1, float v1)
{
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].u = u0;
    vertices[0].v = v0;

    vertices[1].x = x + w;
    vertices[1].y = y;
    vertices[1].u = u1;
    vertices[1].v = v0;

    vertices[2].x = x + w;
    vertices[2].y = y + h;
    vertices[2].u = u1;
    vertices[2].v = v1;

    vertices[3].x = x;
    vertices[3].y = y + h;
    vertices[3].u = u0;
    vertices[3].v = v1;
}

extern "C" void
vg_saturn_draw_sprite_fast(GLuint texture, float x, float y, float w, float h,
                           float u0, float v0, float u1, float v1,
                           float r, float g, float b, float a)
{
    vg_saturn_vertex_t vertices[4];
    quad_set(vertices, x, y, w, h, u0, v0, u1, v1);
    vg_saturn_draw_textured_quad(texture, vertices, r, g, b, a);
}

extern "C" void
vg_saturn_draw_hud_sprite_fast(GLuint texture, float x, float y, float w,
                               float h, float u0, float v0, float u1,
                               float v1, float r, float g, float b, float a)
{
    vg_saturn_draw_sprite_fast(texture, x, y, w, h, u0, v0, u1, v1,
                               r, g, b, a);
}

extern "C" void
vg_saturn_draw_font_glyph_fast(GLuint texture, float x, float y, float w,
                               float h, float u0, float v0, float u1,
                               float v1, float r, float g, float b, float a)
{
    vg_saturn_draw_sprite_fast(texture, x, y, w, h, u0, v0, u1, v1,
                               r, g, b, a);
}

extern "C" void
vg_saturn_draw_solid_rect_fast(float x, float y, float w, float h,
                               float r, float g, float b, float a)
{
    vg_saturn_vertex_t vertices[4];
    quad_set(vertices, x, y, w, h, 0.0f, 0.0f, 1.0f, 1.0f);
    vg_saturn_draw_solid_quad(vertices, r, g, b, a);
}
