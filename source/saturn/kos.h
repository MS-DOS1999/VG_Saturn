#ifndef VG_SATURN_KOS_COMPAT_H
#define VG_SATURN_KOS_COMPAT_H

#include <stdint.h>
#include <stddef.h>
#include <fcntl.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int file_t;
#ifndef FILEHND_INVALID
#define FILEHND_INVALID (-1)
#endif

#define MAPLE_FUNC_MEMCARD 0x00000001

typedef struct maple_device_info {
    uint32 functions;
} maple_device_info_t;

typedef struct maple_device {
    int valid;
    maple_device_info_t info;
} maple_device_t;

typedef struct vmu_pkg {
    char desc_long[32];
    char desc_short[16];
    char app_id[16];
    int icon_cnt;
    int icon_anim_speed;
    const void *icon_data;
    uint8 icon_pal[32];
    int eyecatch_type;
    uint16 data_len;
    const uint8 *data;
} vmu_pkg_t;

#define VMUPKG_EC_NONE 0

#ifdef __cplusplus
extern "C" {
#endif

uint64 timer_ms_gettime64(void);
maple_device_t *maple_enum_dev(int port, int unit);
void vmu_pkg_build(vmu_pkg_t *pkg, uint8 **out, int *out_size);
void vmu_pkg_parse(uint8 *in, vmu_pkg_t *pkg);
int vmufs_free_blocks(maple_device_t *dev);
file_t fs_open(const char *path, int mode);
int fs_total(file_t f);
void fs_close(file_t f);
void vmu_set_icon(const char *icon);

#ifdef __cplusplus
}
#endif

#endif
