#ifndef VG_SATURN_PROFILE_H
#define VG_SATURN_PROFILE_H

#include <stdint.h>

#ifndef VG_SATURN_PROFILE
#define VG_SATURN_PROFILE 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if VG_SATURN_PROFILE
uint16_t vg_saturn_profile_now(void);
uint32_t vg_saturn_profile_elapsed(uint16_t start);
void vg_saturn_profile_init(void);
void vg_saturn_profile_draw_scene_begin(void);
void vg_saturn_profile_draw_scene_end(void);
void vg_saturn_profile_set_render_counts(uint32_t requested, uint32_t visible);
void vg_saturn_profile_add_ticks(uint32_t bucket, uint32_t ticks);
void vg_saturn_profile_count_font_glyph(void);
void vg_saturn_profile_count_hud_sprite(void);
void vg_saturn_profile_backend_ready(uint64_t frame, uint32_t cmdts,
                                     uint32_t quads_in, uint32_t quads_drawn,
                                     uint32_t quads_visible,
                                     uint32_t upload_count,
                                     uint32_t upload_bytes,
                                     uint32_t cache_hits,
                                     uint32_t cache_misses,
                                     uint32_t cache_evictions);
void vg_saturn_profile_vdp1_wait_add(uint32_t ticks);
void vg_saturn_profile_vblank_wait_add(uint32_t ticks);

enum {
    VG_SATURN_PROFILE_BUCKET_ZBUFFER = 0,
    VG_SATURN_PROFILE_BUCKET_GL_COMPAT = 1
};
#else
static inline uint16_t vg_saturn_profile_now(void) { return 0; }
static inline uint32_t vg_saturn_profile_elapsed(uint16_t start)
{
    (void)start;
    return 0;
}
static inline void vg_saturn_profile_init(void) {}
static inline void vg_saturn_profile_draw_scene_begin(void) {}
static inline void vg_saturn_profile_draw_scene_end(void) {}
static inline void vg_saturn_profile_set_render_counts(uint32_t requested,
                                                       uint32_t visible)
{
    (void)requested;
    (void)visible;
}
static inline void vg_saturn_profile_add_ticks(uint32_t bucket, uint32_t ticks)
{
    (void)bucket;
    (void)ticks;
}
static inline void vg_saturn_profile_count_font_glyph(void) {}
static inline void vg_saturn_profile_count_hud_sprite(void) {}
static inline void vg_saturn_profile_backend_ready(uint64_t frame,
                                                   uint32_t cmdts,
                                                   uint32_t quads_in,
                                                   uint32_t quads_drawn,
                                                   uint32_t quads_visible,
                                                   uint32_t upload_count,
                                                   uint32_t upload_bytes,
                                                   uint32_t cache_hits,
                                                   uint32_t cache_misses,
                                                   uint32_t cache_evictions)
{
    (void)frame;
    (void)cmdts;
    (void)quads_in;
    (void)quads_drawn;
    (void)quads_visible;
    (void)upload_count;
    (void)upload_bytes;
    (void)cache_hits;
    (void)cache_misses;
    (void)cache_evictions;
}
static inline void vg_saturn_profile_vdp1_wait_add(uint32_t ticks)
{
    (void)ticks;
}
static inline void vg_saturn_profile_vblank_wait_add(uint32_t ticks)
{
    (void)ticks;
}

enum {
    VG_SATURN_PROFILE_BUCKET_ZBUFFER = 0,
    VG_SATURN_PROFILE_BUCKET_GL_COMPAT = 1
};
#endif

#ifdef __cplusplus
}

#if VG_SATURN_PROFILE
struct VgSaturnProfileScope {
    uint32_t bucket;
    uint16_t start;

    explicit VgSaturnProfileScope(uint32_t profile_bucket)
        : bucket(profile_bucket), start(vg_saturn_profile_now())
    {
    }

    ~VgSaturnProfileScope()
    {
        vg_saturn_profile_add_ticks(bucket, vg_saturn_profile_elapsed(start));
    }
};

#define VG_SATURN_PROFILE_CONCAT_INNER(a, b) a##b
#define VG_SATURN_PROFILE_CONCAT(a, b) VG_SATURN_PROFILE_CONCAT_INNER(a, b)
#define VG_SATURN_PROFILE_SCOPE(bucket) \
    VgSaturnProfileScope VG_SATURN_PROFILE_CONCAT(vg_saturn_profile_scope_, __LINE__)(bucket)
#else
#define VG_SATURN_PROFILE_SCOPE(bucket) ((void)0)
#endif

#endif

#define VG_SATURN_PROFILE_COUNT_FONT_GLYPH() vg_saturn_profile_count_font_glyph()
#define VG_SATURN_PROFILE_COUNT_HUD_SPRITE() vg_saturn_profile_count_hud_sprite()

#endif
