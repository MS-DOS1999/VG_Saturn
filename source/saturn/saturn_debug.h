#ifndef VG_SATURN_DEBUG_H
#define VG_SATURN_DEBUG_H

#include <stdint.h>

#ifndef VG_SATURN_DEBUG_LOG
#define VG_SATURN_DEBUG_LOG 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !VG_SATURN_DEBUG_LOG && !defined(VG_SATURN_DEBUG_IMPLEMENTATION)
#define vg_saturn_debug_init() ((void)0)
#define vg_saturn_debug_puts(text) ((void)0)
#define vg_saturn_debug_stage(id, name) ((void)0)
#define vg_saturn_debug_pass(name) ((void)0)
#define vg_saturn_debug_frame(frame, cmdts, uploads, upload_bytes, cache_slots) ((void)0)
#define vg_saturn_debug_vdp1(frame, quads_in, quads_drawn, quads_skipped, quads_scaled, quads_distorted) ((void)0)
#define vg_saturn_debug_vdp1_detail(frame, skip_alpha, skip_texture, skip_bounds, skip_upload, skip_cmdt, sample_x, sample_y, sample_w, sample_h, sample_sw, sample_sh) ((void)0)
#define vg_saturn_debug_vdp1_regs(frame, edsr, lopr, copr, modr, tvmr, ptmr) ((void)0)
#define vg_saturn_debug_vdp2_regs(frame, tvmd, bgon, spctl, prisa, prisb, prisc, prisd) ((void)0)
#else
void vg_saturn_debug_init(void);
void vg_saturn_debug_puts(const char *text);
void vg_saturn_debug_stage(uint32_t id, const char *name);
void vg_saturn_debug_pass(const char *name);
void vg_saturn_debug_frame(uint64_t frame, uint32_t cmdts, uint32_t uploads,
                           uint32_t upload_bytes, uint32_t cache_slots);
void vg_saturn_debug_vdp1(uint64_t frame, uint32_t quads_in, uint32_t quads_drawn,
                          uint32_t quads_skipped, uint32_t quads_scaled,
                          uint32_t quads_distorted);
void vg_saturn_debug_vdp1_detail(uint64_t frame,
                                 uint32_t skip_alpha,
                                 uint32_t skip_texture,
                                 uint32_t skip_bounds,
                                 uint32_t skip_upload,
                                 uint32_t skip_cmdt,
                                 int32_t sample_x,
                                 int32_t sample_y,
                                 int32_t sample_w,
                                 int32_t sample_h,
                                 uint32_t sample_sw,
                                 uint32_t sample_sh);
void vg_saturn_debug_vdp1_regs(uint64_t frame,
                               uint32_t edsr,
                               uint32_t lopr,
                               uint32_t copr,
                               uint32_t modr,
                               uint32_t tvmr,
                               uint32_t ptmr);
void vg_saturn_debug_vdp2_regs(uint64_t frame,
                               uint32_t tvmd,
                               uint32_t bgon,
                               uint32_t spctl,
                               uint32_t prisa,
                               uint32_t prisb,
                               uint32_t prisc,
                               uint32_t prisd);
#endif

#ifdef __cplusplus
}
#endif

#endif
