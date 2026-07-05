#ifndef VG_SATURN_DEBUG_H
#define VG_SATURN_DEBUG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
