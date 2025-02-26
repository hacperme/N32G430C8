macro(sdk_generate_library)
  if(${ARGC})
  foreach(var ${ARGN})
    set(library_name ${var})
  endforeach()
  else()
  get_filename_component(library_name ${CMAKE_CURRENT_LIST_DIR} NAME)
  endif()

  message(STATUS "[register library : ${library_name}], path:${CMAKE_CURRENT_LIST_DIR}")

  set(CURRENT_STATIC_LIBRARY ${library_name})
  add_library(${library_name} STATIC)
  set_property(GLOBAL APPEND PROPERTY SDK_LIBS ${library_name})
  target_link_libraries(${library_name} PUBLIC sdk_intf_lib)
endmacro()

function(sdk_library_add_sources)
  foreach(arg ${ARGV})
    if(IS_DIRECTORY ${arg})
    message(FATAL_ERROR "sdk_library_add_sources() was called on a directory")
    endif()

    if(IS_ABSOLUTE ${arg})
    set(path ${arg})
    else()
    set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()
    target_sources(${CURRENT_STATIC_LIBRARY} PRIVATE ${path})
  endforeach()
endfunction()

function(sdk_library_add_sources_ifdef feature)
  if(${${feature}})
  sdk_library_add_sources(${ARGN})
  endif()
endfunction()

function(sdk_add_include_directories)
  foreach(arg ${ARGV})
    if(IS_ABSOLUTE ${arg})
      set(path ${arg})
    else()
      set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()
    target_include_directories(sdk_intf_lib INTERFACE ${path})
  endforeach()
endfunction()

function(sdk_add_include_directories_ifdef feature)
  if(${${feature}})
  sdk_add_include_directories(${ARGN})
  endif()
endfunction()

function(sdk_add_compile_definitions)
  target_compile_definitions(sdk_intf_lib INTERFACE ${ARGV})
endfunction()

function(sdk_add_compile_definitions_ifdef feature)
  if(${${feature}})
  sdk_add_compile_definitions(${ARGN})
  endif()
endfunction()

function(sdk_add_compile_options)
  target_compile_options(sdk_intf_lib INTERFACE ${ARGV})
endfunction()

function(sdk_add_compile_options_ifdef feature)
  if(${${feature}})
  sdk_add_compile_options(${ARGN})
  endif()
endfunction()

function(sdk_add_link_options)
  target_link_options(sdk_intf_lib INTERFACE ${ARGV})
endfunction()

function(sdk_add_link_options_ifdef feature)
  if(${${feature}})
  sdk_add_link_options(${ARGN})
  endif()
endfunction()

function(sdk_add_link_libraries)
  target_link_libraries(sdk_intf_lib INTERFACE ${ARGV})
endfunction()

function(sdk_add_link_libraries_ifdef feature)
  if(${${feature}})
  sdk_add_link_libraries(${ARGN})
  endif()
endfunction()

function(sdk_add_subdirectory_ifdef feature dir)
  if(${${feature}})
    add_subdirectory(${dir})
  endif()
endfunction()

function(sdk_add_subdirectory_if_exist dir)
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/CMakeLists.txt)
            add_subdirectory(${dir})
        endif()
    endif()
endfunction()

function(sdk_add_static_library)
  foreach(arg ${ARGV})
  if(IS_DIRECTORY ${arg})
  message(FATAL_ERROR "sdk_add_static_library() was called on a directory")
  endif()

  if(IS_ABSOLUTE ${arg})
  set(path ${arg})
  else()
  set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
  endif()
  get_filename_component(library_name ${path} NAME_WE)
  message(STATUS "[register extern library : ${library_name}], path:${CMAKE_CURRENT_LIST_DIR}")
  set_property(GLOBAL APPEND PROPERTY SDK_LIBS ${path})
  endforeach()
endfunction()

function(sdk_set_linker_script ld)
  if(IS_ABSOLUTE ${ld})
  set(path ${ld})
  else()
  set(path ${CMAKE_CURRENT_SOURCE_DIR}/${ld})
  endif()
  set_property(GLOBAL PROPERTY LINKER_SCRIPT ${path})
endfunction()

macro(sdk_set_main_file)
    if(IS_ABSOLUTE ${ARGV0})
    set(path ${ARGV0})
    else()
    set(path ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV0})
    endif()
  set(CURRENT_MAIN_FILE ${path})
endmacro()

macro(sdk_set_current_sign_image)
  set(CURRENT_IMAGE_SLOT_SIZE ${ARGV0})
  set(CURRENT_IMAGE_VERSION ${ARGV1})
  set(CURRENT_IMAGE_SIGN_KEY ${ARGV2})
endmacro()

macro(project name)

  _project(${name} ASM C CXX)
  
  
  set(EXEC_FILE_SUFFIX ".elf")
  
  set(HEX_FILE ${EXECUTABLE_OUTPUT_PATH}/${name}.hex)
  set(BIN_FILE ${EXECUTABLE_OUTPUT_PATH}/${name}.bin)
  set(MAP_FILE ${EXECUTABLE_OUTPUT_PATH}/${name}.map)
  set(ASM_FILE ${EXECUTABLE_OUTPUT_PATH}/${name}.asm)
  set(SIGN_FILE ${EXECUTABLE_OUTPUT_PATH}/${name}.sign.bin)
  set(EXEC_FILE ${name}${EXEC_FILE_SUFFIX})

  add_executable(${EXEC_FILE} ${CURRENT_MAIN_FILE})
  target_link_libraries(${EXEC_FILE} sdk_intf_lib)
  get_property(LINKER_SCRIPT_PROPERTY GLOBAL PROPERTY LINKER_SCRIPT)
  if(EXISTS ${LINKER_SCRIPT_PROPERTY})
    set_target_properties(${EXEC_FILE} PROPERTIES LINK_FLAGS "-T${LINKER_SCRIPT_PROPERTY} -Wl,-Map=${MAP_FILE} -static")
    set_target_properties(${EXEC_FILE} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT_PROPERTY})
  endif()

  get_property(SDK_LIBS_PROPERTY GLOBAL PROPERTY SDK_LIBS)
  target_link_libraries(${EXEC_FILE} -Wl,--start-group ${SDK_LIBS_PROPERTY} app -Wl,--end-group)

  add_custom_command(TARGET ${EXEC_FILE} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${EXEC_FILE}> ${BIN_FILE}
  COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${EXEC_FILE}> ${HEX_FILE}
  # COMMAND ${SIZE} $<TARGET_FILE:${EXEC_FILE}>
  COMMENT "Generate ${BIN_FILE}\r\n")

endmacro()