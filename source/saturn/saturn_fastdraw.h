#ifndef VG_SATURN_FASTDRAW_H
#define VG_SATURN_FASTDRAW_H

#include "saturn_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

void vg_saturn_draw_sprite_fast(GLuint texture, float x, float y,
                                float w, float h, float u0, float v0,
                                float u1, float v1, float r, float g,
                                float b, float a);
void vg_saturn_draw_hud_sprite_fast(GLuint texture, float x, float y,
                                    float w, float h, float u0, float v0,
                                    float u1, float v1, float r, float g,
                                    float b, float a);
void vg_saturn_draw_font_glyph_fast(GLuint texture, float x, float y,
                                    float w, float h, float u0, float v0,
                                    float u1, float v1, float r, float g,
                                    float b, float a);
void vg_saturn_draw_solid_rect_fast(float x, float y, float w, float h,
                                    float r, float g, float b, float a);

#ifdef __cplusplus
}
#endif

#endif
