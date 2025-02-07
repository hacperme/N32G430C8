SDK_ROOT_PATH ?= ../../

SDK_BASE = $(abspath ../../)

KCONFIG_CONFIG ?= proj.conf
PROJEECT_NAME ?= QUEC_N32G430

export SDK_BASE
export KCONFIG_CONFIG
export PROJEECT_NAME

BUILD_TYPE ?= debug
#cmake definition config
cmake_definition+= -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DPROJEECT_NAME=${PROJEECT_NAME}

include $(SDK_BASE)/project.build

