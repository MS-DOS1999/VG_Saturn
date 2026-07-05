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
