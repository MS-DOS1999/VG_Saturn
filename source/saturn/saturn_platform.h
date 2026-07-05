#ifndef VG_SATURN_PLATFORM_H
#define VG_SATURN_PLATFORM_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "gl_dc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VG_SATURN_SCREEN_W 320
#define VG_SATURN_SCREEN_H 240

typedef struct vg_saturn_vertex {
    float x;
    float y;
    float u;
    float v;
} vg_saturn_vertex_t;

void vg_saturn_init(void);
void vg_saturn_frame_begin(void);
void vg_saturn_frame_end(void);
uint64_t vg_saturn_millis_get(void);
void vg_saturn_lowram_clear(void);
void vg_saturn_cart_object_pool_reset(void);
void *vg_saturn_cart_object_alloc(size_t size, size_t align);
size_t vg_saturn_cart_object_pool_size(void);
size_t vg_saturn_cart_object_pool_used(void);
bool vg_saturn_cd_read_file(const char *path, void **out_data, uint32_t *out_size);
void vg_saturn_cd_free_file(void *data);

void vg_saturn_input_update(void);
uint16_t vg_saturn_input_pressed(int port);
uint16_t vg_saturn_input_held(int port);

GLuint vg_saturn_texture_create(GLsizei width, GLsizei height, const void *argb1555);
void vg_saturn_texture_destroy(GLuint texture);
void vg_saturn_texture_cache_reset(void);
void vg_saturn_texture_set_source_path(GLuint texture, const char *path);
void vg_saturn_texture_replace(GLuint texture, GLsizei width, GLsizei height,
                               const void *data, uint32_t data_size);
void vg_saturn_draw_solid_quad(const vg_saturn_vertex_t *vertices,
                               float r, float g, float b, float a);
void vg_saturn_draw_textured_quad(GLuint texture, const vg_saturn_vertex_t *vertices,
                                  float r, float g, float b, float a);
void vg_saturn_draw_line(float x0, float y0, float x1, float y1,
                         float r, float g, float b, float a);

#ifdef __cplusplus
}
#endif

#endif
