cmake_minimum_required(VERSION 3.15)

message("${SDK_BASE}")

sdk_add_subdirectory_if_exist(CMSIS)

sdk_add_subdirectory_if_exist(n32g430_std_periph_driver)

