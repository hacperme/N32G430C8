sdk_add_compile_options(
    -mcpu=cortex-m4
    -mthumb
    -Wall
    -Os
    -ffunction-sections 
    -fdata-sections
    -DN32G430
    -DUSE_STDPERIPH_DRIVER
    -g 
    -gdwarf-2
 )

sdk_add_link_options(
    -mcpu=cortex-m4
    -mthumb
    -Wall
    --specs=nosys.specs
    -Xlinker --gc-sections
    -Wl,--print-memory-usage
)

sdk_add_link_libraries(c m gcc nosys)


sdk_add_compile_options_ifdef(CONFIG_WERROR -Werror)