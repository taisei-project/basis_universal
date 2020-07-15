
#include "basisu_transcoder_c_api.h"
#include "basisu_transcoder.h"

#include <memory>
#include <mutex>

// BEGIN assertions

#define STATIC_ASSERT(a) static_assert(a, #a)
#define ASSERT_ENUM(c_enum, cpp_enum) STATIC_ASSERT(c_enum == static_cast<int>(cpp_enum))
#define ASSERT_BASIST_FORMAT(fmt) \
    ASSERT_ENUM(BASIST_FORMAT_##fmt, basist::transcoder_texture_format::cTF##fmt)
#define ASSERT_BASISU_FORMAT(fmt) \
    ASSERT_ENUM(BASISU_FORMAT_##fmt, basisu::texture_format::c##fmt)

ASSERT_BASIST_FORMAT(ETC1_RGB);
ASSERT_BASIST_FORMAT(ETC2_RGBA);
ASSERT_BASIST_FORMAT(BC1_RGB);
ASSERT_BASIST_FORMAT(BC3_RGBA);
ASSERT_BASIST_FORMAT(BC4_R);
ASSERT_BASIST_FORMAT(BC5_RG);
ASSERT_BASIST_FORMAT(BC7_RGBA);
ASSERT_BASIST_FORMAT(PVRTC1_4_RGB);
ASSERT_BASIST_FORMAT(PVRTC1_4_RGBA);
ASSERT_BASIST_FORMAT(ASTC_4x4_RGBA);
ASSERT_BASIST_FORMAT(ATC_RGB);
ASSERT_BASIST_FORMAT(ATC_RGBA);
ASSERT_BASIST_FORMAT(ASTC_4x4_RGBA);
ASSERT_BASIST_FORMAT(FXT1_RGB);
ASSERT_BASIST_FORMAT(PVRTC2_4_RGB);
ASSERT_BASIST_FORMAT(PVRTC2_4_RGBA);
ASSERT_BASIST_FORMAT(ETC2_EAC_R11);
ASSERT_BASIST_FORMAT(ETC2_EAC_RG11);
ASSERT_BASIST_FORMAT(RGBA32);
ASSERT_BASIST_FORMAT(RGB565);
ASSERT_BASIST_FORMAT(BGR565);
ASSERT_BASIST_FORMAT(RGBA4444);
ASSERT_ENUM(BASIST_NUM_FORMATS, basist::transcoder_texture_format::cTFTotalTextureFormats);

ASSERT_BASISU_FORMAT(ETC1);
ASSERT_BASISU_FORMAT(ETC1S);
ASSERT_BASISU_FORMAT(ETC2_RGB);
ASSERT_BASISU_FORMAT(ETC2_RGBA);
ASSERT_BASISU_FORMAT(ETC2_ALPHA);
ASSERT_BASISU_FORMAT(BC1);
ASSERT_BASISU_FORMAT(BC3);
ASSERT_BASISU_FORMAT(BC4);
ASSERT_BASISU_FORMAT(BC5);
ASSERT_BASISU_FORMAT(BC7);
ASSERT_BASISU_FORMAT(ASTC4x4);
ASSERT_BASISU_FORMAT(PVRTC1_4_RGB);
ASSERT_BASISU_FORMAT(PVRTC1_4_RGBA);
ASSERT_BASISU_FORMAT(ATC_RGB);
ASSERT_BASISU_FORMAT(ATC_RGBA_INTERPOLATED_ALPHA);
ASSERT_BASISU_FORMAT(FXT1_RGB);
ASSERT_BASISU_FORMAT(PVRTC2_4_RGBA);
ASSERT_BASISU_FORMAT(ETC2_R11_EAC);
ASSERT_BASISU_FORMAT(ETC2_RG11_EAC);
ASSERT_BASISU_FORMAT(UASTC4x4);
ASSERT_BASISU_FORMAT(BC1_NV);
ASSERT_BASISU_FORMAT(BC1_AMD);
ASSERT_BASISU_FORMAT(RGBA32);
ASSERT_BASISU_FORMAT(RGB565);
ASSERT_BASISU_FORMAT(BGR565);
ASSERT_BASISU_FORMAT(RGBA4444);
ASSERT_BASISU_FORMAT(ABGR4444);

ASSERT_ENUM(BASIST_TYPE_2D, basist::basis_texture_type::cBASISTexType2D);
ASSERT_ENUM(BASIST_TYPE_2D_ARRAY, basist::basis_texture_type::cBASISTexType2DArray);
ASSERT_ENUM(BASIST_TYPE_CUBEMAP_ARRAY, basist::basis_texture_type::cBASISTexTypeCubemapArray);
ASSERT_ENUM(BASIST_TYPE_VIDEO_FRAMES, basist::basis_texture_type::cBASISTexTypeVideoFrames);
ASSERT_ENUM(BASIST_TYPE_VOLUME, basist::basis_texture_type::cBASISTexTypeVolume);
ASSERT_ENUM(BASIST_NUM_TYPES, basist::basis_texture_type::cBASISTexTypeTotal);

ASSERT_ENUM(BASIST_SOURCE_ETC1S, basist::basis_tex_format::cETC1S);
ASSERT_ENUM(BASIST_SOURCE_UASTC4x4, basist::basis_tex_format::cUASTC4x4);

STATIC_ASSERT(sizeof(basist_slice_info) == sizeof(basist::basisu_slice_info));
STATIC_ASSERT(offsetof(basist_slice_info, orig_width) == offsetof(basist::basisu_slice_info, m_orig_width));
STATIC_ASSERT(offsetof(basist_slice_info, orig_height) == offsetof(basist::basisu_slice_info, m_orig_height));
STATIC_ASSERT(offsetof(basist_slice_info, width) == offsetof(basist::basisu_slice_info, m_width));
STATIC_ASSERT(offsetof(basist_slice_info, height) == offsetof(basist::basisu_slice_info, m_height));
STATIC_ASSERT(offsetof(basist_slice_info, num_blocks_x) == offsetof(basist::basisu_slice_info, m_num_blocks_x));
STATIC_ASSERT(offsetof(basist_slice_info, num_blocks_y) == offsetof(basist::basisu_slice_info, m_num_blocks_y));
STATIC_ASSERT(offsetof(basist_slice_info, total_blocks) == offsetof(basist::basisu_slice_info, m_total_blocks));
STATIC_ASSERT(offsetof(basist_slice_info, slice_index) == offsetof(basist::basisu_slice_info, m_slice_index));
STATIC_ASSERT(offsetof(basist_slice_info, image_index) == offsetof(basist::basisu_slice_info, m_image_index));
STATIC_ASSERT(offsetof(basist_slice_info, level_index) == offsetof(basist::basisu_slice_info, m_level_index));
STATIC_ASSERT(offsetof(basist_slice_info, alpha_flag) == offsetof(basist::basisu_slice_info, m_alpha_flag));
STATIC_ASSERT(offsetof(basist_slice_info, iframe_flag) == offsetof(basist::basisu_slice_info, m_iframe_flag));

STATIC_ASSERT(sizeof(basist_image_info) == sizeof(basist::basisu_image_info));
STATIC_ASSERT(offsetof(basist_image_info, image_index) == offsetof(basist::basisu_image_info, m_image_index));
STATIC_ASSERT(offsetof(basist_image_info, total_levels) == offsetof(basist::basisu_image_info, m_total_levels));
STATIC_ASSERT(offsetof(basist_image_info, orig_width) == offsetof(basist::basisu_image_info, m_orig_width));
STATIC_ASSERT(offsetof(basist_image_info, orig_height) == offsetof(basist::basisu_image_info, m_orig_height));
STATIC_ASSERT(offsetof(basist_image_info, width) == offsetof(basist::basisu_image_info, m_width));
STATIC_ASSERT(offsetof(basist_image_info, height) == offsetof(basist::basisu_image_info, m_height));
STATIC_ASSERT(offsetof(basist_image_info, num_blocks_x) == offsetof(basist::basisu_image_info, m_num_blocks_x));
STATIC_ASSERT(offsetof(basist_image_info, num_blocks_y) == offsetof(basist::basisu_image_info, m_num_blocks_y));
STATIC_ASSERT(offsetof(basist_image_info, total_blocks) == offsetof(basist::basisu_image_info, m_total_blocks));
STATIC_ASSERT(offsetof(basist_image_info, first_slice_index) == offsetof(basist::basisu_image_info, m_first_slice_index));
STATIC_ASSERT(offsetof(basist_image_info, alpha_flag) == offsetof(basist::basisu_image_info, m_alpha_flag));
STATIC_ASSERT(offsetof(basist_image_info, iframe_flag) == offsetof(basist::basisu_image_info, m_iframe_flag));

STATIC_ASSERT(sizeof(basist_image_level_info) == sizeof(basist::basisu_image_level_info));
STATIC_ASSERT(offsetof(basist_image_level_info, image_index) == offsetof(basist::basisu_image_level_info, m_image_index));
STATIC_ASSERT(offsetof(basist_image_level_info, level_index) == offsetof(basist::basisu_image_level_info, m_level_index));
STATIC_ASSERT(offsetof(basist_image_level_info, orig_width) == offsetof(basist::basisu_image_level_info, m_orig_width));
STATIC_ASSERT(offsetof(basist_image_level_info, orig_height) == offsetof(basist::basisu_image_level_info, m_orig_height));
STATIC_ASSERT(offsetof(basist_image_level_info, width) == offsetof(basist::basisu_image_level_info, m_width));
STATIC_ASSERT(offsetof(basist_image_level_info, height) == offsetof(basist::basisu_image_level_info, m_height));
STATIC_ASSERT(offsetof(basist_image_level_info, num_blocks_x) == offsetof(basist::basisu_image_level_info, m_num_blocks_x));
STATIC_ASSERT(offsetof(basist_image_level_info, num_blocks_y) == offsetof(basist::basisu_image_level_info, m_num_blocks_y));
STATIC_ASSERT(offsetof(basist_image_level_info, total_blocks) == offsetof(basist::basisu_image_level_info, m_total_blocks));
STATIC_ASSERT(offsetof(basist_image_level_info, first_slice_index) == offsetof(basist::basisu_image_level_info, m_first_slice_index));
STATIC_ASSERT(offsetof(basist_image_level_info, alpha_flag) == offsetof(basist::basisu_image_level_info, m_alpha_flag));
STATIC_ASSERT(offsetof(basist_image_level_info, iframe_flag) == offsetof(basist::basisu_image_level_info, m_iframe_flag));

ASSERT_ENUM(BASIST_DECODE_PVRTC_DECODE_TO_NEXT_POW2, basist::cDecodeFlagsPVRTCDecodeToNextPow2);
ASSERT_ENUM(BASIST_DECODE_TRANSCODE_ALPHA_DATA_TO_OPAQUE_FORMATS, basist::cDecodeFlagsTranscodeAlphaDataToOpaqueFormats);
ASSERT_ENUM(BASIST_DECODE_BC1_FORBID_THREE_COLOR_BLOCKS, basist::cDecodeFlagsBC1ForbidThreeColorBlocks);
ASSERT_ENUM(BASIST_DECODE_OUTPUT_HAS_ALPHA_INDICES, basist::cDecodeFlagsOutputHasAlphaIndices);
ASSERT_ENUM(BASIST_DECODE_HIGH_QUALITY, basist::cDecodeFlagsHighQuality);

// END assertions

static struct G {
    std::once_flag init_flag;
    std::unique_ptr<basist::etc1_global_selector_codebook> sel_codebook;

    void init() {
        std::call_once(init_flag, [this]() {
            basist::basisu_transcoder_init();
            sel_codebook = std::make_unique<basist::etc1_global_selector_codebook>(basist::g_global_selector_cb_size, basist::g_global_selector_cb);
        });
    }
} G;

struct basist_transcoder_s {
    std::unique_ptr<basist::basisu_transcoder> tc;
    basist_data data;
};

extern "C" {

uint32_t basist_get_bytes_per_block_or_pixel(basist_texture_format fmt) {
    return basist::basis_get_bytes_per_block_or_pixel(static_cast<basist::transcoder_texture_format>(fmt));
}

const char *basist_get_format_name(basist_texture_format fmt) {
    return basist::basis_get_format_name(static_cast<basist::transcoder_texture_format>(fmt));
}

bool basist_format_has_alpha(basist_texture_format fmt) {
    return basist::basis_transcoder_format_has_alpha(static_cast<basist::transcoder_texture_format>(fmt));
}

basisu_texture_format basist_get_basisu_texture_format(basist_texture_format fmt) {
    return static_cast<basisu_texture_format>(
        basist::basis_get_basisu_texture_format(static_cast<basist::transcoder_texture_format>(fmt))
    );
}

const char *basist_get_texture_type_name(basist_texture_type tex_type) {
    return basist::basis_get_texture_type_name(static_cast<basist::basis_texture_type>(tex_type));
}

bool basist_is_format_supported(basist_texture_format fmt, basist_source_format src_fmt) {
    return basist::basis_is_format_supported(
        static_cast<basist::transcoder_texture_format>(fmt),
        static_cast<basist::basis_tex_format>(src_fmt)
    );
}

bool basist_is_format_uncompressed(basist_texture_format tex_type) {
    return basist::basis_transcoder_format_is_uncompressed(static_cast<basist::transcoder_texture_format>(tex_type));
}

uint32_t basist_get_uncompressed_bytes_per_pixel(basist_texture_format fmt) {
    return basist::basis_get_uncompressed_bytes_per_pixel(static_cast<basist::transcoder_texture_format>(fmt));
}

uint32_t basist_get_block_width(basist_texture_format fmt) {
    return basist::basis_get_block_width(static_cast<basist::transcoder_texture_format>(fmt));
}

uint32_t basist_get_block_height(basist_texture_format fmt) {
    return basist::basis_get_block_height(static_cast<basist::transcoder_texture_format>(fmt));
}

basist_transcoder *basist_transcoder_create(void) {
    G.init();
    auto tc = new basist_transcoder;
    tc->tc = std::make_unique<basist::basisu_transcoder>(G.sel_codebook.get());
    tc->data.data = nullptr;
    tc->data.size = 0;
    return tc;
}

void basist_transcoder_destroy(basist_transcoder *tc ) {
    tc->tc = nullptr;
    delete tc;
}

void basist_transcoder_set_data(basist_transcoder *tc, basist_data data) {
    tc->data = data;
}

basist_data basist_transcoder_get_data(basist_transcoder *tc) {
    return tc->data;
}

#define TC (*tc->tc.get())
#define DATA tc->data.data, tc->data.size

bool basist_transcoder_validate_file_checksums(basist_transcoder *tc, bool full_validation) {
    return TC.validate_file_checksums(DATA, full_validation);
}

bool basist_transcoder_validate_header(basist_transcoder *tc) {
    return TC.validate_header(DATA);
}

basist_texture_type basist_transcoder_get_texture_type(basist_transcoder *tc) {
    return static_cast<basist_texture_type>(TC.get_texture_type(DATA));
}

bool basist_transcoder_get_userdata(basist_transcoder *tc, basist_userdata *out_udata) {
    return TC.get_userdata(DATA, out_udata->userdata[0], out_udata->userdata[1]);
}

uint32_t basist_transcoder_get_total_images(basist_transcoder *tc) {
    return TC.get_total_images(DATA);
}

basist_source_format basist_transcoder_get_source_format(basist_transcoder *tc) {
    return static_cast<basist_source_format>(TC.get_tex_format(DATA));
}

uint32_t basist_transcoder_get_total_image_levels(basist_transcoder *tc, uint32_t image_index) {
    return TC.get_total_image_levels(DATA, image_index);
}

bool basist_transcoder_get_image_level_desc(basist_transcoder *tc, uint32_t image_index, uint32_t level_index, basist_image_level_desc *out_desc) {
    return TC.get_image_level_desc(DATA, image_index, level_index, out_desc->orig_width, out_desc->orig_height, out_desc->total_blocks);
}

bool basist_transcoder_get_image_info(basist_transcoder *tc, uint32_t image_index, basist_image_info *out_image_info) {
    return TC.get_image_info(DATA, *reinterpret_cast<basist::basisu_image_info*>(out_image_info), image_index);
}

bool basist_transcoder_get_image_level_info(basist_transcoder *tc, uint32_t image_index, uint32_t level_index, basist_image_level_info *out_level_info) {
    return TC.get_image_level_info(DATA, *reinterpret_cast<basist::basisu_image_level_info*>(out_level_info), image_index, level_index);
}

bool basist_transcoder_get_file_info(basist_transcoder *tc, basist_file_info *ofi) {
    basist::basisu_file_info fi;

    if(!TC.get_file_info(DATA, fi)) {
        return false;
    }

    ofi->version = fi.m_version;
    ofi->total_header_size = fi.m_total_header_size;
    ofi->total_selectors = fi.m_total_selectors;
    ofi->selector_codebook_size = fi.m_selector_codebook_size;
    ofi->total_endpoints = fi.m_total_endpoints;
    ofi->endpoint_codebook_size = fi.m_endpoint_codebook_size;
    ofi->tables_size = fi.m_tables_size;
    ofi->slices_size = fi.m_slices_size;
    ofi->tex_type = static_cast<basist_texture_type>(fi.m_tex_type);
    ofi->us_per_frame = fi.m_us_per_frame;
    ofi->total_slices = fi.m_slice_info.size();
    ofi->total_images = fi.m_total_images;
    ofi->userdata.userdata[0] = fi.m_userdata0;
    ofi->userdata.userdata[1] = fi.m_userdata1;
    ofi->source_format = static_cast<basist_source_format>(fi.m_tex_format);
    ofi->y_flipped = fi.m_y_flipped;
    ofi->etc1s = fi.m_etc1s;
    ofi->has_alpha_slices = fi.m_has_alpha_slices;

    return true;
}

bool basist_transcoder_start_transcoding(basist_transcoder *tc) {
    return TC.start_transcoding(DATA);
}

bool basist_transcoder_stop_transcoding(basist_transcoder *tc) {
    return TC.stop_transcoding();
}

bool basist_transcoder_get_ready_to_transcode(basist_transcoder *tc) {
    return TC.get_ready_to_transcode();
}

bool basist_transcoder_get_slice_info(basist_transcoder *tc, uint32_t slice_index, basist_slice_info *out_slice_info) {
    basist::basisu_file_info fi;

    if(!TC.get_file_info(DATA, fi)) {
        return false;
    }

    *reinterpret_cast<basist::basisu_slice_info*>(out_slice_info) = fi.m_slice_info[slice_index];
    return true;
}

void basist_init_transcode_level_params(basist_transcode_level_params *params) {
    memset(params, 0, sizeof(*params));
    params->output_blocks = nullptr;
    params->transcoder_state = nullptr;
    params->format = BASIST_FORMAT_ETC1_RGB;
}

bool basist_transcoder_transcode_image_level(basist_transcoder *tc, const basist_transcode_level_params *p) {
    return TC.transcode_image_level(DATA,
        p->image_index,
        p->level_index,
        p->output_blocks,
        p->output_blocks_size,
        static_cast<basist::transcoder_texture_format>(p->format),
        p->decode_flags,
        p->output_row_pitch,
        reinterpret_cast<basist::basisu_transcoder_state*>(p->transcoder_state),
        p->output_rows
    );
}

}  // extern "C"
