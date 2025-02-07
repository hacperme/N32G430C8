sdk_generate_library(n32g430_std_periph_driver)

file(GLOB_RECURSE SOURCES ./src/*.c)
sdk_library_add_sources( ${SOURCES})

sdk_add_include_directories(
    inc
)