SDK_ROOT_PATH ?= ../../

SDK_BASE = $(abspath ../../)

KCONFIG_CONFIG ?= proj.conf

export SDK_BASE
export KCONFIG_CONFIG
export project
export version
export subversion

bulid_type ?= debug
#cmake definition config
cmake_definition+= -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DPROJECT=${project} -DVERSION=${version} -DSUBVERSION=${subversion}

include $(SDK_BASE)/project.build

