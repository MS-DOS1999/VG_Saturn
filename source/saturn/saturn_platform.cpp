#include "saturn_platform.h"
#include "saturn_debug.h"
#include "saturn_profile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <yaul.h>

static constexpr uint32_t kMaxCmdts = 2048;
static constexpr uint32_t kMaxTextures = 512;
static constexpr uint32_t kTextureBudget = 0x00054000;
static constexpr uint32_t kClutCount = 512;
static constexpr uint32_t kFrameUploadMax = 384;
static constexpr uint32_t kMaxCacheSlots = 256;
static constexpr uint32_t kCartObjectPoolBytes = 0x00110000;
static constexpr bool kDebugDrawVdp1Marker = false;
static constexpr bool kDebugUseDefaultVdp1Layout = false;

#if VG_SATURN_DEBUG_LOG
#define VG_SATURN_DEBUG_DBGP(...) dbgio_printf(__VA_ARGS__)
#else
#define VG_SATURN_DEBUG_DBGP(...) ((void)0)
#endif

struct SaturnTexture {
    uint16_t width;
    uint16_t height;
    uint32_t data_bytes;
    vdp1_clut_t *clut;
    bool used;
    bool resident;
    bool skipped;
    bool warned;
    int cache_slot;
    char path[192];
};

struct CacheSlot {
    uint8_t *base;
    uint32_t bytes;
    uint32_t capacity;
    uint32_t last_used;
    GLuint texture;
    bool used;
};

struct Vdp1FrameKey {
    GLuint texture;
    uint16_t sx;
    uint16_t sy;
    uint16_t sw;
    uint16_t sh;
};

struct Vdp1FrameSlot {
    Vdp1FrameKey key;
    uint8_t *base;
    uint32_t bytes;
    uint32_t capacity;
    uint16_t slot_w;
    uint16_t slot_h;
    uint32_t last_used_frame;
    bool used;
    bool touched_this_frame;
};

struct OrderedQuadVertex {
    float x;
    float y;
    float u;
    float v;
};

struct SatTextureHeader {
    char magic[4];
    uint16_t width;
    uint16_t height;
    uint32_t data_size;
};

static vdp1_cmdt_list_t *g_cmdt_list;
static vdp1_vram_partitions_t g_vdp1_parts;
static uint32_t g_cmdt_index;
static uint8_t *g_frame_vram_base;
static uint8_t *g_frame_vram_cursor;
static uint8_t *g_frame_vram_end;
static Vdp1FrameSlot g_frame_slots[kFrameUploadMax];
static uint32_t g_frame_slot_count;
static uint32_t g_frame_upload_count;
static uint32_t g_frame_upload_bytes;
static uint32_t g_frame_cache_hits;
static uint32_t g_frame_cache_misses;
static uint32_t g_frame_cache_evictions;
static SaturnTexture g_textures[kMaxTextures];
static CacheSlot g_cache_slots[kMaxCacheSlots];
static uint32_t g_cache_slot_count;
static uint8_t *g_cache_base;
static uint32_t g_cache_size;
static uint32_t g_cache_cursor;
static uint32_t g_cache_tick;
static uint32_t g_next_texture = 1;
static volatile uint64_t g_frame_count;
static smpc_peripheral_digital_t g_digital[2];
static uint8_t *g_cart_object_pool_base;
static uint32_t g_cart_object_pool_size;
static uint32_t g_cart_object_pool_cursor;
static bool g_inited;
static bool g_warned_no_cart;
static bool g_debug_passed_first_frame;
static uint32_t g_debug_last_cmdts;
static uint32_t g_debug_last_uploads;
static uint32_t g_debug_last_upload_bytes;
static uint32_t g_debug_last_quads_in;
static uint32_t g_debug_last_quads_drawn;
static uint32_t g_debug_last_quads_skipped;
static uint32_t g_debug_last_quads_scaled;
static uint32_t g_debug_last_quads_distorted;
static uint32_t g_debug_skip_alpha;
static uint32_t g_debug_skip_texture;
static uint32_t g_debug_skip_bounds;
static uint32_t g_debug_skip_upload;
static uint32_t g_debug_skip_cmdt;
static bool g_debug_sample_valid;
static int32_t g_debug_sample_x;
static int32_t g_debug_sample_y;
static int32_t g_debug_sample_w;
static int32_t g_debug_sample_h;
static uint32_t g_debug_sample_sw;
static uint32_t g_debug_sample_sh;
static uint32_t g_debug_vdp1_edsr;
static uint32_t g_debug_vdp1_lopr;
static uint32_t g_debug_vdp1_copr;
static uint32_t g_debug_vdp1_modr;
static uint32_t g_debug_vdp1_tvmr;
static uint32_t g_debug_vdp1_ptmr;
static uint32_t g_debug_vdp2_tvmd;
static uint32_t g_debug_vdp2_bgon;
static uint32_t g_debug_vdp2_spctl;
static uint32_t g_debug_vdp2_prisa;
static uint32_t g_debug_vdp2_prisb;
static uint32_t g_debug_vdp2_prisc;
static uint32_t g_debug_vdp2_prisd;
static uint32_t g_frame_quads_in;
static uint32_t g_frame_quads_drawn;
static uint32_t g_frame_quads_skipped;
static uint32_t g_frame_quads_scaled;
static uint32_t g_frame_quads_distorted;
static uint32_t g_frame_skip_alpha;
static uint32_t g_frame_skip_texture;
static uint32_t g_frame_skip_bounds;
static uint32_t g_frame_skip_upload;
static uint32_t g_frame_skip_cmdt;
static bool g_frame_sample_valid;
static int32_t g_frame_sample_x;
static int32_t g_frame_sample_y;
static int32_t g_frame_sample_w;
static int32_t g_frame_sample_h;
static uint32_t g_frame_sample_sw;
static uint32_t g_frame_sample_sh;
static uint32_t g_frame_debug_draw_logs;
static bool g_debug_first_texture_cd;
static uint32_t g_debug_texture_cd_count;
static uint32_t g_debug_texture_cd_attempt_count;
static cdfs_filelist_entry_t g_cd_entries[512];
static uint8_t g_cd_sector_buffer[CDFS_SECTOR_SIZE];

static uint8_t g_placeholder_pixels[(16 * 16) / 2];
static uint16_t g_placeholder_palette[16];

static vdp1_cmdt_t *cmdt_next(void);
static void frame_cache_reset_all(void);
static void frame_cache_evict_texture(GLuint texture);
static void debug_draw_log(const char *kind, GLuint input_texture,
                           GLuint final_texture, const SaturnTexture *tex,
                           uint16_t sx, uint16_t sy, uint16_t sw,
                           uint16_t sh);
static bool cd_find_path(const char *path, cdfs_filelist_entry_t *out_entry);
static bool cd_read_entry_to(const cdfs_filelist_entry_t *entry, uint8_t *data,
                             uint32_t capacity, uint32_t *out_size);

static int
char_lower_ascii(int c)
{
    if ((c >= 'A') && (c <= 'Z')) {
        return c - 'A' + 'a';
    }
    return c;
}

static int
char_upper_ascii(int c)
{
    if ((c >= 'a') && (c <= 'z')) {
        return c - 'a' + 'A';
    }
    return c;
}

static bool
cd_name_equal(const char *left, const char *right)
{
    while ((*left != '\0') && (*left != ';') &&
           (*right != '\0') && (*right != ';')) {
        if (char_lower_ascii((unsigned char)*left) !=
            char_lower_ascii((unsigned char)*right)) {
            return false;
        }
        left++;
        right++;
    }

    return ((*left == '\0') || (*left == ';')) &&
           ((*right == '\0') || (*right == ';'));
}

static bool
cd_name_equal_without_dot(const char *entry_name, const char *candidate_name)
{
    char compact[ISO_FILENAME_MAX_LENGTH + 1];
    uint32_t out = 0;

    for (const char *scan = candidate_name;
         (*scan != '\0') && (*scan != ';') && ((out + 1) < sizeof(compact));
         scan++) {
        if (*scan == '.') {
            continue;
        }
        compact[out++] = *scan;
    }
    compact[out] = '\0';

    return cd_name_equal(entry_name, compact);
}

static void
cd_component_iso_name(const char *raw, char *component, size_t component_size)
{
    char base[9];
    char ext[4];
    uint32_t base_count = 0;
    uint32_t ext_count = 0;
    const char *dot = nullptr;

    for (const char *scan = raw; *scan != '\0'; scan++) {
        if (*scan == '.') {
            dot = scan;
        }
    }

    const char *scan = raw;
    while ((*scan != '\0') && (scan != dot) && (base_count < 8)) {
        base[base_count++] = char_upper_ascii((unsigned char)*scan++);
    }
    base[base_count] = '\0';

    if (dot != nullptr) {
        scan = dot + 1;
        while ((*scan != '\0') && (ext_count < 3)) {
            ext[ext_count++] = char_upper_ascii((unsigned char)*scan++);
        }
    }
    ext[ext_count] = '\0';

    if (component_size == 0) {
        return;
    }

    uint32_t out = 0;
    for (uint32_t i = 0; (i < base_count) && ((out + 1) < component_size); i++) {
        component[out++] = base[i];
    }
    if ((ext_count > 0) && ((out + 1) < component_size)) {
        component[out++] = '.';
        for (uint32_t i = 0; (i < ext_count) && ((out + 1) < component_size); i++) {
            component[out++] = ext[i];
        }
    }
    component[out] = '\0';
}

static bool
cd_next_component(const char **cursor, char *component, size_t component_size,
                  bool *has_more)
{
    const char *path = *cursor;
    while ((*path == '/') || (*path == '\\')) {
        path++;
    }

    if (*path == '\0') {
        component[0] = '\0';
        *cursor = path;
        *has_more = false;
        return false;
    }

    char raw_component[128];
    size_t count = 0;
    while ((*path != '\0') && (*path != '/') && (*path != '\\')) {
        if (count + 1 < sizeof(raw_component)) {
            raw_component[count++] = *path;
        }
        path++;
    }
    raw_component[count] = '\0';
    cd_component_iso_name(raw_component, component, component_size);

    const char *next = path;
    while ((*next == '/') || (*next == '\\')) {
        next++;
    }
    *has_more = (*next != '\0');
    *cursor = path;

    return component[0] != '\0';
}

static bool
cd_find_entry(cdfs_filelist_t *filelist, const char *name,
              cdfs_entry_type_t type, cdfs_filelist_entry_t *out_entry)
{
    for (uint32_t i = 0; i < filelist->entries_count; i++) {
        const cdfs_filelist_entry_t *entry = &filelist->entries[i];
        if ((entry->type == type) &&
            (cd_name_equal(entry->name, name) ||
             cd_name_equal_without_dot(entry->name, name))) {
            *out_entry = *entry;
            return true;
        }
    }

    return false;
}

static uint32_t
align_up_u32(uint32_t value, uint32_t align)
{
    if (align == 0) {
        return value;
    }

    const uint32_t mask = align - 1U;
    return (value + mask) & ~mask;
}

static void
debug_draw_log(const char *kind, GLuint input_texture, GLuint final_texture,
               const SaturnTexture *tex, uint16_t sx, uint16_t sy,
               uint16_t sw, uint16_t sh)
{
#if VG_SATURN_DEBUG_LOG
    if (g_debug_passed_first_frame || (g_frame_debug_draw_logs >= 8)) {
        return;
    }
    g_frame_debug_draw_logs++;

    char buffer[256];
    snprintf(buffer, sizeof(buffer),
             "[DRAW] %s in=%lu tex=%lu wh=%lux%lu src=%lu,%lu,%lux%lu path=%s\n",
             (kind != nullptr) ? kind : "?",
             (uint32_t)input_texture,
             (uint32_t)final_texture,
             tex != nullptr ? (uint32_t)tex->width : 0,
             tex != nullptr ? (uint32_t)tex->height : 0,
             (uint32_t)sx, (uint32_t)sy, (uint32_t)sw, (uint32_t)sh,
             (tex != nullptr && tex->path[0] != '\0') ? tex->path : "-");
    vg_saturn_debug_puts(buffer);
#else
    (void)kind;
    (void)input_texture;
    (void)final_texture;
    (void)tex;
    (void)sx;
    (void)sy;
    (void)sw;
    (void)sh;
#endif
}

static void
debug_marker_draw(void)
{
    vdp1_cmdt_t *cmdt = cmdt_next();
    if (cmdt == nullptr) {
        return;
    }

    int16_vec2_t points[4] = {};
    points[0].x = 8;
    points[0].y = 40;
    points[1].x = 40;
    points[1].y = 40;
    points[2].x = 40;
    points[2].y = 8;
    points[3].x = 8;
    points[3].y = 8;

    vdp1_cmdt_polygon_set(cmdt);
    vdp1_cmdt_draw_mode_t draw_mode = {};
    vdp1_cmdt_draw_mode_set(cmdt, draw_mode);
    vdp1_cmdt_color_set(cmdt, RGB1555(1, 31, 0, 31));
    vdp1_cmdt_vtx_set(cmdt, points);
}

static rgb1555_t
rgb1555_from_float(float r, float g, float b)
{
    if (r < 0.0f) r = 0.0f;
    if (g < 0.0f) g = 0.0f;
    if (b < 0.0f) b = 0.0f;
    if (r > 1.0f) r = 1.0f;
    if (g > 1.0f) g = 1.0f;
    if (b > 1.0f) b = 1.0f;

    const uint16_t ri = (uint16_t)(r * 31.0f);
    const uint16_t gi = (uint16_t)(g * 31.0f);
    const uint16_t bi = (uint16_t)(b * 31.0f);
    return RGB1555(1, ri, gi, bi);
}

static uint16_t
align8_u16(uint16_t value)
{
    return (uint16_t)((value + 7U) & ~7U);
}

static float
clampf(float value, float lo, float hi)
{
    if (value < lo) {
        return lo;
    }
    if (value > hi) {
        return hi;
    }
    return value;
}

static int16_t
round_to_i16(float value)
{
    if (value >= 32767.0f) {
        return 32767;
    }
    if (value <= -32768.0f) {
        return -32768;
    }
    return (int16_t)((value >= 0.0f) ? (value + 0.5f) : (value - 0.5f));
}

static bool
nearly_equal(float a, float b, float epsilon)
{
    const float diff = a - b;
    return (diff >= -epsilon) && (diff <= epsilon);
}

static void
quad_order_spatial(const vg_saturn_vertex_t *vertices, OrderedQuadVertex *out)
{
    OrderedQuadVertex tmp[4];
    int order[4] = {0, 1, 2, 3};

    for (int i = 0; i < 4; i++) {
        tmp[i].x = vertices[i].x;
        tmp[i].y = vertices[i].y;
        tmp[i].u = vertices[i].u;
        tmp[i].v = vertices[i].v;
    }

    for (int pass = 0; pass < 3; pass++) {
        for (int i = 0; i < 3 - pass; i++) {
            const OrderedQuadVertex &a = tmp[order[i]];
            const OrderedQuadVertex &b = tmp[order[i + 1]];
            if ((a.y > b.y) || (nearly_equal(a.y, b.y, 0.5f) && (a.x > b.x))) {
                const int swap = order[i];
                order[i] = order[i + 1];
                order[i + 1] = swap;
            }
        }
    }

    if (tmp[order[0]].x > tmp[order[1]].x) {
        const int swap = order[0];
        order[0] = order[1];
        order[1] = swap;
    }
    if (tmp[order[2]].x > tmp[order[3]].x) {
        const int swap = order[2];
        order[2] = order[3];
        order[3] = swap;
    }

    out[0] = tmp[order[0]]; /* upper-left */
    out[1] = tmp[order[1]]; /* upper-right */
    out[2] = tmp[order[3]]; /* lower-right */
    out[3] = tmp[order[2]]; /* lower-left */
}

static bool
quad_bounds(const OrderedQuadVertex *quad, float *left, float *top,
            float *right, float *bottom)
{
    float min_x = quad[0].x;
    float max_x = quad[0].x;
    float min_y = quad[0].y;
    float max_y = quad[0].y;

    for (int i = 1; i < 4; i++) {
        if (quad[i].x < min_x) min_x = quad[i].x;
        if (quad[i].x > max_x) max_x = quad[i].x;
        if (quad[i].y < min_y) min_y = quad[i].y;
        if (quad[i].y > max_y) max_y = quad[i].y;
    }

    *left = min_x;
    *right = max_x;
    *top = min_y;
    *bottom = max_y;

    return ((max_x - min_x) >= 1.0f) && ((max_y - min_y) >= 1.0f);
}

static bool
quad_is_axis_aligned(const OrderedQuadVertex *quad)
{
    return nearly_equal(quad[0].y, quad[1].y, 0.75f) &&
           nearly_equal(quad[2].y, quad[3].y, 0.75f) &&
           nearly_equal(quad[0].x, quad[3].x, 0.75f) &&
           nearly_equal(quad[1].x, quad[2].x, 0.75f);
}

static vdp1_cmdt_char_flip_t
quad_flip_get(const OrderedQuadVertex *quad)
{
    vdp1_cmdt_char_flip_t flip = VDP1_CMDT_CHAR_FLIP_NONE;
    const float left_u = (quad[0].u + quad[3].u) * 0.5f;
    const float right_u = (quad[1].u + quad[2].u) * 0.5f;
    const float top_v = (quad[0].v + quad[1].v) * 0.5f;
    const float bottom_v = (quad[2].v + quad[3].v) * 0.5f;

    if (left_u > right_u) {
        flip = (vdp1_cmdt_char_flip_t)(flip | VDP1_CMDT_CHAR_FLIP_H);
    }
    if (top_v > bottom_v) {
        flip = (vdp1_cmdt_char_flip_t)(flip | VDP1_CMDT_CHAR_FLIP_V);
    }
    return flip;
}

static bool
path_contains_ci(const char *path, const char *needle)
{
    if ((path == nullptr) || (needle == nullptr) || (*needle == '\0')) {
        return false;
    }

    for (const char *cursor = path; *cursor != '\0'; cursor++) {
        const char *a = cursor;
        const char *b = needle;
        while ((*a != '\0') && (*b != '\0') &&
               (char_lower_ascii((unsigned char)*a) ==
                char_lower_ascii((unsigned char)*b))) {
            a++;
            b++;
        }
        if (*b == '\0') {
            return true;
        }
    }

    return false;
}

static bool
path_is_suppressed_background(const char *path)
{
    if (path == nullptr) {
        return false;
    }

    return path_contains_ci(path, "verdict/bgs/") ||
           path_contains_ci(path, "verdict\\bgs\\") ||
           path_contains_ci(path, "verdict/title/bg") ||
           path_contains_ci(path, "verdict\\title\\bg") ||
           path_contains_ci(path, "verdict/title/bg_vs") ||
           path_contains_ci(path, "verdict\\title\\bg_vs") ||
           path_contains_ci(path, "verdict/title/bg_anim") ||
           path_contains_ci(path, "verdict\\title\\bg_anim") ||
           path_contains_ci(path, "verdict/story/bg/") ||
           path_contains_ci(path, "verdict\\story\\bg\\");
}

static void
vblank_out_handler(void *work __unused)
{
    g_frame_count++;
    smpc_peripheral_intback_issue();
}

static void
placeholder_init(void)
{
    memset(g_placeholder_palette, 0, sizeof(g_placeholder_palette));
    g_placeholder_palette[1] = RGB1555(1, 31, 0, 31).raw;
    g_placeholder_palette[2] = RGB1555(1, 0, 0, 0).raw;

    for (uint32_t y = 0; y < 16; y++) {
        for (uint32_t x = 0; x < 16; x += 2) {
            const uint8_t a = ((((x >> 2) ^ (y >> 2)) & 1) != 0) ? 1 : 2;
            const uint8_t b = (((((x + 1) >> 2) ^ (y >> 2)) & 1) != 0) ? 1 : 2;
            g_placeholder_pixels[(y * 8) + (x >> 1)] = (uint8_t)((a << 4) | b);
        }
    }
}

static void
cmdt_header_set(void)
{
    static const int16_vec2_t system_clip =
        INT16_VEC2_INITIALIZER(VG_SATURN_SCREEN_W - 1, VG_SATURN_SCREEN_H - 1);
    static const int16_vec2_t local =
        INT16_VEC2_INITIALIZER(0, 0);

    vdp1_cmdt_t *cmdts = g_cmdt_list->cmdts;

    memset(cmdts, 0, sizeof(vdp1_cmdt_t) * kMaxCmdts);
    g_cmdt_list->count = kMaxCmdts;

    vdp1_cmdt_system_clip_coord_set(&cmdts[0]);
    vdp1_cmdt_vtx_system_clip_coord_set(&cmdts[0], system_clip);

    vdp1_cmdt_local_coord_set(&cmdts[1]);
    vdp1_cmdt_vtx_local_coord_set(&cmdts[1], local);

    g_cmdt_index = 2;
}

static vdp1_cmdt_t *
cmdt_next(void)
{
    if (g_cmdt_index >= (kMaxCmdts - 1)) {
        return nullptr;
    }
    return &g_cmdt_list->cmdts[g_cmdt_index++];
}

static void
frame_uploads_reset(void)
{
    g_frame_upload_count = 0;
    g_frame_upload_bytes = 0;
    g_frame_cache_hits = 0;
    g_frame_cache_misses = 0;
    g_frame_cache_evictions = 0;
    g_debug_last_upload_bytes = 0;
    for (uint32_t i = 0; i < g_frame_slot_count; i++) {
        g_frame_slots[i].touched_this_frame = false;
    }
}

static void
frame_cache_reset_all(void)
{
    memset(g_frame_slots, 0, sizeof(g_frame_slots));
    g_frame_slot_count = 0;
    g_frame_vram_cursor = g_frame_vram_base;
    g_frame_upload_count = 0;
    g_frame_upload_bytes = 0;
    g_frame_cache_hits = 0;
    g_frame_cache_misses = 0;
    g_frame_cache_evictions = 0;
    g_debug_last_upload_bytes = 0;
}

static bool
frame_key_equal(const Vdp1FrameKey &left, const Vdp1FrameKey &right)
{
    return (left.texture == right.texture) &&
           (left.sx == right.sx) &&
           (left.sy == right.sy) &&
           (left.sw == right.sw) &&
           (left.sh == right.sh);
}

static void
frame_cache_evict_texture(GLuint texture)
{
    if (texture == 0) {
        return;
    }

    for (uint32_t i = 0; i < g_frame_slot_count; i++) {
        Vdp1FrameSlot &slot = g_frame_slots[i];
        if (slot.used && (slot.key.texture == texture)) {
            slot.used = false;
            slot.touched_this_frame = false;
        }
    }
}

static void
cart_object_pool_init(void)
{
    void *cart = dram_cart_area_get();
    const size_t cart_size = dram_cart_size_get();
    g_cart_object_pool_base = nullptr;
    g_cart_object_pool_size = 0;
    g_cart_object_pool_cursor = 0;

    if ((cart == nullptr) || (cart_size < (kCartObjectPoolBytes + 0x00010000U))) {
        return;
    }

    g_cart_object_pool_base = static_cast<uint8_t *>(cart);
    g_cart_object_pool_size = kCartObjectPoolBytes;
    memset(g_cart_object_pool_base, 0, g_cart_object_pool_size);
}

static void
cache_init(void)
{
    void *cart = dram_cart_area_get();
    const size_t cart_size = dram_cart_size_get();
    g_cache_slot_count = 0;
    g_cache_base = nullptr;
    g_cache_size = 0;
    g_cache_cursor = 0;
    memset(g_cache_slots, 0, sizeof(g_cache_slots));

    if ((cart == nullptr) || (cart_size <= kCartObjectPoolBytes)) {
        g_warned_no_cart = true;
        return;
    }

    g_cache_base = static_cast<uint8_t *>(cart) + kCartObjectPoolBytes;
    const size_t cache_size = cart_size - kCartObjectPoolBytes;
    if (cache_size < 0x00010000U) {
        g_warned_no_cart = true;
        g_cache_base = nullptr;
        return;
    }

    g_cache_size = (uint32_t)cache_size;
}

static void
cache_reset_all(void)
{
    memset(g_cache_slots, 0, sizeof(g_cache_slots));
    g_cache_slot_count = 0;
    g_cache_cursor = 0;

    for (uint32_t i = 0; i < kMaxTextures; i++) {
        g_textures[i].resident = false;
        g_textures[i].cache_slot = -1;
    }
}

static void
texture_evict(GLuint texture)
{
    if (texture >= kMaxTextures) {
        return;
    }

    frame_cache_evict_texture(texture);

    SaturnTexture &tex = g_textures[texture];
    if ((tex.cache_slot >= 0) && ((uint32_t)tex.cache_slot < g_cache_slot_count)) {
        CacheSlot &slot = g_cache_slots[tex.cache_slot];
        if (slot.texture == texture) {
            slot.used = false;
            slot.texture = 0;
            slot.bytes = 0;
        }
    }

    tex.cache_slot = -1;
    tex.resident = false;
}

extern "C" void
vg_saturn_cart_object_pool_reset(void)
{
    if (g_cart_object_pool_base == nullptr) {
        return;
    }

    g_cart_object_pool_cursor = 0;
    memset(g_cart_object_pool_base, 0, g_cart_object_pool_size);
}

extern "C" void *
vg_saturn_cart_object_alloc(size_t size, size_t align)
{
    if ((g_cart_object_pool_base == nullptr) || (size == 0)) {
        return nullptr;
    }

    if (align < 16) {
        align = 16;
    }

    const uint32_t aligned_cursor =
        align_up_u32(g_cart_object_pool_cursor, (uint32_t)align);
    if ((aligned_cursor > g_cart_object_pool_size) ||
        (size > (g_cart_object_pool_size - aligned_cursor))) {
        return nullptr;
    }

    uint8_t *ptr = g_cart_object_pool_base + aligned_cursor;
    g_cart_object_pool_cursor = aligned_cursor + (uint32_t)size;
    return ptr;
}

extern "C" size_t
vg_saturn_cart_object_pool_size(void)
{
    return g_cart_object_pool_size;
}

extern "C" size_t
vg_saturn_cart_object_pool_used(void)
{
    return g_cart_object_pool_cursor;
}

static int
cache_slot_acquire(GLuint texture, uint32_t bytes)
{
    if ((g_cache_base == nullptr) || (g_cache_size == 0) || (bytes == 0) ||
        (bytes > g_cache_size)) {
        return -1;
    }

    bytes = align_up_u32(bytes, 16);

    SaturnTexture &tex = g_textures[texture];
    if ((tex.cache_slot >= 0) && ((uint32_t)tex.cache_slot < g_cache_slot_count)) {
        CacheSlot &slot = g_cache_slots[tex.cache_slot];
        if (slot.texture == texture) {
            slot.last_used = ++g_cache_tick;
            return tex.cache_slot;
        }
    }

    if ((g_cache_cursor > g_cache_size) ||
        (bytes > (g_cache_size - g_cache_cursor)) ||
        (g_cache_slot_count >= kMaxCacheSlots)) {
        cache_reset_all();
    }

    if ((g_cache_cursor > g_cache_size) ||
        (bytes > (g_cache_size - g_cache_cursor)) ||
        (g_cache_slot_count >= kMaxCacheSlots)) {
        return -1;
    }

    const int selected = (int)g_cache_slot_count++;
    CacheSlot &slot = g_cache_slots[selected];
    slot.used = true;
    slot.base = g_cache_base + g_cache_cursor;
    slot.capacity = bytes;
    slot.bytes = bytes;
    slot.texture = texture;
    slot.last_used = ++g_cache_tick;
    tex.cache_slot = selected;
    g_cache_cursor += bytes;
    return selected;
}

static void
texture_palette_upload(SaturnTexture &tex, const uint16_t *palette)
{
    if (tex.clut == nullptr) {
        return;
    }

    memcpy(tex.clut->colors, palette, sizeof(uint16_t) * 16);
}

static bool
texture_upload_from_memory(GLuint texture, const uint8_t *data, uint32_t data_size)
{
    if ((texture == 0) || (texture >= kMaxTextures) || (data == nullptr) ||
        (data_size <= 32)) {
        return false;
    }

    SaturnTexture &tex = g_textures[texture];
    const uint32_t payload_bytes = data_size - 32;
    const int slot_index = cache_slot_acquire(texture, payload_bytes);
    if (slot_index < 0) {
        if (!tex.warned) {
            VG_SATURN_DEBUG_DBGP("No ext RAM slot for tex %lu (%lu bytes)\n",
                                 texture, payload_bytes);
            tex.warned = true;
        }
        tex.resident = false;
        return false;
    }

    uint16_t palette[16];
    memcpy(palette, data, sizeof(palette));
    texture_palette_upload(tex, palette);
    memcpy(g_cache_slots[slot_index].base, data + 32, payload_bytes);
    tex.data_bytes = payload_bytes;
    tex.resident = true;
    return true;
}

static bool
texture_load_from_cd(GLuint texture)
{
    if ((texture == 0) || (texture >= kMaxTextures)) {
        return false;
    }

    SaturnTexture &tex = g_textures[texture];
    if (tex.path[0] == '\0') {
        return false;
    }

#if VG_SATURN_DEBUG_LOG
    const bool debug_this_read = (g_debug_texture_cd_attempt_count < 96);
    g_debug_texture_cd_attempt_count++;
#else
    const bool debug_this_read = false;
#endif
    if (debug_this_read) {
        vg_saturn_debug_stage(733, "texture_cd_before_read");
        vg_saturn_debug_puts("[TEX] ");
        vg_saturn_debug_puts(tex.path);
        vg_saturn_debug_puts("\n");
    }

    cdfs_filelist_entry_t entry = {};
    if (!cd_find_path(tex.path, &entry)) {
        if (debug_this_read) {
            vg_saturn_debug_stage(732, "texture_cd_find_failed");
        }
        if (!tex.warned) {
            VG_SATURN_DEBUG_DBGP("Texture CD open failed: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    const int first_read_result =
        cd_block_sectors_read(entry.starting_fad, g_cd_sector_buffer,
                              CDFS_SECTOR_SIZE);
    if (first_read_result != 0) {
        if (debug_this_read) {
            char fail_buffer[128];
            snprintf(fail_buffer, sizeof(fail_buffer),
                     "[CDERR] first path=%s fad=%lu size=%lu ret=%d\n",
                     tex.path, (uint32_t)entry.starting_fad,
                     (uint32_t)entry.size, first_read_result);
            vg_saturn_debug_puts(fail_buffer);
            vg_saturn_debug_stage(732, "texture_cd_first_read_failed");
        }
        if (!tex.warned) {
            VG_SATURN_DEBUG_DBGP("Texture CD first sector failed: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }
    const uint32_t file_size = (uint32_t)entry.size;

    if (debug_this_read) {
        vg_saturn_debug_stage(734, "texture_cd_after_read");
    }

    const uint32_t header_bytes = sizeof(SatTextureHeader);
    const uint32_t palette_bytes = sizeof(uint16_t) * 16;
    if (file_size < (header_bytes + palette_bytes)) {
        if (!tex.warned) {
            VG_SATURN_DEBUG_DBGP("Texture CD header invalid: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    SatTextureHeader header;
    memcpy(&header, g_cd_sector_buffer, sizeof(header));
    uint16_t palette[16];
    memcpy(palette, g_cd_sector_buffer + header_bytes, sizeof(palette));

    if ((memcmp(header.magic, "VG4P", 4) != 0) ||
        (header.width == 0) || (header.height == 0) ||
        (header.data_size == 0) || 
        ((header_bytes + palette_bytes + header.data_size) > file_size)) {
        if (!tex.warned) {
            VG_SATURN_DEBUG_DBGP("Texture CD header invalid: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    const uint32_t sector_count = cdfs_sector_count_round(file_size);
    const uint32_t rounded_size = sector_count * CDFS_SECTOR_SIZE;
    if ((g_cache_size == 0) || (rounded_size > g_cache_size)) {
        if (!tex.warned) {
            VG_SATURN_DEBUG_DBGP("Texture too large for ext slot: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    const int slot_index = cache_slot_acquire(texture, rounded_size);
    if (slot_index < 0) {
        if (!tex.warned) {
            VG_SATURN_DEBUG_DBGP("No ext RAM slot for: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    CacheSlot &slot = g_cache_slots[slot_index];
    uint32_t loaded_size = 0;
    if (!cd_read_entry_to(&entry, slot.base, rounded_size, &loaded_size)) {
        texture_evict(texture);
        if (!tex.warned) {
            VG_SATURN_DEBUG_DBGP("Texture CD slot read failed: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }
    memmove(slot.base, slot.base + header_bytes + palette_bytes, header.data_size);
    slot.bytes = header.data_size;

    tex.width = header.width;
    tex.height = header.height;
    tex.data_bytes = header.data_size;
    tex.resident = true;
    tex.warned = false;
    texture_palette_upload(tex, palette);
    if (debug_this_read) {
        vg_saturn_debug_stage(735, "texture_cd_cached");
    }
    g_debug_first_texture_cd = true;
    g_debug_texture_cd_count++;
    return true;
}

static const uint8_t *
texture_pixels_get(GLuint texture)
{
    if ((texture == 0) || (texture >= kMaxTextures)) {
        return nullptr;
    }

    SaturnTexture &tex = g_textures[texture];
    if (!tex.used || tex.skipped) {
        return nullptr;
    }

    if (!tex.resident && !texture_load_from_cd(texture)) {
        return nullptr;
    }

    if ((tex.cache_slot < 0) || ((uint32_t)tex.cache_slot >= g_cache_slot_count)) {
        return nullptr;
    }

    CacheSlot &slot = g_cache_slots[tex.cache_slot];
    if (!slot.used || (slot.texture != texture)) {
        tex.resident = false;
        tex.cache_slot = -1;
        return nullptr;
    }

    slot.last_used = ++g_cache_tick;
    return slot.base;
}

static uint8_t
source_texel_get(const uint8_t *pixels, uint16_t texture_width, uint16_t x,
                 uint16_t y)
{
    const uint32_t stride = ((uint32_t)texture_width + 1U) >> 1;
    const uint8_t value = pixels[((uint32_t)y * stride) + (x >> 1)];
    return (x & 1U) ? (value & 0x0FU) : (value >> 4);
}

static Vdp1FrameSlot *
frame_slot_lru_find(uint32_t bytes)
{
    Vdp1FrameSlot *candidate = nullptr;
    for (uint32_t i = 0; i < g_frame_slot_count; i++) {
        Vdp1FrameSlot &slot = g_frame_slots[i];
        if (!slot.used || slot.touched_this_frame || (slot.capacity < bytes)) {
            continue;
        }
        if ((candidate == nullptr) ||
            (slot.last_used_frame < candidate->last_used_frame)) {
            candidate = &slot;
        }
    }
    return candidate;
}

static Vdp1FrameSlot *
frame_slot_alloc(uint32_t bytes)
{
    for (uint32_t i = 0; i < g_frame_slot_count; i++) {
        Vdp1FrameSlot &slot = g_frame_slots[i];
        if (!slot.used && (slot.capacity >= bytes)) {
            return &slot;
        }
    }

    if ((g_frame_slot_count < kFrameUploadMax) &&
        ((g_frame_vram_cursor + bytes) <= g_frame_vram_end)) {
        Vdp1FrameSlot &slot = g_frame_slots[g_frame_slot_count++];
        slot.base = g_frame_vram_cursor;
        slot.capacity = bytes;
        g_frame_vram_cursor += bytes;
        return &slot;
    }

    Vdp1FrameSlot *slot = frame_slot_lru_find(bytes);
    if (slot != nullptr) {
        slot->used = false;
        slot->touched_this_frame = false;
        g_frame_cache_evictions++;
    }
    return slot;
}

static void
frame_slot_copy_pixels(Vdp1FrameSlot &slot, const SaturnTexture &tex,
                       const uint8_t *pixels)
{
    const uint32_t dst_row_bytes = slot.slot_w >> 1;
    const uint32_t src_stride = ((uint32_t)tex.width + 1U) >> 1;
    const uint16_t sx = slot.key.sx;
    const uint16_t sy = slot.key.sy;
    const uint16_t sw = slot.key.sw;
    const uint16_t sh = slot.key.sh;

    if (((sx & 1U) == 0U) && ((sw & 1U) == 0U)) {
        const uint32_t copy_bytes = sw >> 1;
        const uint32_t pad_bytes = dst_row_bytes - copy_bytes;
        for (uint16_t y = 0; y < sh; y++) {
            uint8_t *dst = slot.base + ((uint32_t)y * dst_row_bytes);
            const uint8_t *src =
                pixels + ((uint32_t)(sy + y) * src_stride) + (sx >> 1);
            memcpy(dst, src, copy_bytes);
            if (pad_bytes > 0) {
                memset(dst + copy_bytes, 0, pad_bytes);
            }
        }
        return;
    }

    for (uint16_t y = 0; y < sh; y++) {
        uint8_t *dst = slot.base + ((uint32_t)y * dst_row_bytes);
        for (uint16_t x = 0; x < slot.slot_w; x += 2) {
            uint8_t a = 0;
            uint8_t b = 0;
            if (x < sw) {
                a = source_texel_get(pixels, tex.width, (uint16_t)(sx + x),
                                     (uint16_t)(sy + y));
            }
            if ((uint16_t)(x + 1) < sw) {
                b = source_texel_get(pixels, tex.width, (uint16_t)(sx + x + 1),
                                     (uint16_t)(sy + y));
            }
            dst[x >> 1] = (uint8_t)((a << 4) | b);
        }
    }
}

static const Vdp1FrameSlot *
sprite_frame_get_or_upload(GLuint texture, const uint8_t *pixels, uint16_t sx,
                           uint16_t sy, uint16_t sw, uint16_t sh)
{
    SaturnTexture &tex = g_textures[texture];
    const Vdp1FrameKey key = {texture, sx, sy, sw, sh};
    for (uint32_t i = 0; i < g_frame_slot_count; i++) {
        Vdp1FrameSlot &slot = g_frame_slots[i];
        if (slot.used && frame_key_equal(slot.key, key)) {
            slot.last_used_frame = (uint32_t)g_frame_count;
            slot.touched_this_frame = true;
            g_frame_cache_hits++;
            return &slot;
        }
    }

    const uint16_t slot_w = align8_u16(sw);
    const uint32_t row_bytes = slot_w >> 1;
    const uint32_t bytes = (row_bytes * sh + 7U) & ~7U;
    if (bytes == 0) {
        return nullptr;
    }

    Vdp1FrameSlot *slot = frame_slot_alloc(bytes);
    if (slot == nullptr) {
        if (!tex.warned) {
            VG_SATURN_DEBUG_DBGP("VDP1 frame cache full (%lux%lu)\n",
                                 (uint32_t)sw, (uint32_t)sh);
            tex.warned = true;
        }
        return nullptr;
    }

    slot->key = key;
    slot->bytes = bytes;
    slot->slot_w = slot_w;
    slot->slot_h = sh;
    slot->last_used_frame = (uint32_t)g_frame_count;
    slot->used = true;
    slot->touched_this_frame = true;

    frame_slot_copy_pixels(*slot, tex, pixels);
    g_frame_upload_count++;
    g_frame_upload_bytes += bytes;
    g_debug_last_upload_bytes += bytes;
    g_frame_cache_misses++;

    return slot;
}

static GLuint
placeholder_texture_get(void)
{
    static GLuint placeholder_id = 0;
    if (placeholder_id == 0) {
        placeholder_id = vg_saturn_texture_create(16, 16, nullptr);
        SaturnTexture &tex = g_textures[placeholder_id];
        tex.width = 16;
        tex.height = 16;
        tex.data_bytes = sizeof(g_placeholder_pixels);
        tex.resident = true;
        texture_palette_upload(tex, g_placeholder_palette);
        const int slot_index = cache_slot_acquire(placeholder_id, sizeof(g_placeholder_pixels));
        if (slot_index >= 0) {
            memcpy(g_cache_slots[slot_index].base, g_placeholder_pixels,
                   sizeof(g_placeholder_pixels));
            tex.cache_slot = slot_index;
        }
    }
    return placeholder_id;
}

void
vg_saturn_init(void)
{
    if (g_inited) {
        return;
    }

    vg_saturn_debug_init();
    vg_saturn_debug_stage(10, "platform_init_begin");

    g_inited = true;
    vg_saturn_lowram_clear();
    placeholder_init();

    smpc_peripheral_init();
    cd_block_init();
    cdfs_config_default_set();
    cdfs_init();
    dram_cart_init();
    cart_object_pool_init();

    vdp2_tvmd_display_res_set(VDP2_TVMD_INTERLACE_NONE, VDP2_TVMD_HORZ_NORMAL_A,
                              VDP2_TVMD_VERT_240);
    vdp2_scrn_back_color_set(VDP2_VRAM_ADDR(3, 0x01FFFE),
                             RGB1555(1, 0, 4, 0));
    for (uint32_t i = 0; i < 8; i++) {
        vdp2_sprite_priority_set(i, 6);
    }

    if (kDebugUseDefaultVdp1Layout) {
        vdp1_env_default_set();
    } else {
        vdp1_env_t vdp1_env;
        vdp1_env_default_init(&vdp1_env);
        vdp1_env.bpp = VDP1_ENV_BPP_16;
        vdp1_env.rotation = VDP1_ENV_ROTATION_0;
        vdp1_env.color_mode = VDP1_ENV_COLOR_MODE_RGB_PALETTE;
        vdp1_env.sprite_type = 1;
        vdp1_env.erase_color = RGB1555(1, 0, 4, 0);
        vdp1_env.erase_points[0].x = 0;
        vdp1_env.erase_points[0].y = 0;
        vdp1_env.erase_points[1].x = VG_SATURN_SCREEN_W;
        vdp1_env.erase_points[1].y = VG_SATURN_SCREEN_H;
        vdp1_env_set(&vdp1_env);
    }
    vdp1_sync_interval_set(0);
    vdp2_tvmd_display_set();
    vdp_sync_vblank_out_set(vblank_out_handler, nullptr);

    if (!kDebugUseDefaultVdp1Layout) {
        vdp1_vram_partitions_set(kMaxCmdts, kTextureBudget, 64, kClutCount);
    }
    vdp1_vram_partitions_get(&g_vdp1_parts);
    g_frame_vram_base = static_cast<uint8_t *>(g_vdp1_parts.texture_base);
    g_frame_vram_end = g_frame_vram_base + g_vdp1_parts.texture_size;
    memset(g_frame_vram_base, 0, g_vdp1_parts.texture_size);
    memset(g_textures, 0, sizeof(g_textures));
    for (uint32_t i = 0; i < kMaxTextures; i++) {
        g_textures[i].cache_slot = -1;
    }
    frame_cache_reset_all();
    cache_init();

    g_cmdt_list = vdp1_cmdt_list_alloc(kMaxCmdts);
    cmdt_header_set();

    dbgio_init();
#if VG_SATURN_PROFILE || VG_SATURN_DEBUG_LOG
    dbgio_dev_default_init(DBGIO_DEV_MEDNAFEN_DEBUG);
#else
    dbgio_dev_default_init(DBGIO_DEV_NULL);
#endif
    vg_saturn_profile_init();
    for (uint32_t i = 0; i < 8; i++) {
        vdp2_sprite_priority_set(i, 6);
    }
#if VG_SATURN_DEBUG_LOG
    if (g_warned_no_cart) {
        VG_SATURN_DEBUG_DBGP("4MB RAM cart missing; sprite streaming disabled\n");
        vg_saturn_debug_stage(19, "platform_init_no_cart");
    } else {
        VG_SATURN_DEBUG_DBGP("Ext RAM cache slots: %lu\n", g_cache_slot_count);
        vg_saturn_debug_stage(18, "platform_init_cart_ok");
    }
#endif

    vdp2_sync();
    vdp2_sync_wait();
    vg_saturn_debug_stage(20, "platform_init_done");
}

static bool
cd_find_path(const char *path, cdfs_filelist_entry_t *out_entry)
{
    if ((path == nullptr) || (out_entry == nullptr)) {
        return false;
    }

    cdfs_filelist_t filelist;
    cdfs_filelist_init(&filelist, g_cd_entries,
                       (int32_t)(sizeof(g_cd_entries) / sizeof(g_cd_entries[0])));
    cdfs_filelist_root_read(&filelist);

    const char *cursor = path;
    if ((cursor[0] == 'c' || cursor[0] == 'C') &&
        (cursor[1] == 'd' || cursor[1] == 'D') &&
        ((cursor[2] == '/') || (cursor[2] == '\\'))) {
        cursor += 3;
    }

    cdfs_filelist_entry_t entry = {};
    char component[32];
    bool has_more = false;
    bool found_component = false;

    while (cd_next_component(&cursor, component, sizeof(component), &has_more)) {
        found_component = true;
        if (has_more) {
            if (!cd_find_entry(&filelist, component, CDFS_ENTRY_TYPE_DIRECTORY, &entry)) {
                return false;
            }
            cdfs_filelist_read(&filelist, entry);
        } else {
            if (!cd_find_entry(&filelist, component, CDFS_ENTRY_TYPE_FILE, &entry)) {
                return false;
            }
        }
    }

    if (!found_component || (entry.type != CDFS_ENTRY_TYPE_FILE) || (entry.size == 0)) {
        return false;
    }

    *out_entry = entry;
    return true;
}

static bool
cd_read_entry_to(const cdfs_filelist_entry_t *entry, uint8_t *data,
                 uint32_t capacity, uint32_t *out_size)
{
    if ((entry == nullptr) || (data == nullptr) || (out_size == nullptr) ||
        (entry->type != CDFS_ENTRY_TYPE_FILE) || (entry->size == 0)) {
        return false;
    }

    const uint32_t sector_count = cdfs_sector_count_round((uint32_t)entry->size);
    const uint32_t rounded_size = sector_count * CDFS_SECTOR_SIZE;
    if (rounded_size > capacity) {
        return false;
    }

    if (cd_block_sectors_read(entry->starting_fad, data, (uint32_t)entry->size) != 0) {
        return false;
    }

    if (capacity > (uint32_t)entry->size) {
        data[entry->size] = 0;
    }
    *out_size = (uint32_t)entry->size;
    return true;
}

bool
vg_saturn_cd_read_file(const char *path, void **out_data, uint32_t *out_size)
{
    if ((path == nullptr) || (out_data == nullptr) || (out_size == nullptr)) {
        return false;
    }

    *out_data = nullptr;
    *out_size = 0;

    cdfs_filelist_entry_t entry = {};
    if (!cd_find_path(path, &entry)) {
        return false;
    }

    const uint32_t sector_count = cdfs_sector_count_round((uint32_t)entry.size);
    const uint32_t rounded_size = sector_count * CDFS_SECTOR_SIZE;
    uint8_t *data = static_cast<uint8_t *>(malloc(rounded_size + 1));
    if (data == nullptr) {
        return false;
    }

    if (!cd_read_entry_to(&entry, data, rounded_size + 1, out_size)) {
        free(data);
        return false;
    }

    *out_data = data;
    return true;
}

void
vg_saturn_cd_free_file(void *data)
{
    free(data);
}

void
vg_saturn_frame_begin(void)
{
    vg_saturn_init();
    cmdt_header_set();
    frame_uploads_reset();
    g_frame_quads_in = 0;
    g_frame_quads_drawn = 0;
    g_frame_quads_skipped = 0;
    g_frame_quads_scaled = 0;
    g_frame_quads_distorted = 0;
    g_frame_skip_alpha = 0;
    g_frame_skip_texture = 0;
    g_frame_skip_bounds = 0;
    g_frame_skip_upload = 0;
    g_frame_skip_cmdt = 0;
    g_frame_sample_valid = false;
    g_frame_sample_x = 0;
    g_frame_sample_y = 0;
    g_frame_sample_w = 0;
    g_frame_sample_h = 0;
    g_frame_sample_sw = 0;
    g_frame_sample_sh = 0;
    g_frame_debug_draw_logs = 0;
}

void
vg_saturn_frame_end(void)
{
    vg_saturn_init();

    if (g_cmdt_index >= kMaxCmdts) {
        g_cmdt_index = kMaxCmdts - 1;
    }

    if (kDebugDrawVdp1Marker) {
        debug_marker_draw();
    }

    vdp1_cmdt_end_set(&g_cmdt_list->cmdts[g_cmdt_index]);
    g_cmdt_list->count = (uint16_t)(g_cmdt_index + 1);
    g_debug_last_cmdts = g_cmdt_index + 1;
    g_debug_last_uploads = g_frame_upload_count;
    g_debug_last_quads_in = g_frame_quads_in;
    g_debug_last_quads_drawn = g_frame_quads_drawn;
    g_debug_last_quads_skipped = g_frame_quads_skipped;
    g_debug_last_quads_scaled = g_frame_quads_scaled;
    g_debug_last_quads_distorted = g_frame_quads_distorted;
    g_debug_skip_alpha = g_frame_skip_alpha;
    g_debug_skip_texture = g_frame_skip_texture;
    g_debug_skip_bounds = g_frame_skip_bounds;
    g_debug_skip_upload = g_frame_skip_upload;
    g_debug_skip_cmdt = g_frame_skip_cmdt;
    g_debug_sample_valid = g_frame_sample_valid;
    g_debug_sample_x = g_frame_sample_x;
    g_debug_sample_y = g_frame_sample_y;
    g_debug_sample_w = g_frame_sample_w;
    g_debug_sample_h = g_frame_sample_h;
    g_debug_sample_sw = g_frame_sample_sw;
    g_debug_sample_sh = g_frame_sample_sh;

    vg_saturn_profile_backend_ready(g_frame_count, g_debug_last_cmdts,
                                    g_debug_last_quads_in,
                                    g_debug_last_quads_drawn,
                                    g_debug_last_quads_skipped,
                                    g_debug_last_uploads,
                                    g_debug_last_upload_bytes,
                                    g_frame_cache_hits,
                                    g_frame_cache_misses,
                                    g_frame_cache_evictions);

    vdp1_sync_cmdt_list_put(g_cmdt_list, 0);
    vdp1_sync_render();
    vdp1_sync();
#if VG_SATURN_PROFILE
    const uint16_t vdp1_wait_start = vg_saturn_profile_now();
#endif
    vdp1_sync_wait();
#if VG_SATURN_PROFILE
    vg_saturn_profile_vdp1_wait_add(
        vg_saturn_profile_elapsed(vdp1_wait_start));
#endif

#if VG_SATURN_DEBUG_LOG
    volatile vdp1_ioregs_t * const vdp1_ioregs =
        (volatile vdp1_ioregs_t *)VDP1_IOREG_BASE;
    g_debug_vdp1_edsr = vdp1_ioregs->edsr;
    g_debug_vdp1_lopr = vdp1_ioregs->lopr;
    g_debug_vdp1_copr = vdp1_ioregs->copr;
    g_debug_vdp1_modr = vdp1_ioregs->modr;
    g_debug_vdp1_tvmr = vdp1_ioregs->tvmr;
    g_debug_vdp1_ptmr = vdp1_ioregs->ptmr;

    volatile vdp2_ioregs_t * const vdp2_ioregs =
        (volatile vdp2_ioregs_t *)VDP2_IOREG_BASE;
    g_debug_vdp2_tvmd = vdp2_ioregs->tvmd;
    g_debug_vdp2_bgon = vdp2_ioregs->bgon;
    g_debug_vdp2_spctl = vdp2_ioregs->spctl;
    g_debug_vdp2_prisa = vdp2_ioregs->prisa;
    g_debug_vdp2_prisb = vdp2_ioregs->prisb;
    g_debug_vdp2_prisc = vdp2_ioregs->prisc;
    g_debug_vdp2_prisd = vdp2_ioregs->prisd;

    if (!g_debug_passed_first_frame) {
        g_debug_passed_first_frame = true;
        vg_saturn_debug_pass("first_vdp1_frame");
        vg_saturn_debug_vdp1_regs(g_frame_count, g_debug_vdp1_edsr,
                                  g_debug_vdp1_lopr,
                                  g_debug_vdp1_copr,
                                  g_debug_vdp1_modr,
                                  g_debug_vdp1_tvmr,
                                  g_debug_vdp1_ptmr);
        vg_saturn_debug_vdp1(g_frame_count, g_debug_last_quads_in,
                             g_debug_last_quads_drawn,
                             g_debug_last_quads_skipped,
                             g_debug_last_quads_scaled,
                             g_debug_last_quads_distorted);
        vg_saturn_debug_vdp1_detail(g_frame_count, g_debug_skip_alpha,
                                    g_debug_skip_texture,
                                    g_debug_skip_bounds,
                                    g_debug_skip_upload,
                                    g_debug_skip_cmdt,
                                    g_debug_sample_valid ? g_debug_sample_x : 0,
                                    g_debug_sample_valid ? g_debug_sample_y : 0,
                                    g_debug_sample_valid ? g_debug_sample_w : 0,
                                    g_debug_sample_valid ? g_debug_sample_h : 0,
                                    g_debug_sample_valid ? g_debug_sample_sw : 0,
                                    g_debug_sample_valid ? g_debug_sample_sh : 0);
        vg_saturn_debug_vdp2_regs(g_frame_count, g_debug_vdp2_tvmd,
                                  g_debug_vdp2_bgon,
                                  g_debug_vdp2_spctl,
                                  g_debug_vdp2_prisa,
                                  g_debug_vdp2_prisb,
                                  g_debug_vdp2_prisc,
                                  g_debug_vdp2_prisd);
    }

    dbgio_flush();
    const uint64_t debug_frame = g_frame_count;
    if ((debug_frame % 60) == 0) {
        dbgio_printf("[VG] frame=%lu cmdts=%lu uploads=%lu upload_bytes=%lu cache_slots=%lu\n",
                     (uint32_t)debug_frame, g_debug_last_cmdts,
                     g_debug_last_uploads, g_debug_last_upload_bytes,
                     g_cache_slot_count);
        dbgio_printf("[VDP1] quads=%lu drawn=%lu skip=%lu scaled=%lu distort=%lu\n",
                     g_debug_last_quads_in, g_debug_last_quads_drawn,
                     g_debug_last_quads_skipped, g_debug_last_quads_scaled,
                     g_debug_last_quads_distorted);
        dbgio_flush();
        vg_saturn_debug_frame(debug_frame, g_debug_last_cmdts,
                              g_debug_last_uploads, g_debug_last_upload_bytes,
                              g_cache_slot_count);
        vg_saturn_debug_vdp1(debug_frame, g_debug_last_quads_in,
                             g_debug_last_quads_drawn,
                             g_debug_last_quads_skipped,
                             g_debug_last_quads_scaled,
                             g_debug_last_quads_distorted);
        vg_saturn_debug_vdp1_detail(debug_frame, g_debug_skip_alpha,
                                    g_debug_skip_texture,
                                    g_debug_skip_bounds,
                                    g_debug_skip_upload,
                                    g_debug_skip_cmdt,
                                    g_debug_sample_valid ? g_debug_sample_x : 0,
                                    g_debug_sample_valid ? g_debug_sample_y : 0,
                                    g_debug_sample_valid ? g_debug_sample_w : 0,
                                    g_debug_sample_valid ? g_debug_sample_h : 0,
                                    g_debug_sample_valid ? g_debug_sample_sw : 0,
                                    g_debug_sample_valid ? g_debug_sample_sh : 0);
        vg_saturn_debug_vdp1_regs(debug_frame, g_debug_vdp1_edsr,
                                  g_debug_vdp1_lopr,
                                  g_debug_vdp1_copr,
                                  g_debug_vdp1_modr,
                                  g_debug_vdp1_tvmr,
                                  g_debug_vdp1_ptmr);
        vg_saturn_debug_vdp2_regs(debug_frame, g_debug_vdp2_tvmd,
                                  g_debug_vdp2_bgon,
                                  g_debug_vdp2_spctl,
                                  g_debug_vdp2_prisa,
                                  g_debug_vdp2_prisb,
                                  g_debug_vdp2_prisc,
                                  g_debug_vdp2_prisd);
    }
#endif
    vdp2_sync();
#if VG_SATURN_PROFILE
    const uint16_t vblank_wait_start = vg_saturn_profile_now();
#endif
    vdp2_sync_wait();
#if VG_SATURN_PROFILE
    vg_saturn_profile_vblank_wait_add(
        vg_saturn_profile_elapsed(vblank_wait_start));
#endif
}

uint64_t
vg_saturn_millis_get(void)
{
    return (g_frame_count * 1000ULL) / 60ULL;
}

void
vg_saturn_input_update(void)
{
    vg_saturn_init();
    smpc_peripheral_process();
    smpc_peripheral_digital_port(1, &g_digital[0]);
    smpc_peripheral_digital_port(2, &g_digital[1]);
}

uint16_t
vg_saturn_input_pressed(int port)
{
    if ((port < 0) || (port > 1)) {
        return 0;
    }
    return g_digital[port].pressed.raw;
}

uint16_t
vg_saturn_input_held(int port)
{
    if ((port < 0) || (port > 1)) {
        return 0;
    }
    return g_digital[port].held.raw;
}

GLuint
vg_saturn_texture_create(GLsizei width, GLsizei height, const void *argb1555)
{
    (void)argb1555;
    vg_saturn_init();

    GLuint id = g_next_texture++;
    if (id >= kMaxTextures) {
        id = 1;
        g_next_texture = 2;
    }

    texture_evict(id);
    SaturnTexture &tex = g_textures[id];
    memset(&tex, 0, sizeof(tex));
    tex.width = (uint16_t)((width > 0) ? width : 16);
    tex.height = (uint16_t)((height > 0) ? height : 16);
    tex.clut = &g_vdp1_parts.clut_base[id % kClutCount];
    tex.used = true;
    tex.cache_slot = -1;
    texture_palette_upload(tex, g_placeholder_palette);

    return id;
}

void
vg_saturn_texture_destroy(GLuint texture)
{
    if (texture < kMaxTextures) {
        texture_evict(texture);
        g_textures[texture].used = false;
    }
}

void
vg_saturn_texture_cache_reset(void)
{
    cache_reset_all();
    frame_cache_reset_all();
}

void
vg_saturn_texture_set_source_path(GLuint texture, const char *path)
{
    if ((texture == 0) || (texture >= kMaxTextures) || !g_textures[texture].used) {
        return;
    }

    SaturnTexture &tex = g_textures[texture];
    if (path == nullptr) {
        tex.path[0] = '\0';
    } else {
        strncpy(tex.path, path, sizeof(tex.path) - 1);
        tex.path[sizeof(tex.path) - 1] = '\0';
    }
    tex.skipped = path_is_suppressed_background(tex.path);
    tex.warned = false;
    if (tex.skipped) {
        texture_evict(texture);
    }
}

void
vg_saturn_texture_replace(GLuint texture, GLsizei width, GLsizei height,
                          const void *data, uint32_t data_size)
{
    if ((texture == 0) || (texture >= kMaxTextures) || !g_textures[texture].used) {
        return;
    }

    SaturnTexture &tex = g_textures[texture];
    if ((width <= 0) || (height <= 0)) {
        return;
    }

    tex.width = (uint16_t)width;
    tex.height = (uint16_t)height;
    frame_cache_evict_texture(texture);

    if (tex.skipped) {
        texture_evict(texture);
        return;
    }

    if (data != nullptr) {
        texture_upload_from_memory(texture, static_cast<const uint8_t *>(data), data_size);
    } else if (!texture_load_from_cd(texture)) {
        const GLuint placeholder = placeholder_texture_get();
        if (placeholder != texture) {
            tex.width = 16;
            tex.height = 16;
        }
    }
}

void
vg_saturn_draw_solid_quad(const vg_saturn_vertex_t *vertices,
                          float r, float g, float b, float a)
{
    if ((a <= 0.0f) || (vertices == nullptr)) {
        g_frame_quads_skipped++;
        g_frame_skip_alpha++;
        return;
    }
    g_frame_quads_in++;

    OrderedQuadVertex quad[4];
    quad_order_spatial(vertices, quad);

    float left = 0.0f;
    float top = 0.0f;
    float right = 0.0f;
    float bottom = 0.0f;
    if (!quad_bounds(quad, &left, &top, &right, &bottom) ||
        (right < 0.0f) || (bottom < 0.0f) ||
        (left > (float)(VG_SATURN_SCREEN_W - 1)) ||
        (top > (float)(VG_SATURN_SCREEN_H - 1))) {
        g_frame_quads_skipped++;
        g_frame_skip_bounds++;
        return;
    }

    debug_draw_log("solid", 0, 0, nullptr, 0, 0, 0, 0);

    vdp1_cmdt_t *cmdt = cmdt_next();
    if (cmdt == nullptr) {
        g_frame_quads_skipped++;
        g_frame_skip_cmdt++;
        return;
    }

    int16_vec2_t points[4];
    for (int i = 0; i < 4; i++) {
        points[i].x = round_to_i16(quad[i].x);
        points[i].y = round_to_i16(quad[i].y);
    }

    vdp1_cmdt_draw_mode_t mode = {};
    if (a < 0.99f) {
        mode.cc_mode = VDP1_CMDT_CC_HALF_TRANSPARENT;
    }

    vdp1_cmdt_polygon_set(cmdt);
    vdp1_cmdt_draw_mode_set(cmdt, mode);
    vdp1_cmdt_color_set(cmdt, rgb1555_from_float(r, g, b));
    vdp1_cmdt_vtx_set(cmdt, points);
    g_frame_quads_drawn++;
    g_frame_quads_distorted++;
}

void
vg_saturn_draw_textured_quad(GLuint texture, const vg_saturn_vertex_t *vertices,
                             float r, float g, float b, float a)
{
    const GLuint input_texture = texture;
    if (texture == 0) {
        vg_saturn_draw_solid_quad(vertices, r, g, b, a);
        return;
    }

    if ((a <= 0.0f) || (vertices == nullptr)) {
        g_frame_quads_skipped++;
        g_frame_skip_alpha++;
        return;
    }
    g_frame_quads_in++;

    if ((texture >= kMaxTextures) || !g_textures[texture].used ||
        g_textures[texture].skipped) {
        g_frame_quads_skipped++;
        g_frame_skip_texture++;
        return;
    }

    SaturnTexture &tex = g_textures[texture];
    const uint8_t *pixels = texture_pixels_get(texture);
    if (pixels == nullptr) {
        texture = placeholder_texture_get();
        pixels = texture_pixels_get(texture);
        if (pixels == nullptr) {
            g_frame_quads_skipped++;
            g_frame_skip_texture++;
            return;
        }
    }

    OrderedQuadVertex quad[4];
    quad_order_spatial(vertices, quad);

    float left = 0.0f;
    float top = 0.0f;
    float right = 0.0f;
    float bottom = 0.0f;
    if (!quad_bounds(quad, &left, &top, &right, &bottom) ||
        (right < 0.0f) || (bottom < 0.0f) ||
        (left > (float)(VG_SATURN_SCREEN_W - 1)) ||
        (top > (float)(VG_SATURN_SCREEN_H - 1))) {
        g_frame_quads_skipped++;
        g_frame_skip_bounds++;
        if (!g_frame_sample_valid) {
            g_frame_sample_valid = true;
            g_frame_sample_x = round_to_i16(left);
            g_frame_sample_y = round_to_i16(top);
            g_frame_sample_w = round_to_i16(right - left);
            g_frame_sample_h = round_to_i16(bottom - top);
            g_frame_sample_sw = 0;
            g_frame_sample_sh = 0;
        }
        return;
    }

    float min_u = quad[0].u;
    float max_u = quad[0].u;
    float min_v = quad[0].v;
    float max_v = quad[0].v;
    for (int i = 1; i < 4; i++) {
        if (quad[i].u < min_u) min_u = quad[i].u;
        if (quad[i].u > max_u) max_u = quad[i].u;
        if (quad[i].v < min_v) min_v = quad[i].v;
        if (quad[i].v > max_v) max_v = quad[i].v;
    }

    min_u = clampf(min_u, 0.0f, 1.0f);
    max_u = clampf(max_u, 0.0f, 1.0f);
    min_v = clampf(min_v, 0.0f, 1.0f);
    max_v = clampf(max_v, 0.0f, 1.0f);

    uint16_t sx = (uint16_t)(min_u * (float)tex.width);
    uint16_t sy = (uint16_t)(min_v * (float)tex.height);
    uint16_t ex = (uint16_t)((max_u * (float)tex.width) + 0.999f);
    uint16_t ey = (uint16_t)((max_v * (float)tex.height) + 0.999f);
    if (sx >= tex.width) sx = tex.width - 1;
    if (sy >= tex.height) sy = tex.height - 1;
    if (ex > tex.width) ex = tex.width;
    if (ey > tex.height) ey = tex.height;
    if (ex <= sx) ex = (uint16_t)(sx + 1);
    if (ey <= sy) ey = (uint16_t)(sy + 1);

    const uint16_t sw = (uint16_t)(ex - sx);
    const uint16_t sh = (uint16_t)(ey - sy);
    debug_draw_log("tex", input_texture, texture, &tex, sx, sy, sw, sh);
    const Vdp1FrameSlot *upload =
        sprite_frame_get_or_upload(texture, pixels, sx, sy, sw, sh);
    if (upload == nullptr) {
        g_frame_quads_skipped++;
        g_frame_skip_upload++;
        return;
    }

    vdp1_cmdt_t *cmdt = cmdt_next();
    if (cmdt == nullptr) {
        g_frame_quads_skipped++;
        g_frame_skip_cmdt++;
        return;
    }

    vdp1_cmdt_draw_mode_t mode = {};
    mode.color_mode = VDP1_CMDT_CM_CLUT_16;
    mode.trans_pixel_disable = false;
    mode.pre_clipping_disable = false;
    if (a < 0.99f) {
        mode.cc_mode = VDP1_CMDT_CC_HALF_TRANSPARENT;
    }

    const vdp1_cmdt_char_flip_t flip = quad_flip_get(quad);
    if (!g_frame_sample_valid) {
        g_frame_sample_valid = true;
        g_frame_sample_x = round_to_i16(left);
        g_frame_sample_y = round_to_i16(top);
        g_frame_sample_w = round_to_i16(right - left);
        g_frame_sample_h = round_to_i16(bottom - top);
        g_frame_sample_sw = sw;
        g_frame_sample_sh = sh;
    }
    if (quad_is_axis_aligned(quad)) {
        const int16_t x = round_to_i16(left);
        const int16_t y = round_to_i16(top);
        int16_t w = round_to_i16(right - left);
        int16_t h = round_to_i16(bottom - top);
        if (w <= 0) w = 1;
        if (h <= 0) h = 1;

        vdp1_cmdt_scaled_sprite_set(cmdt);
        vdp1_cmdt_draw_mode_set(cmdt, mode);
        vdp1_cmdt_color_mode1_set(cmdt, reinterpret_cast<vdp1_vram_t>(tex.clut));
        vdp1_cmdt_char_base_set(cmdt, reinterpret_cast<vdp1_vram_t>(upload->base));
        vdp1_cmdt_char_size_set(cmdt, upload->slot_w, upload->slot_h);
        vdp1_cmdt_char_flip_set(cmdt, flip);
        vdp1_cmdt_zoom_set(cmdt, VDP1_CMDT_ZOOM_POINT_UPPER_LEFT);
        vdp1_cmdt_vtx_zoom_point_set(cmdt, INT16_VEC2_INITIALIZER(x, y));
        vdp1_cmdt_vtx_zoom_display_set(cmdt, INT16_VEC2_INITIALIZER(w, h));
        g_frame_quads_scaled++;
    } else {
        int16_vec2_t points[4];
        for (int i = 0; i < 4; i++) {
            points[i].x = round_to_i16(quad[i].x);
            points[i].y = round_to_i16(quad[i].y);
        }

        vdp1_cmdt_distorted_sprite_set(cmdt);
        vdp1_cmdt_draw_mode_set(cmdt, mode);
        vdp1_cmdt_color_mode1_set(cmdt, reinterpret_cast<vdp1_vram_t>(tex.clut));
        vdp1_cmdt_char_base_set(cmdt, reinterpret_cast<vdp1_vram_t>(upload->base));
        vdp1_cmdt_char_size_set(cmdt, upload->slot_w, upload->slot_h);
        vdp1_cmdt_char_flip_set(cmdt, flip);
        vdp1_cmdt_vtx_set(cmdt, points);
        g_frame_quads_distorted++;
    }
    g_frame_quads_drawn++;

    (void)r;
    (void)g;
    (void)b;
}

void
vg_saturn_draw_line(float x0, float y0, float x1, float y1,
                    float r, float g, float b, float a)
{
    if (a <= 0.0f) {
        return;
    }

    vdp1_cmdt_t *cmdt = cmdt_next();
    if (cmdt == nullptr) {
        return;
    }

    int16_vec2_t points[4] = {};
    points[0].x = (int16_t)x0;
    points[0].y = (int16_t)y0;
    points[1].x = (int16_t)x1;
    points[1].y = (int16_t)y1;

    vdp1_cmdt_line_set(cmdt);
    vdp1_cmdt_draw_mode_t mode = {};
    vdp1_cmdt_draw_mode_set(cmdt, mode);
    vdp1_cmdt_color_set(cmdt, rgb1555_from_float(r, g, b));
    vdp1_cmdt_vtx_set(cmdt, points);
}
