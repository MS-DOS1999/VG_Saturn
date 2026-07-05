#include <stdio.h>
#include <string.h>

extern "C" unsigned char __vg_lowram_bss_start;
extern "C" unsigned char __vg_lowram_bss_end;

static bool g_lowram_cleared;

extern "C" void
vg_saturn_lowram_clear(void)
{
    if (g_lowram_cleared) {
        return;
    }

    unsigned char *start = &__vg_lowram_bss_start;
    unsigned char *end = &__vg_lowram_bss_end;
    if (end > start) {
        memset(start, 0, (size_t)(end - start));
    }

    g_lowram_cleared = true;
}

void
set_system_ram(void)
{
    vg_saturn_lowram_clear();
}

unsigned long
get_system_ram(void)
{
    return 0x000FC000UL + 0x00100000UL;
}

unsigned long
get_free_ram(void)
{
    return 0;
}

void
print_ram_stats(void)
{
    printf("Saturn RAM: HIRAM 1008 KiB, LOWRAM 1024 KiB, cart RAM optional\n");
}
