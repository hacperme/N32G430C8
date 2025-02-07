sdk_generate_library(CMSIS)

# file(GLOB_RECURSE SOURCES ./*.c)
sdk_library_add_sources(
    device/startup/startup_n32g430_gcc.s
    device/system_n32g430.c
)

sdk_add_include_directories(
    core 
    device
)