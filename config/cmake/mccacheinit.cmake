# This is the CMakeCache file.

#########################
# EXTERNAL cache entries
#########################

set (BUILD_TESTING ON CACHE BOOL "Build HDF4 Unit Testing" FORCE)

set (HDF_PACKAGE_EXT "" CACHE STRING "Name of HDF package extension" FORCE)

set (HDF_PACKAGE_NAMESPACE "hdf4::" CACHE STRING "Name for HDF package namespace" FORCE)

set (HDF4_BUILD_EXAMPLES ON CACHE BOOL "Build HDF4 Library Examples" FORCE)

set (HDF4_BUILD_UTILS ON CACHE BOOL "Build HDF4 Library Utilities" FORCE)

set (HDF4_BUILD_GENERATORS OFF CACHE BOOL "Build Test Generators" FORCE)

set (HDF4_ENABLE_JPEG_LIB_SUPPORT ON CACHE BOOL "Use JPEG Filter" FORCE)

set (HDF4_ENABLE_SZIP_SUPPORT OFF CACHE BOOL "Use SZip Filter" FORCE)

set (HDF4_ENABLE_SZIP_ENCODING OFF CACHE BOOL "Use SZip Encoding" FORCE)

set (HDF4_USING_ANALYSIS_TOOL ON CACHE BOOL "Indicate that an analysis checker is used" FORCE)

set (HDF4_DISABLE_COMPILER_WARNINGS OFF CACHE BOOL "Disable compiler warnings" FORCE)

set (HDF4_ENABLE_DEPRECATED_SYMBOLS ON CACHE BOOL "Enable deprecated public API symbols" FORCE)

set (HDF4_PACKAGE_EXTLIBS OFF CACHE BOOL "CPACK - include external libraries" FORCE)

set (HDF4_NO_PACKAGES ON CACHE BOOL "CPACK - Disable packaging" FORCE)

set (HDF4_MINGW_STATIC_GCC_LIBS ON CACHE BOOL "Statically link libgcc/libstdc++" FORCE)

set (HDF4_ALLOW_EXTERNAL_SUPPORT "TGZ" CACHE STRING "Allow External Library Building (NO GIT TGZ)" FORCE)
set_property (CACHE HDF4_ALLOW_EXTERNAL_SUPPORT PROPERTY STRINGS NO GIT TGZ)

########################
# compression options
########################
set (ZLIB_PACKAGE_NAME "zlib" CACHE STRING "Name of ZLIB package" FORCE)
set (ZLIB_TGZ_NAME "zlib-1.3.1.tar.gz" CACHE STRING "Use HDF4_ZLib from compressed file" FORCE)
set (ZLIB_TGZ_ORIGPATH "https://github.com/madler/zlib/releases/download/v1.3.1" CACHE STRING "Use ZLIB from original location" FORCE)
set (ZLIB_USE_LOCALCONTENT ON CACHE BOOL "Use local file for ZLIB FetchContent" FORCE)
set (ZLIB_GIT_URL "https://github.com/madler/zlib.git" CACHE STRING "Use ZLIB from  GitHub repository" FORCE)
set (ZLIB_GIT_BRANCH "develop" CACHE STRING "" FORCE)

set (ZLIBNG_PACKAGE_NAME "zlib-ng" CACHE STRING "Name of ZLIBNG package" FORCE)
set (ZLIBNG_TGZ_NAME "2.2.2.tar.gz" CACHE STRING "Use ZLib from compressed file" FORCE)
set (ZLIBNG_TGZ_ORIGPATH "https://github.com/zlib-ng/zlib-ng/archive/refs/tags" CACHE STRING "Use ZLIBNG from original location" FORCE)
set (ZLIBNG_GIT_URL "https://github.com/zlib-ng/zlib-ng.git" CACHE STRING "Use ZLIBNG from  GitHub repository" FORCE)
set (ZLIBNG_GIT_BRANCH "develop" CACHE STRING "" FORCE)

set (LIBAEC_PACKAGE_NAME "libaec" CACHE STRING "Name of AEC SZIP package" FORCE)
set (LIBAEC_TGZ_NAME "libaec-1.1.3.tar.gz" CACHE STRING "Use SZip AEC from compressed file" FORCE)
set (LIBAEC_TGZ_ORIGPATH "https://github.com/MathisRosenhauer/libaec/releases/download/v1.1.3" CACHE STRING "Use LIBAEC from original location" FORCE)
set (LIBAEC_USE_LOCALCONTENT ON CACHE BOOL "Use local file for LIBAEC FetchContent" FORCE)
set (LIBAEC_GIT_URL "https://github.com/MathisRosenhauer/libaec.git" CACHE STRING "Use LIBAEC from  GitHub repository" FORCE)
set (LIBAEC_GIT_BRANCH "v1.1.3" CACHE STRING "" FORCE)

set (JPEG_PACKAGE_NAME "jpeg" CACHE STRING "Name of JPEG package" FORCE)
set (JPEG_TGZ_ORIGPATH "https://www.ijg.org/filesz" CACHE STRING "Use JPEG from original location" FORCE)
set (JPEG_TGZ_NAME "jpegsrc.v9e.tar.gz" CACHE STRING "Use JPEG from original compressed file" FORCE)
set (JPEG_USE_LOCALCONTENT ON CACHE BOOL "Use local file for JPEG FetchContent" FORCE)

set (CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build Debug" FORCE)

set (CTEST_CONFIGURATION_TYPE "Debug" CACHE STRING "Build Debug" FORCE)
