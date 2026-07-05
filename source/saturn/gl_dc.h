#ifndef VG_SATURN_GL_DC_H
#define VG_SATURN_GL_DC_H

#include <stdint.h>

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef double GLdouble;
typedef void GLvoid;

#define GL_FALSE 0
#define GL_TRUE 1

#define GL_TEXTURE_2D 0x0DE1
#define GL_PROJECTION 0x1701
#define GL_MODELVIEW 0x1700
#define GL_QUADS 0x0007
#define GL_LINES 0x0001
#define GL_POINTS 0x0000

#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100

#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_UNSIGNED_BYTE 0x1401

#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601

#define GL_BLEND 0x0BE2
#define GL_DEPTH_TEST 0x0B71
#define GL_LIGHTING 0x0B50
#define GL_DITHER 0x0BD0
#define GL_FOG 0x0B60
#define GL_FOG_MODE 0x0B65
#define GL_FOG_DENSITY 0x0B62
#define GL_FOG_START 0x0B63
#define GL_FOG_END 0x0B64
#define GL_FOG_HINT 0x0C54
#define GL_FOG_COLOR 0x0B66
#define GL_FASTEST 0x1101
#define GL_FLAT 0x1D00
#define GL_SMOOTH 0x1D01

#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_ONE 1
#define GL_ONE_MINUS_DST_ALPHA 0x0307
#define GL_SRC_COLOR 0x0300

#define GL_RENDERER 0x1F01
#define GL_VENDOR 0x1F00
#define GL_VERSION 0x1F02
#define GL_EXTENSIONS 0x1F03

#define GL_COMPRESSED_ARGB_1555_VQ_KOS 0xEEE6
#define GL_COMPRESSED_ARGB_1555_VQ_MIPMAP_KOS 0xEEED
#define GL_COMPRESSED_ARGB_1555_VQ_TWID_KOS 0xEEEA
#define GL_COMPRESSED_ARGB_1555_VQ_MIPMAP_TWID_KOS 0xEEF0
#define GL_COMPRESSED_ARGB_4444_VQ_KOS 0xEEE7
#define GL_COMPRESSED_ARGB_4444_VQ_MIPMAP_KOS 0xEEEE
#define GL_COMPRESSED_ARGB_4444_VQ_TWID_KOS 0xEEEB
#define GL_COMPRESSED_ARGB_4444_VQ_MIPMAP_TWID_KOS 0xEEF1
#define GL_COMPRESSED_RGB_565_VQ_KOS 0xEEE4
#define GL_COMPRESSED_RGB_565_VQ_MIPMAP_KOS 0xEEEC
#define GL_COMPRESSED_RGB_565_VQ_TWID_KOS 0xEEE8
#define GL_COMPRESSED_RGB_565_VQ_MIPMAP_TWID_KOS 0xEEEF
#define GL_SATURN_4BPP_CLUT16 0x5A71

#ifdef __cplusplus
extern "C" {
#endif

void glKosInit(void);
void glKosSwapBuffers(void);

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
void glMatrixMode(GLenum mode);
void glLoadIdentity(void);
void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
             GLdouble near_val, GLdouble far_val);
void glPushMatrix(void);
void glPopMatrix(void);
void glTranslatef(GLfloat x, GLfloat y, GLfloat z);
void glScalef(GLfloat x, GLfloat y, GLfloat z);
void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

void glBegin(GLenum mode);
void glEnd(void);
void glTexCoord2f(GLfloat s, GLfloat t);
void glTexCoord2fv(const GLfloat *v);
void glVertex2f(GLfloat x, GLfloat y);
void glVertex2fv(const GLfloat *v);
void glVertex3f(GLfloat x, GLfloat y, GLfloat z);
void glNormal3f(GLfloat x, GLfloat y, GLfloat z);
void glColor3f(GLfloat r, GLfloat g, GLfloat b);
void glColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void glColor4fv(const GLfloat *v);

void glClear(GLbitfield mask);
void glClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void glEnable(GLenum cap);
void glDisable(GLenum cap);
void glBlendFunc(GLenum sfactor, GLenum dfactor);
void glFogi(GLenum pname, GLint param);
void glFogf(GLenum pname, GLfloat param);
void glFogfv(GLenum pname, const GLfloat *params);
void glHint(GLenum target, GLenum mode);
void glShadeModel(GLenum mode);
void glFlush(void);
void glLineWidth(GLfloat width);
void glPointSize(GLfloat size);

void glGenTextures(GLsizei n, GLuint *textures);
void glDeleteTextures(GLsizei n, const GLuint *textures);
void glBindTexture(GLenum target, GLuint texture);
void glTexParameteri(GLenum target, GLenum pname, GLint param);
void glTexImage2D(GLenum target, GLint level, GLint internalformat,
                  GLsizei width, GLsizei height, GLint border, GLenum format,
                  GLenum type, const GLvoid *pixels);
void glCompressedTexImage2DARB(GLenum target, GLint level, GLenum internalformat,
                               GLsizei width, GLsizei height, GLint border,
                               GLsizei imageSize, const GLvoid *data);
const GLubyte *glGetString(GLenum name);

void glSaturnSetTextureSourcePath(const char *path);

#ifdef __cplusplus
}
#endif

#endif
