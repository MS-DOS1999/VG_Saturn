#include "kos.h"

#include "saturn_platform.h"

#include <string.h>

uint64 timer_ms_gettime64(void)
{
    return vg_saturn_millis_get();
}

maple_device_t *maple_enum_dev(int port, int unit)
{
    (void)port;
    (void)unit;
    return nullptr;
}

void vmu_pkg_build(vmu_pkg_t *pkg, uint8 **out, int *out_size)
{
    (void)pkg;
    *out_size = 0;
    *out = nullptr;
}

void vmu_pkg_parse(uint8 *in, vmu_pkg_t *pkg)
{
    if (pkg == nullptr) {
        return;
    }
    pkg->data = in;
    pkg->data_len = 500;
}

int vmufs_free_blocks(maple_device_t *dev)
{
    (void)dev;
    return 0x7FFF;
}

file_t fs_open(const char *path, int mode)
{
    (void)path;
    (void)mode;
    return FILEHND_INVALID;
}

int fs_total(file_t f)
{
    (void)f;
    return 0;
}

void fs_close(file_t f)
{
    (void)f;
}

void vmu_set_icon(const char *icon)
{
    (void)icon;
}
