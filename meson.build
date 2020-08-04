project('basisu', 'c', 'cpp',
    version : '1.12',
    meson_version : '>=0.48.0',
    license : 'Apache-2.0',
)

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
    '-Wno-unused-variable',
    '-fno-exceptions',
    '-fno-rtti',
    '-fno-strict-aliasing',
)

basisu_transcoder_src = files(
    'transcoder/basisu_transcoder.cpp',
    'transcoder/basisu_transcoder_c_api.cpp',
)

basisu_src = files(
    'apg_bmp.c',
    'basisu_astc_decomp.cpp',
    'basisu_basis_file.cpp',
    'basisu_bc7enc.cpp',
    'basisu_comp.cpp',
    'basisu_enc.cpp',
    'basisu_etc.cpp',
    'basisu_frontend.cpp',
    'basisu_global_selector_palette_helpers.cpp',
    'basisu_gpu_texture.cpp',
    'basisu_pvrtc1_4.cpp',
    'basisu_resample_filters.cpp',
    'basisu_resampler.cpp',
    'basisu_ssim.cpp',
    'basisu_tool.cpp',
    'basisu_uastc_enc.cpp',
    'jpgd.cpp',
    'lodepng.cpp',
    'basisu_backend.cpp',
) + basisu_transcoder_src

basisu_native = executable('basisu', basisu_src,
    cpp_args : basisu_cflags,
    build_by_default : false,
    gnu_symbol_visibility : 'hidden',
    install : false,
    native : true,
#     override_options : native_options,
    dependencies : basisu_deps,
)

transcoder_opts = []

if host_machine.endian() == 'big'
    transcoder_opts += '-DBASISD_IS_BIG_ENDIAN=1'
else
    transcoder_opts += '-DBASISD_IS_BIG_ENDIAN=0'
endif

# Let's be safe
transcoder_opts += '-DBASISD_USE_UNALIGNED_WORD_READS=0'

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
    transcoder_opts += '-DBASISD_SUPPORT_ASTC=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_ASTC=0'
endif

if enable_atc
    transcoder_opts += '-DBASISD_SUPPORT_ATC=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_ATC=0'
endif

if enable_bc7
    transcoder_opts += '-DBASISD_SUPPORT_BC7=1'
    transcoder_opts += '-DBASISD_SUPPORT_BC7_MODE5=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_BC7=0'
    transcoder_opts += '-DBASISD_SUPPORT_BC7_MODE5=0'
endif

if enable_dxt1
    transcoder_opts += '-DBASISD_SUPPORT_DXT1=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_DXT1=0'
endif

if enable_dxt5a
    transcoder_opts += '-DBASISD_SUPPORT_DXT5A=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_DXT5A=0'
endif

if enable_etc2_eac_a8
    transcoder_opts += '-DBASISD_SUPPORT_ETC2_EAC_A8=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_ETC2_EAC_A8=0'
endif

if enable_etc2_eac_rg11
    transcoder_opts += '-DBASISD_SUPPORT_ETC2_EAC_RG11=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_ETC2_EAC_RG11=0'
endif

if enable_fxt1
    transcoder_opts += '-DBASISD_SUPPORT_FXT1=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_FXT1=0'
endif

if enable_pvrtc1
    transcoder_opts += '-DBASISD_SUPPORT_PVRTC1=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_PVRTC1=0'
endif

if enable_pvrtc2
    transcoder_opts += '-DBASISD_SUPPORT_PVRTC2=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_PVRTC2=0'
endif

if enable_uastc
    transcoder_opts += '-DBASISD_SUPPORT_UASTC=1'
else
    transcoder_opts += '-DBASISD_SUPPORT_UASTC=0'
endif

basisu_transcoder = static_library('basisu_transcoder', basisu_transcoder_src,
    cpp_args : basisu_cflags + transcoder_opts,
    build_by_default : false,
    gnu_symbol_visibility : 'hidden',
    install : false,
    dependencies : dep_m,
)

basisu_transcoder_dep = declare_dependency(
    link_with : basisu_transcoder,
    include_directories : include_directories('transcoder'),
    version : meson.project_version(),
    compile_args : transcoder_opts,
)