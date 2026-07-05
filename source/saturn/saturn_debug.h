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

#ifdef __cplusplus
}
#endif

#endif
