cmake_minimum_required(VERSION 3.15)


set(SRC_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/proj.conf)
set(TARGET_CONFIG ${CMAKE_CURRENT_BINARY_DIR}/proj.conf)
set(TOP_KCONFIG_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/kconfig)
execute_process(
    COMMAND python $ENV{SDK_BASE}/quectel_build/tools/kconfig/genconfig.py ${TOP_KCONFIG_CONFIG} --config-out=${SRC_CONFIG}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

file(COPY ${SRC_CONFIG} DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})

set(TARGET_CMAKE ${CMAKE_CURRENT_BINARY_DIR}/proj.cmake)
execute_process(
    COMMAND python $ENV{SDK_BASE}/quectel_build/tools/kconfig/cmakeconfig.py ${TARGET_CONFIG} ${TARGET_CMAKE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

include(${TARGET_CMAKE})


find_package(quec_n32g430_sdk REQUIRED HINTS $ENV{SDK_BASE}/quectel_build/scripts)

sdk_set_linker_script($ENV{SDK_BASE}/quectel_build/config/n32g430_flash.ld)

string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")
sdk_add_compile_definitions(
    "-DPROJECT=\"${PROJECT}\""
    "-DVERSION=\"${VERSION}\"" 
    "-DSUBVERSION=\"${SUBVERSION}\""
    "-DBUILD_TIMESTAMP=\"${BUILD_TIMESTAMP}\""
)

sdk_add_compile_options(
    -include quec_prj_config.h
)


# sdk_add_link_options(
#     -Wl,--defsym=__stack_size__=0x3000
#     -Wl,--defsym=__heap_size__=0x8000
# )

sdk_add_subdirectory_if_exist(bsp)
sdk_add_subdirectory_if_exist(task)
sdk_add_subdirectory_if_exist(utils)

sdk_set_main_file(main.c)

sdk_add_include_directories(.)

project(${PROJECT}_${VERSION}_${SUBVERSION})
