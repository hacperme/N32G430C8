if(NOT DEFINED ENV{SDK_BASE})
    message(FATAL_ERROR "please set SDK_BASE in your system environment")
endif()

set(SDK_BASE $ENV{SDK_BASE})

set(build_dir ${CMAKE_CURRENT_BINARY_DIR}/out)
set(PROJECT_SOURCE_DIR ${SDK_BASE})
set(PROJECT_BINARY_DIR ${build_dir})
set(EXECUTABLE_OUTPUT_PATH ${SDK_BASE}/quectel_build/release/target)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

add_library(sdk_intf_lib INTERFACE)
add_library(app STATIC ${SDK_BASE}/misc/empty_file.c)
target_link_libraries(app sdk_intf_lib)
if(MINGW OR CYGWIN OR WIN32)
include(${SDK_BASE}/quectel_build/scripts/cmake_toolchain_files/armgcc.cmake)
endif()
include(${SDK_BASE}/quectel_build/scripts/extension.cmake)
include(${SDK_BASE}/quectel_build/scripts/compiler_flags.cmake)

enable_language(C CXX ASM)

add_subdirectory(${SDK_BASE} ${build_dir})