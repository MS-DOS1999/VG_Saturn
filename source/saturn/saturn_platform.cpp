#include "saturn_platform.h"
#include "saturn_debug.h"

#include <stdio.h>
#include <string.h>
#include <yaul.h>

static constexpr uint32_t kMaxCmdts = 2048;
static constexpr uint32_t kMaxTextures = 512;
static constexpr uint32_t kTextureBudget = 0x00054000;
static constexpr uint32_t kClutCount = 512;
static constexpr uint32_t kFrameUploadMax = 384;
static constexpr uint32_t kCacheSlotBytes = 0x00090000;
static constexpr uint32_t kMaxCacheSlots = 7;

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
    uint32_t last_used;
    GLuint texture;
    bool used;
};

struct FrameUpload {
    uint8_t *base;
    uint32_t bytes;
    GLuint texture;
    uint16_t sx;
    uint16_t sy;
    uint16_t sw;
    uint16_t sh;
    uint16_t slot_w;
    bool used;
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
static FrameUpload g_frame_uploads[kFrameUploadMax];
static uint32_t g_frame_upload_count;
static SaturnTexture g_textures[kMaxTextures];
static CacheSlot g_cache_slots[kMaxCacheSlots];
static uint32_t g_cache_slot_count;
static uint32_t g_cache_tick;
static uint32_t g_next_texture = 1;
static volatile uint64_t g_frame_count;
static smpc_peripheral_digital_t g_digital[2];
static bool g_inited;
static bool g_warned_no_cart;
static uint32_t g_debug_last_cmdts;
static uint32_t g_debug_last_uploads;
static uint32_t g_debug_last_upload_bytes;

static uint8_t g_placeholder_pixels[(16 * 16) / 2];
static uint16_t g_placeholder_palette[16];

static vdp1_cmdt_t *cmdt_next(void);

static void
debug_marker_draw(void)
{
    vdp1_cmdt_t *cmdt = cmdt_next();
    if (cmdt == nullptr) {
        return;
    }

    int16_vec2_t points[4] = {};
    points[0].x = 4;
    points[0].y = 4;
    points[1].x = 84;
    points[1].y = 4;

    vdp1_cmdt_line_set(cmdt);
    vdp1_cmdt_color_set(cmdt, RGB1555(1, 0, 31, 0));
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
    rgb1555_t out;
    out.raw = (uint16_t)(0x8000 | (ri << 10) | (gi << 5) | bi);
    return out;
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

static bool
path_is_suppressed_background(const char *path)
{
    if (path == nullptr) {
        return false;
    }

    return (strstr(path, "verdict/bgs/") != nullptr) ||
           (strstr(path, "verdict\\bgs\\") != nullptr) ||
           (strstr(path, "verdict/title/bg") != nullptr) ||
           (strstr(path, "verdict\\title\\bg") != nullptr);
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
    g_frame_vram_cursor = g_frame_vram_base;
    g_frame_upload_count = 0;
    g_debug_last_upload_bytes = 0;
    memset(g_frame_uploads, 0, sizeof(g_frame_uploads));
}

static void
cache_init(void)
{
    void *cart = dram_cart_area_get();
    const size_t cart_size = dram_cart_size_get();
    g_cache_slot_count = 0;
    memset(g_cache_slots, 0, sizeof(g_cache_slots));

    if ((cart == nullptr) || (cart_size < kCacheSlotBytes)) {
        g_warned_no_cart = true;
        return;
    }

    uint32_t slots = (uint32_t)(cart_size / kCacheSlotBytes);
    if (slots > kMaxCacheSlots) {
        slots = kMaxCacheSlots;
    }

    uint8_t *base = static_cast<uint8_t *>(cart);
    for (uint32_t i = 0; i < slots; i++) {
        g_cache_slots[i].base = base + (i * kCacheSlotBytes);
    }
    g_cache_slot_count = slots;
}

static void
texture_evict(GLuint texture)
{
    if (texture >= kMaxTextures) {
        return;
    }

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

static int
cache_slot_acquire(GLuint texture, uint32_t bytes)
{
    if ((g_cache_slot_count == 0) || (bytes > kCacheSlotBytes)) {
        return -1;
    }

    SaturnTexture &tex = g_textures[texture];
    if ((tex.cache_slot >= 0) && ((uint32_t)tex.cache_slot < g_cache_slot_count)) {
        CacheSlot &slot = g_cache_slots[tex.cache_slot];
        if (slot.texture == texture) {
            slot.last_used = ++g_cache_tick;
            slot.bytes = bytes;
            return tex.cache_slot;
        }
    }

    int selected = -1;
    for (uint32_t i = 0; i < g_cache_slot_count; i++) {
        if (!g_cache_slots[i].used) {
            selected = (int)i;
            break;
        }
    }

    if (selected < 0) {
        uint32_t oldest = 0xFFFFFFFFU;
        for (uint32_t i = 0; i < g_cache_slot_count; i++) {
            if (g_cache_slots[i].last_used < oldest) {
                oldest = g_cache_slots[i].last_used;
                selected = (int)i;
            }
        }
    }

    if (selected < 0) {
        return -1;
    }

    CacheSlot &slot = g_cache_slots[selected];
    if (slot.used && (slot.texture > 0) && (slot.texture < kMaxTextures)) {
        SaturnTexture &old_tex = g_textures[slot.texture];
        old_tex.resident = false;
        old_tex.cache_slot = -1;
    }

    slot.used = true;
    slot.texture = texture;
    slot.bytes = bytes;
    slot.last_used = ++g_cache_tick;
    tex.cache_slot = selected;
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
            dbgio_printf("No ext RAM slot for tex %lu (%lu bytes)\n",
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

    FILE *file = fopen(tex.path, "rb");
    if (file == nullptr) {
        if (!tex.warned) {
            dbgio_printf("Texture CD open failed: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    SatTextureHeader header;
    uint16_t palette[16];
    if ((fread(&header, sizeof(header), 1, file) != 1) ||
        (memcmp(header.magic, "VG4P", 4) != 0) ||
        (header.width == 0) || (header.height == 0) ||
        (header.data_size == 0) ||
        (fread(palette, sizeof(palette), 1, file) != 1)) {
        fclose(file);
        if (!tex.warned) {
            dbgio_printf("Texture CD header invalid: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    if (header.data_size > kCacheSlotBytes) {
        fclose(file);
        if (!tex.warned) {
            dbgio_printf("Texture too large for ext slot: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    const int slot_index = cache_slot_acquire(texture, header.data_size);
    if (slot_index < 0) {
        fclose(file);
        if (!tex.warned) {
            dbgio_printf("No ext RAM slot for: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    CacheSlot &slot = g_cache_slots[slot_index];
    if (fread(slot.base, header.data_size, 1, file) != 1) {
        fclose(file);
        texture_evict(texture);
        if (!tex.warned) {
            dbgio_printf("Texture CD read failed: %s\n", tex.path);
            tex.warned = true;
        }
        return false;
    }

    fclose(file);
    tex.width = header.width;
    tex.height = header.height;
    tex.data_bytes = header.data_size;
    tex.resident = true;
    tex.warned = false;
    texture_palette_upload(tex, palette);
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

static FrameUpload *
frame_upload_get(GLuint texture, const uint8_t *pixels, uint16_t sx,
                 uint16_t sy, uint16_t sw, uint16_t sh)
{
    SaturnTexture &tex = g_textures[texture];
    for (uint32_t i = 0; i < g_frame_upload_count; i++) {
        FrameUpload &upload = g_frame_uploads[i];
        if (upload.used && (upload.texture == texture) && (upload.sx == sx) &&
            (upload.sy == sy) && (upload.sw == sw) && (upload.sh == sh)) {
            return &upload;
        }
    }

    if (g_frame_upload_count >= kFrameUploadMax) {
        if (!tex.warned) {
            dbgio_printf("VDP1 frame upload table full\n");
            tex.warned = true;
        }
        return nullptr;
    }

    const uint16_t slot_w = align8_u16(sw);
    const uint32_t row_bytes = slot_w >> 1;
    const uint32_t bytes = (row_bytes * sh + 7U) & ~7U;
    if ((bytes == 0) || ((g_frame_vram_cursor + bytes) > g_frame_vram_end)) {
        if (!tex.warned) {
            dbgio_printf("VDP1 frame VRAM full (%lux%lu)\n",
                         (uint32_t)sw, (uint32_t)sh);
            tex.warned = true;
        }
        return nullptr;
    }

    FrameUpload &upload = g_frame_uploads[g_frame_upload_count++];
    upload.base = g_frame_vram_cursor;
    upload.bytes = bytes;
    upload.texture = texture;
    upload.sx = sx;
    upload.sy = sy;
    upload.sw = sw;
    upload.sh = sh;
    upload.slot_w = slot_w;
    upload.used = true;
    g_frame_vram_cursor += bytes;
    g_debug_last_upload_bytes += bytes;

    for (uint16_t y = 0; y < sh; y++) {
        uint8_t *dst = upload.base + ((uint32_t)y * row_bytes);
        for (uint16_t x = 0; x < slot_w; x += 2) {
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

    return &upload;
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
    dram_cart_init();

    vdp2_tvmd_display_res_set(VDP2_TVMD_INTERLACE_NONE, VDP2_TVMD_HORZ_NORMAL_A,
                              VDP2_TVMD_VERT_240);
    vdp2_scrn_back_color_set(VDP2_VRAM_ADDR(3, 0x01FFFE),
                             RGB1555(1, 0, 4, 0));
    vdp2_sprite_priority_set(0, 7);
    vdp1_env_default_set();
    vdp2_tvmd_display_set();
    vdp_sync_vblank_out_set(vblank_out_handler, nullptr);

    vdp1_vram_partitions_set(kMaxCmdts, kTextureBudget, 64, kClutCount);
    vdp1_vram_partitions_get(&g_vdp1_parts);
    g_frame_vram_base = static_cast<uint8_t *>(g_vdp1_parts.texture_base);
    g_frame_vram_end = g_frame_vram_base + g_vdp1_parts.texture_size;
    memset(g_textures, 0, sizeof(g_textures));
    for (uint32_t i = 0; i < kMaxTextures; i++) {
        g_textures[i].cache_slot = -1;
    }
    frame_uploads_reset();
    cache_init();

    g_cmdt_list = vdp1_cmdt_list_alloc(kMaxCmdts);
    cmdt_header_set();

    dbgio_init();
    dbgio_dev_default_init(DBGIO_DEV_VDP2_ASYNC);
    dbgio_dev_font_load();
    if (g_warned_no_cart) {
        dbgio_printf("4MB RAM cart missing; sprite streaming disabled\n");
        vg_saturn_debug_stage(19, "platform_init_no_cart");
    } else {
        dbgio_printf("Ext RAM cache slots: %lu\n", g_cache_slot_count);
        vg_saturn_debug_stage(18, "platform_init_cart_ok");
    }

    vdp2_sync();
    vdp2_sync_wait();
    vg_saturn_debug_stage(20, "platform_init_done");
}

void
vg_saturn_frame_begin(void)
{
    vg_saturn_init();
    cmdt_header_set();
    frame_uploads_reset();
}

void
vg_saturn_frame_end(void)
{
    vg_saturn_init();

    if (g_cmdt_index >= kMaxCmdts) {
        g_cmdt_index = kMaxCmdts - 1;
    }

    debug_marker_draw();

    vdp1_cmdt_end_set(&g_cmdt_list->cmdts[g_cmdt_index]);
    g_cmdt_list->count = (uint16_t)(g_cmdt_index + 1);
    g_debug_last_cmdts = g_cmdt_index + 1;
    g_debug_last_uploads = g_frame_upload_count;

    vdp1_sync_cmdt_list_put(g_cmdt_list, 0);
    vdp1_sync_render();
    vdp1_sync();
    vdp1_sync_wait();

    dbgio_flush();
    if ((g_frame_count % 60) == 0) {
        dbgio_printf("[VG] frame=%lu cmdts=%lu uploads=%lu upload_bytes=%lu cache_slots=%lu\n",
                     (uint32_t)g_frame_count, g_debug_last_cmdts,
                     g_debug_last_uploads, g_debug_last_upload_bytes,
                     g_cache_slot_count);
        dbgio_flush();
        vg_saturn_debug_frame(g_frame_count, g_debug_last_cmdts,
                              g_debug_last_uploads, g_debug_last_upload_bytes,
                              g_cache_slot_count);
    }
    vdp2_sync();
    vdp2_sync_wait();
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
vg_saturn_draw_textured_quad(GLuint texture, const vg_saturn_vertex_t *vertices,
                             float r, float g, float b, float a)
{
    if ((a <= 0.0f) || (vertices == nullptr)) {
        return;
    }

    if ((texture == 0) || (texture >= kMaxTextures) || !g_textures[texture].used ||
        g_textures[texture].skipped) {
        texture = placeholder_texture_get();
    }

    SaturnTexture &tex = g_textures[texture];
    const uint8_t *pixels = texture_pixels_get(texture);
    if (pixels == nullptr) {
        texture = placeholder_texture_get();
        pixels = texture_pixels_get(texture);
        if (pixels == nullptr) {
            return;
        }
    }

    float min_u = vertices[0].u;
    float max_u = vertices[0].u;
    float min_v = vertices[0].v;
    float max_v = vertices[0].v;
    for (int i = 1; i < 4; i++) {
        if (vertices[i].u < min_u) min_u = vertices[i].u;
        if (vertices[i].u > max_u) max_u = vertices[i].u;
        if (vertices[i].v < min_v) min_v = vertices[i].v;
        if (vertices[i].v > max_v) max_v = vertices[i].v;
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
    FrameUpload *upload = frame_upload_get(texture, pixels, sx, sy, sw, sh);
    if (upload == nullptr) {
        return;
    }

    vdp1_cmdt_t *cmdt = cmdt_next();
    if (cmdt == nullptr) {
        return;
    }

    int16_vec2_t points[4];
    for (int i = 0; i < 4; i++) {
        points[i].x = (int16_t)vertices[i].x;
        points[i].y = (int16_t)vertices[i].y;
    }

    vdp1_cmdt_distorted_sprite_set(cmdt);
    vdp1_cmdt_draw_mode_t mode = {};
    mode.color_mode = VDP1_CMDT_CM_CLUT_16;
    mode.trans_pixel_disable = false;
    mode.pre_clipping_disable = true;
    if (a < 0.99f) {
        mode.cc_mode = VDP1_CMDT_CC_HALF_TRANSPARENT;
    }
    vdp1_cmdt_draw_mode_set(cmdt, mode);
    vdp1_cmdt_color_mode1_set(cmdt, reinterpret_cast<vdp1_vram_t>(tex.clut));
    vdp1_cmdt_char_base_set(cmdt, reinterpret_cast<vdp1_vram_t>(upload->base));
    vdp1_cmdt_char_size_set(cmdt, upload->slot_w, upload->sh);

    vdp1_cmdt_char_flip_t flip = VDP1_CMDT_CHAR_FLIP_NONE;
    if ((vertices[0].u > vertices[1].u) || (vertices[3].u > vertices[2].u)) {
        flip = (vdp1_cmdt_char_flip_t)(flip | VDP1_CMDT_CHAR_FLIP_H);
    }
    if ((vertices[0].v > vertices[3].v) || (vertices[1].v > vertices[2].v)) {
        flip = (vdp1_cmdt_char_flip_t)(flip | VDP1_CMDT_CHAR_FLIP_V);
    }
    vdp1_cmdt_char_flip_set(cmdt, flip);
    vdp1_cmdt_vtx_set(cmdt, points);

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
    vdp1_cmdt_color_set(cmdt, rgb1555_from_float(r, g, b));
    vdp1_cmdt_vtx_set(cmdt, points);
}
