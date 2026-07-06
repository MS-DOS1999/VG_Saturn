#include "saturn_profile.h"

#include <stdio.h>
#include <string.h>
#include <yaul.h>

#if VG_SATURN_PROFILE

static constexpr uint32_t kTicksPerMs = CPU_FRT_NTSC_320_128_COUNT_1MS;

struct SaturnProfileFrame {
    uint16_t frame_start;
    uint16_t draw_scene_start;
    uint64_t frame_number;
    uint32_t total_ticks;
    uint32_t cpu_before_vdp1_ticks;
    uint32_t vdp1_wait_ticks;
    uint32_t vblank_wait_ticks;
    uint32_t zbuffer_ticks;
    uint32_t draw_scene_ticks;
    uint32_t gl_compat_ticks;
    uint32_t cmdts;
    uint32_t quads_in;
    uint32_t quads_drawn;
    uint32_t quads_visible;
    uint32_t sprites_requested;
    uint32_t sprites_visible;
    uint32_t upload_count;
    uint32_t upload_bytes;
    uint32_t cache_hits;
    uint32_t cache_misses;
    uint32_t cache_evictions;
    uint32_t font_glyphs;
    uint32_t hud_sprites;
};

static SaturnProfileFrame g_profile;
static bool g_profile_inited;

static uint32_t
ticks_to_us(uint32_t ticks)
{
    if (kTicksPerMs == 0) {
        return ticks;
    }
    return (ticks * 1000U) / kTicksPerMs;
}

extern "C" uint16_t
vg_saturn_profile_now(void)
{
    return cpu_frt_count_get();
}

extern "C" uint32_t
vg_saturn_profile_elapsed(uint16_t start)
{
    const uint16_t end = cpu_frt_count_get();
    return (uint16_t)(end - start);
}

extern "C" void
vg_saturn_profile_init(void)
{
    if (g_profile_inited) {
        return;
    }
    g_profile_inited = true;
    cpu_frt_init(CPU_FRT_CLOCK_DIV_128);
    cpu_frt_count_set(0);
    memset(&g_profile, 0, sizeof(g_profile));
}

extern "C" void
vg_saturn_profile_draw_scene_begin(void)
{
    vg_saturn_profile_init();
    memset(&g_profile, 0, sizeof(g_profile));
    g_profile.frame_start = vg_saturn_profile_now();
    g_profile.draw_scene_start = g_profile.frame_start;
}

extern "C" void
vg_saturn_profile_draw_scene_end(void)
{
    g_profile.draw_scene_ticks =
        vg_saturn_profile_elapsed(g_profile.draw_scene_start);
    g_profile.total_ticks = vg_saturn_profile_elapsed(g_profile.frame_start);

    if ((g_profile.frame_number % 60ULL) != 0ULL) {
        return;
    }

    dbgio_printf("[PROF] f=%lu total=%luus cpu=%luus vdp1w=%luus vblw=%luus "
                 "cmd=%lu q=%lu drawn=%lu spr=%lu/%lu up=%lu/%luB "
                 "hit=%lu miss=%lu ev=%lu glyph=%lu hud=%lu "
                 "z=%luus draw=%luus gl=%luus\n",
                 (uint32_t)g_profile.frame_number,
                 ticks_to_us(g_profile.total_ticks),
                 ticks_to_us(g_profile.cpu_before_vdp1_ticks),
                 ticks_to_us(g_profile.vdp1_wait_ticks),
                 ticks_to_us(g_profile.vblank_wait_ticks),
                 g_profile.cmdts,
                 g_profile.quads_in,
                 g_profile.quads_drawn,
                 g_profile.sprites_visible,
                 g_profile.sprites_requested,
                 g_profile.upload_count,
                 g_profile.upload_bytes,
                 g_profile.cache_hits,
                 g_profile.cache_misses,
                 g_profile.cache_evictions,
                 g_profile.font_glyphs,
                 g_profile.hud_sprites,
                 ticks_to_us(g_profile.zbuffer_ticks),
                 ticks_to_us(g_profile.draw_scene_ticks),
                 ticks_to_us(g_profile.gl_compat_ticks));
    dbgio_flush();
}

extern "C" void
vg_saturn_profile_set_render_counts(uint32_t requested, uint32_t visible)
{
    g_profile.sprites_requested = requested;
    g_profile.sprites_visible = visible;
}

extern "C" void
vg_saturn_profile_add_ticks(uint32_t bucket, uint32_t ticks)
{
    switch (bucket) {
    case VG_SATURN_PROFILE_BUCKET_ZBUFFER:
        g_profile.zbuffer_ticks += ticks;
        break;
    case VG_SATURN_PROFILE_BUCKET_GL_COMPAT:
        g_profile.gl_compat_ticks += ticks;
        break;
    default:
        break;
    }
}

extern "C" void
vg_saturn_profile_count_font_glyph(void)
{
    g_profile.font_glyphs++;
}

extern "C" void
vg_saturn_profile_count_hud_sprite(void)
{
    g_profile.hud_sprites++;
}

extern "C" void
vg_saturn_profile_backend_ready(uint64_t frame, uint32_t cmdts,
                                uint32_t quads_in, uint32_t quads_drawn,
                                uint32_t quads_visible,
                                uint32_t upload_count,
                                uint32_t upload_bytes,
                                uint32_t cache_hits,
                                uint32_t cache_misses,
                                uint32_t cache_evictions)
{
    g_profile.frame_number = frame;
    g_profile.cpu_before_vdp1_ticks =
        vg_saturn_profile_elapsed(g_profile.frame_start);
    g_profile.cmdts = cmdts;
    g_profile.quads_in = quads_in;
    g_profile.quads_drawn = quads_drawn;
    g_profile.quads_visible = quads_visible;
    g_profile.upload_count = upload_count;
    g_profile.upload_bytes = upload_bytes;
    g_profile.cache_hits = cache_hits;
    g_profile.cache_misses = cache_misses;
    g_profile.cache_evictions = cache_evictions;
}

extern "C" void
vg_saturn_profile_vdp1_wait_add(uint32_t ticks)
{
    g_profile.vdp1_wait_ticks += ticks;
}

extern "C" void
vg_saturn_profile_vblank_wait_add(uint32_t ticks)
{
    g_profile.vblank_wait_ticks += ticks;
}

#else

extern "C" void vg_saturn_profile_cpp_anchor(void) {}

#endif
