#include "saturn_debug.h"

#include <stddef.h>

#define SCSP_MIDI_STATUS (*(volatile uint16_t *)0x25B00404)
#define SCSP_MIDI_OUT    (*(volatile uint16_t *)0x25B00406)
#define SCSP_MIDI_MOFULL 0x1000

static void
midi_putc(char c)
{
    uint32_t timeout = 100000;
    while ((SCSP_MIDI_STATUS & SCSP_MIDI_MOFULL) != 0) {
        if (--timeout == 0) {
            return;
        }
    }
    SCSP_MIDI_OUT = (uint16_t)(uint8_t)c;
}

static char *
append_char(char *dst, char *end, char c)
{
    if (dst < end) {
        *dst++ = c;
    }
    return dst;
}

static char *
append_text(char *dst, char *end, const char *text)
{
    if (text == NULL) {
        return dst;
    }
    while (*text != '\0') {
        dst = append_char(dst, end, *text++);
    }
    return dst;
}

static char *
append_u32(char *dst, char *end, uint32_t value)
{
    char tmp[10];
    uint32_t count = 0;
    do {
        tmp[count++] = (char)('0' + (value % 10));
        value /= 10;
    } while ((value != 0) && (count < sizeof(tmp)));

    while (count > 0) {
        dst = append_char(dst, end, tmp[--count]);
    }
    return dst;
}

static char *
append_i32(char *dst, char *end, int32_t value)
{
    if (value < 0) {
        dst = append_char(dst, end, '-');
        return append_u32(dst, end, (uint32_t)(-value));
    }
    return append_u32(dst, end, (uint32_t)value);
}

static char *
append_u64(char *dst, char *end, uint64_t value)
{
    char tmp[20];
    uint32_t count = 0;
    do {
        tmp[count++] = (char)('0' + (value % 10));
        value /= 10;
    } while ((value != 0) && (count < sizeof(tmp)));

    while (count > 0) {
        dst = append_char(dst, end, tmp[--count]);
    }
    return dst;
}

extern "C" void
vg_saturn_debug_init(void)
{
    vg_saturn_debug_puts("[BOOT] saturn_debug_init\n");
}

extern "C" void
vg_saturn_debug_puts(const char *text)
{
    if (text == NULL) {
        return;
    }
    while (*text != '\0') {
        if (*text == '\n') {
            midi_putc('\r');
        }
        midi_putc(*text++);
    }
}

extern "C" void
vg_saturn_debug_stage(uint32_t id, const char *name)
{
    char buffer[128];
    char *out = buffer;
    char *end = buffer + sizeof(buffer) - 1;

    out = append_text(out, end, "[CHECKPOINT] id=");
    out = append_u32(out, end, id);
    out = append_text(out, end, " name=");
    out = append_text(out, end, name);
    out = append_char(out, end, '\n');
    *out = '\0';
    vg_saturn_debug_puts(buffer);
}

extern "C" void
vg_saturn_debug_vdp1_detail(uint64_t frame,
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
                            uint32_t sample_sh)
{
    char buffer[224];
    char *out = buffer;
    char *end = buffer + sizeof(buffer) - 1;

    out = append_text(out, end, "[VDP1D] frame=");
    out = append_u64(out, end, frame);
    out = append_text(out, end, " alpha=");
    out = append_u32(out, end, skip_alpha);
    out = append_text(out, end, " tex=");
    out = append_u32(out, end, skip_texture);
    out = append_text(out, end, " bounds=");
    out = append_u32(out, end, skip_bounds);
    out = append_text(out, end, " upload=");
    out = append_u32(out, end, skip_upload);
    out = append_text(out, end, " cmdt=");
    out = append_u32(out, end, skip_cmdt);
    out = append_text(out, end, " xywh=");
    out = append_i32(out, end, sample_x);
    out = append_char(out, end, ',');
    out = append_i32(out, end, sample_y);
    out = append_char(out, end, ',');
    out = append_i32(out, end, sample_w);
    out = append_char(out, end, ',');
    out = append_i32(out, end, sample_h);
    out = append_text(out, end, " src=");
    out = append_u32(out, end, sample_sw);
    out = append_char(out, end, 'x');
    out = append_u32(out, end, sample_sh);
    out = append_char(out, end, '\n');
    *out = '\0';
    vg_saturn_debug_puts(buffer);
}

extern "C" void
vg_saturn_debug_vdp1_regs(uint64_t frame,
                          uint32_t edsr,
                          uint32_t lopr,
                          uint32_t copr,
                          uint32_t modr,
                          uint32_t tvmr,
                          uint32_t ptmr)
{
    char buffer[192];
    char *out = buffer;
    char *end = buffer + sizeof(buffer) - 1;

    out = append_text(out, end, "[VDP1R] frame=");
    out = append_u64(out, end, frame);
    out = append_text(out, end, " edsr=");
    out = append_u32(out, end, edsr);
    out = append_text(out, end, " lopr=");
    out = append_u32(out, end, lopr);
    out = append_text(out, end, " copr=");
    out = append_u32(out, end, copr);
    out = append_text(out, end, " modr=");
    out = append_u32(out, end, modr);
    out = append_text(out, end, " tvmr=");
    out = append_u32(out, end, tvmr);
    out = append_text(out, end, " ptmr=");
    out = append_u32(out, end, ptmr);
    out = append_char(out, end, '\n');
    *out = '\0';
    vg_saturn_debug_puts(buffer);
}

extern "C" void
vg_saturn_debug_vdp2_regs(uint64_t frame,
                          uint32_t tvmd,
                          uint32_t bgon,
                          uint32_t spctl,
                          uint32_t prisa,
                          uint32_t prisb,
                          uint32_t prisc,
                          uint32_t prisd)
{
    char buffer[224];
    char *out = buffer;
    char *end = buffer + sizeof(buffer) - 1;

    out = append_text(out, end, "[VDP2R] frame=");
    out = append_u64(out, end, frame);
    out = append_text(out, end, " tvmd=");
    out = append_u32(out, end, tvmd);
    out = append_text(out, end, " bgon=");
    out = append_u32(out, end, bgon);
    out = append_text(out, end, " spctl=");
    out = append_u32(out, end, spctl);
    out = append_text(out, end, " prisa=");
    out = append_u32(out, end, prisa);
    out = append_text(out, end, " prisb=");
    out = append_u32(out, end, prisb);
    out = append_text(out, end, " prisc=");
    out = append_u32(out, end, prisc);
    out = append_text(out, end, " prisd=");
    out = append_u32(out, end, prisd);
    out = append_char(out, end, '\n');
    *out = '\0';
    vg_saturn_debug_puts(buffer);
}

extern "C" void
vg_saturn_debug_pass(const char *name)
{
    char buffer[128];
    char *out = buffer;
    char *end = buffer + sizeof(buffer) - 1;

    out = append_text(out, end, "[PASS] ");
    out = append_text(out, end, name);
    out = append_char(out, end, '\n');
    *out = '\0';
    vg_saturn_debug_puts(buffer);
}

extern "C" void
vg_saturn_debug_frame(uint64_t frame, uint32_t cmdts, uint32_t uploads,
                      uint32_t upload_bytes, uint32_t cache_slots)
{
    char buffer[160];
    char *out = buffer;
    char *end = buffer + sizeof(buffer) - 1;

    out = append_text(out, end, "[HB] frame=");
    out = append_u64(out, end, frame);
    out = append_text(out, end, " cmdts=");
    out = append_u32(out, end, cmdts);
    out = append_text(out, end, " uploads=");
    out = append_u32(out, end, uploads);
    out = append_text(out, end, " bytes=");
    out = append_u32(out, end, upload_bytes);
    out = append_text(out, end, " cache=");
    out = append_u32(out, end, cache_slots);
    out = append_char(out, end, '\n');
    *out = '\0';
    vg_saturn_debug_puts(buffer);
}

extern "C" void
vg_saturn_debug_vdp1(uint64_t frame, uint32_t quads_in, uint32_t quads_drawn,
                     uint32_t quads_skipped, uint32_t quads_scaled,
                     uint32_t quads_distorted)
{
    char buffer[192];
    char *out = buffer;
    char *end = buffer + sizeof(buffer) - 1;

    out = append_text(out, end, "[VDP1] frame=");
    out = append_u64(out, end, frame);
    out = append_text(out, end, " quads=");
    out = append_u32(out, end, quads_in);
    out = append_text(out, end, " drawn=");
    out = append_u32(out, end, quads_drawn);
    out = append_text(out, end, " skip=");
    out = append_u32(out, end, quads_skipped);
    out = append_text(out, end, " scaled=");
    out = append_u32(out, end, quads_scaled);
    out = append_text(out, end, " distort=");
    out = append_u32(out, end, quads_distorted);
    out = append_char(out, end, '\n');
    *out = '\0';
    vg_saturn_debug_puts(buffer);
}
