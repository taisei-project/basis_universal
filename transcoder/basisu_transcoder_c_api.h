
#ifndef BASICU_TRANSCODER_C_API_H
#define BASICU_TRANSCODER_C_API_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum basist_texture_format {
    /*
     * Must correspond to basist::transcoder_texture_format
     */

    BASIST_FORMAT_ETC1_RGB = 0,
    BASIST_FORMAT_ETC2_RGBA = 1,
    BASIST_FORMAT_BC1_RGB = 2,
    BASIST_FORMAT_BC3_RGBA = 3,
    BASIST_FORMAT_BC4_R = 4,
    BASIST_FORMAT_BC5_RG = 5,
    BASIST_FORMAT_BC7_RGBA = 6,
    BASIST_FORMAT_PVRTC1_4_RGB = 8,
    BASIST_FORMAT_PVRTC1_4_RGBA = 9,
    BASIST_FORMAT_ASTC_4x4_RGBA = 10,
    BASIST_FORMAT_ATC_RGB = 11,
    BASIST_FORMAT_ATC_RGBA = 12,
    BASIST_FORMAT_FXT1_RGB = 17,
    BASIST_FORMAT_PVRTC2_4_RGB = 18,
    BASIST_FORMAT_PVRTC2_4_RGBA = 19,
    BASIST_FORMAT_ETC2_EAC_R11 = 20,
    BASIST_FORMAT_ETC2_EAC_RG11 = 21,
    BASIST_FORMAT_RGBA32 = 13,
    BASIST_FORMAT_RGB565 = 14,
    BASIST_FORMAT_BGR565 = 15,
    BASIST_FORMAT_RGBA4444 = 16,

    BASIST_NUM_FORMATS = 22,
} basist_texture_format;

typedef enum basisu_texture_format {
    /*
     * Must correspond to basisu::texture_format
     */

    BASISU_FORMAT_INVALID = -1,
    BASISU_FORMAT_ETC1,
    BASISU_FORMAT_ETC1S,
    BASISU_FORMAT_ETC2_RGB,
    BASISU_FORMAT_ETC2_RGBA,
    BASISU_FORMAT_ETC2_ALPHA,
    BASISU_FORMAT_BC1,
    BASISU_FORMAT_BC3,
    BASISU_FORMAT_BC4,
    BASISU_FORMAT_BC5,
    BASISU_FORMAT_BC7,
    BASISU_FORMAT_ASTC4x4,
    BASISU_FORMAT_PVRTC1_4_RGB,
    BASISU_FORMAT_PVRTC1_4_RGBA,
    BASISU_FORMAT_ATC_RGB,
    BASISU_FORMAT_ATC_RGBA_INTERPOLATED_ALPHA,
    BASISU_FORMAT_FXT1_RGB,
    BASISU_FORMAT_PVRTC2_4_RGBA,
    BASISU_FORMAT_ETC2_R11_EAC,
    BASISU_FORMAT_ETC2_RG11_EAC,
    BASISU_FORMAT_UASTC4x4,
    BASISU_FORMAT_BC1_NV,
    BASISU_FORMAT_BC1_AMD,
    BASISU_FORMAT_RGBA32,
    BASISU_FORMAT_RGB565,
    BASISU_FORMAT_BGR565,
    BASISU_FORMAT_RGBA4444,
    BASISU_FORMAT_ABGR4444
} basisu_texture_format;

typedef enum basist_texture_type {
    /*
     * Must correspond to basist::basis_texture_type
     */

    BASIST_TYPE_2D = 0,
    BASIST_TYPE_2D_ARRAY = 1,
    BASIST_TYPE_CUBEMAP_ARRAY = 2,
    BASIST_TYPE_VIDEO_FRAMES = 3,
    BASIST_TYPE_VOLUME = 4,

    BASIST_NUM_TYPES,
} basist_texture_type;

typedef enum basist_source_format {
    /*
     * Must correspond to basist::basis_tex_format
     */

    BASIST_SOURCE_ETC1S = 0,
    BASIST_SOURCE_UASTC4x4 = 1,
} basist_source_format;

typedef enum basist_decode_flag {
    BASIST_DECODE_PVRTC_DECODE_TO_NEXT_POW2 = 2,
    BASIST_DECODE_TRANSCODE_ALPHA_DATA_TO_OPAQUE_FORMATS = 4,
    BASIST_DECODE_BC1_FORBID_THREE_COLOR_BLOCKS = 8,
    BASIST_DECODE_OUTPUT_HAS_ALPHA_INDICES = 16,
    BASIST_DECODE_HIGH_QUALITY = 32,
} basist_decode_flag;

typedef struct basist_transcoder_s basist_transcoder;

typedef struct basist_data_s {
    void *data;
    uint32_t size;
} basist_data;

typedef struct basist_userdata {
    uint32_t userdata[2];
} basist_userdata;

typedef struct basist_image_level_desc_s {
    uint32_t orig_width;
    uint32_t orig_height;
    uint32_t total_blocks;
} basist_image_level_desc;

typedef struct basist_slice_info_s {
    /*
     * Must correspond to basist::basisu_slice_info
     */

    uint32_t orig_width;
    uint32_t orig_height;

    uint32_t width;
    uint32_t height;

    uint32_t num_blocks_x;
    uint32_t num_blocks_y;
    uint32_t total_blocks;

    uint32_t compressed_size;

    uint32_t slice_index;	// the slice index in the .basis file
    uint32_t image_index;	// the source image index originally provided to the encoder
    uint32_t level_index;	// the mipmap level within this image

    uint32_t unpacked_slice_crc16;

    bool alpha_flag;		// true if the slice has alpha data
    bool iframe_flag;		// true if the slice is an I-Frame
} basist_slice_info;

typedef struct basist_image_info_s {
    /*
     * Must correspond to basist::basisu_image_info
     */

    uint32_t image_index;
    uint32_t total_levels;

    uint32_t orig_width;
    uint32_t orig_height;

    uint32_t width;
    uint32_t height;

    uint32_t num_blocks_x;
    uint32_t num_blocks_y;
    uint32_t total_blocks;

    uint32_t first_slice_index;

    bool alpha_flag;
    bool iframe_flag;
} basist_image_info;

typedef struct basist_image_level_info_s {
    /*
     * Must correspond to basist::basisu_image_level_info
     */

    uint32_t image_index;
    uint32_t level_index;

    uint32_t orig_width;
    uint32_t orig_height;

    uint32_t width;
    uint32_t height;

    uint32_t num_blocks_x;
    uint32_t num_blocks_y;
    uint32_t total_blocks;

    uint32_t first_slice_index;

    bool alpha_flag;
    bool iframe_flag;
} basist_image_level_info;

typedef struct basist_file_info_s {
    /*
     * Based on basist::basisu_file_info, but NOT binary compatible!
     */

    uint32_t version;
    uint32_t total_header_size;

    uint32_t total_selectors;
    uint32_t selector_codebook_size;

    uint32_t total_endpoints;
    uint32_t endpoint_codebook_size;

    uint32_t tables_size;
    uint32_t slices_size;

    basist_texture_type tex_type;
    uint32_t us_per_frame;

    uint32_t total_slices;
    uint32_t total_images;

    basist_userdata userdata;

    basist_source_format source_format;

    bool y_flipped;
    bool etc1s;
    bool has_alpha_slices;
} basist_file_info;

typedef struct basist_transcoder_state_s basist_transcoder_state;

typedef struct basist_transcode_level_params_s {
    void *output_blocks;
    basist_transcoder_state *transcoder_state;  // TODO
    uint32_t image_index;
    uint32_t level_index;
    uint32_t output_blocks_size;  // in blocks or pixels
    uint32_t output_row_pitch;  // in blocks or pixels
    uint32_t output_rows;  // in blocks or pixels
    uint32_t decode_flags;  // basist_decode_flag
    basist_texture_format format;
} basist_transcode_level_params;

#ifndef BASIST_API
#define BASIST_API
#endif

BASIST_API uint32_t basist_get_bytes_per_block_or_pixel(basist_texture_format fmt);
BASIST_API const char *basist_get_format_name(basist_texture_format fmt);
BASIST_API bool basist_format_has_alpha(basist_texture_format fmt);
BASIST_API basisu_texture_format basist_get_basisu_texture_format(basist_texture_format fmt);
BASIST_API const char *basist_get_texture_type_name(basist_texture_type tex_type);
BASIST_API bool basist_is_format_supported(basist_texture_format fmt, basist_source_format src_fmt);
BASIST_API bool basist_is_format_uncompressed(basist_texture_format fmt);
BASIST_API uint32_t basist_get_uncompressed_bytes_per_pixel(basist_texture_format fmt);
BASIST_API uint32_t basist_get_block_width(basist_texture_format fmt);
BASIST_API uint32_t basist_get_block_height(basist_texture_format fmt);

BASIST_API basist_transcoder *basist_transcoder_create(void);
BASIST_API void basist_transcoder_destroy(basist_transcoder *tc);
BASIST_API void basist_transcoder_set_data(basist_transcoder *tc, basist_data data);
BASIST_API basist_data basist_transcoder_get_data(basist_transcoder *tc);
BASIST_API bool basist_transcoder_validate_file_checksums(basist_transcoder *tc, bool full_validation);
BASIST_API bool basist_transcoder_validate_header(basist_transcoder *tc);
BASIST_API basist_texture_type basist_transcoder_get_texture_type(basist_transcoder *tc);
BASIST_API bool basist_transcoder_get_userdata(basist_transcoder *tc, basist_userdata *out_udata);
BASIST_API uint32_t basist_transcoder_get_total_images(basist_transcoder *tc);
BASIST_API basist_source_format basist_transcoder_get_source_format(basist_transcoder *tc);
BASIST_API uint32_t basist_transcoder_get_total_image_levels(basist_transcoder *tc, uint32_t image_index);
BASIST_API bool basist_transcoder_get_image_level_desc(basist_transcoder *tc, uint32_t image_index, uint32_t level_index, basist_image_level_desc *out_desc);
BASIST_API bool basist_transcoder_get_image_info(basist_transcoder *tc, uint32_t image_index, basist_image_info *out_image_info);
BASIST_API bool basist_transcoder_get_image_level_info(basist_transcoder *tc, uint32_t image_index, uint32_t level_index, basist_image_level_info *out_level_info);
BASIST_API bool basist_transcoder_get_slice_info(basist_transcoder *tc, uint32_t slice_index, basist_slice_info *out_slice_info);
BASIST_API bool basist_transcoder_get_file_info(basist_transcoder *tc, basist_file_info *out_file_info);
BASIST_API bool basist_transcoder_start_transcoding(basist_transcoder *tc);
BASIST_API bool basist_transcoder_stop_transcoding(basist_transcoder *tc);
BASIST_API bool basist_transcoder_get_ready_to_transcode(basist_transcoder *tc);
BASIST_API void basist_init_transcode_level_params(basist_transcode_level_params *params);
BASIST_API bool basist_transcoder_transcode_image_level(basist_transcoder *tc, const basist_transcode_level_params *params);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
