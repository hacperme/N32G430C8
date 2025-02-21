sdk_generate_library(utils)

file(GLOB_RECURSE SOURCES ./ring_buffer/*.c)
sdk_library_add_sources( ${SOURCES})

sdk_add_include_directories(
    ring_buffer
)