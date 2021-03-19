project('basisu', 'c', 'cpp',
    version : '1.13',
    meson_version : '>=0.48.0',
    license : 'Apache-2.0',
    default_options : [
        'cpp_std=c++14',
        'cpp_eh=none',
        'cpp_rtti=false',
    ]
)

cpp_options = [
    'cpp_std=c++14',
    'cpp_eh=none',
    'cpp_rtti=false',
]

native_options = [
    'b_lto=false',
    'b_ndebug=true',
    'b_sanitize=none',
    'debug=false',
    'optimization=0',
]

cc = meson.get_compiler('cpp')

dep_m = cc.find_library('m', required : false)
dep_thread = dependency('threads', required : false)

basisu_deps = [
    dep_m,
    dep_thread,
]

basisu_cflags = cc.get_supported_arguments(
    '-Wall',
    '-Wno-class-memaccess',
    '-Wno-misleading-indentation',
    '-Wno-sign-compare',
    '-Wno-unused-but-set-variable',
    '-Wno-unused-value',
    '-Wno-unused-variable',
    '-fno-exceptions',
    '-fno-rtti',
    '-fno-strict-aliasing',
)

encoder_cflags = cc.get_supported_arguments(
    '-mno-avx',
    '-mno-avx2',
    '-mno-avx512f',
    '-mno-sse4.2',
)

if cc.has_argument('-msse4.1')
    encoder_cflags += [
        '-msse4.1',
        '-DBASISU_SUPPORT_SSE=1',
    ]
else
    encoder_cflags += [
        '-DBASISU_SUPPORT_SSE=0',
    ]
endif

basisu_transcoder_src = files(
    'transcoder/basisu_transcoder.cpp',
    'transcoder/basisu_transcoder_c_api.cpp',
)

basisu_src = files(
    'basisu_tool.cpp',
    'encoder/apg_bmp.c',
    'encoder/basisu_astc_decomp.cpp',
    'encoder/basisu_backend.cpp',
    'encoder/basisu_basis_file.cpp',
    'encoder/basisu_bc7enc.cpp',
    'encoder/basisu_comp.cpp',
    'encoder/basisu_enc.cpp',
    'encoder/basisu_etc.cpp',
    'encoder/basisu_frontend.cpp',
    'encoder/basisu_global_selector_palette_helpers.cpp',
    'encoder/basisu_gpu_texture.cpp',
    'encoder/basisu_kernels_sse.cpp',
    'encoder/basisu_pvrtc1_4.cpp',
    'encoder/basisu_resample_filters.cpp',
    'encoder/basisu_resampler.cpp',
    'encoder/basisu_ssim.cpp',
    'encoder/basisu_uastc_enc.cpp',
    'encoder/jpgd.cpp',
    'encoder/lodepng.cpp',
) + basisu_transcoder_src

basisu_native = executable('basisu', basisu_src,
    cpp_args : basisu_cflags + encoder_cflags,
    build_by_default : false,
    gnu_symbol_visibility : 'hidden',
    install : false,
    native : true,
#     override_options : native_options + cpp_options,
    dependencies : basisu_deps,
)

transcoder_cflags = []

if host_machine.endian() == 'big'
    transcoder_cflags += '-DBASISD_IS_BIG_ENDIAN=1'
else
    transcoder_cflags += '-DBASISD_IS_BIG_ENDIAN=0'
endif

# Let's be safe
transcoder_cflags += '-DBASISD_USE_UNALIGNED_WORD_READS=0'

enable_astc = get_option('enable_astc')
enable_atc = get_option('enable_atc')
enable_bc7 = get_option('enable_bc7')
enable_dxt1 = get_option('enable_dxt1')
enable_dxt5a = get_option('enable_dxt5a')
enable_etc2_eac_a8 = get_option('enable_etc2_eac_a8')
enable_etc2_eac_rg11 = get_option('enable_etc2_eac_rg11')
enable_fxt1 = get_option('enable_fxt1')
enable_pvrtc1 = get_option('enable_pvrtc1')
enable_pvrtc2 = get_option('enable_pvrtc2')
enable_uastc = get_option('enable_uastc')

enable_atc = enable_atc or enable_pvrtc2
enable_dxt5a = enable_dxt5a or enable_atc

if enable_astc
    transcoder_cflags += '-DBASISD_SUPPORT_ASTC=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_ASTC=0'
endif

if enable_atc
    transcoder_cflags += '-DBASISD_SUPPORT_ATC=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_ATC=0'
endif

if enable_bc7
    transcoder_cflags += '-DBASISD_SUPPORT_BC7=1'
    transcoder_cflags += '-DBASISD_SUPPORT_BC7_MODE5=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_BC7=0'
    transcoder_cflags += '-DBASISD_SUPPORT_BC7_MODE5=0'
endif

if enable_dxt1
    transcoder_cflags += '-DBASISD_SUPPORT_DXT1=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_DXT1=0'
endif

if enable_dxt5a
    transcoder_cflags += '-DBASISD_SUPPORT_DXT5A=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_DXT5A=0'
endif

if enable_etc2_eac_a8
    transcoder_cflags += '-DBASISD_SUPPORT_ETC2_EAC_A8=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_ETC2_EAC_A8=0'
endif

if enable_etc2_eac_rg11
    transcoder_cflags += '-DBASISD_SUPPORT_ETC2_EAC_RG11=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_ETC2_EAC_RG11=0'
endif

if enable_fxt1
    transcoder_cflags += '-DBASISD_SUPPORT_FXT1=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_FXT1=0'
endif

if enable_pvrtc1
    transcoder_cflags += '-DBASISD_SUPPORT_PVRTC1=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_PVRTC1=0'
endif

if enable_pvrtc2
    transcoder_cflags += '-DBASISD_SUPPORT_PVRTC2=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_PVRTC2=0'
endif

if enable_uastc
    transcoder_cflags += '-DBASISD_SUPPORT_UASTC=1'
else
    transcoder_cflags += '-DBASISD_SUPPORT_UASTC=0'
endif

basisu_transcoder = static_library('basisu_transcoder', basisu_transcoder_src,
    cpp_args : basisu_cflags + transcoder_cflags,
    build_by_default : false,
    gnu_symbol_visibility : 'hidden',
    install : false,
    dependencies : dep_m,
    override_options : cpp_options,
)

basisu_transcoder_dep = declare_dependency(
    link_with : basisu_transcoder,
    include_directories : include_directories('transcoder'),
    version : meson.project_version(),
    compile_args : transcoder_cflags,
)
