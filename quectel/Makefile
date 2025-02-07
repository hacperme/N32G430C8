build_dirs += app

all: $(build_dirs)

options ?= 

$(build_dirs):
	mingw32-make -C $@ $(options)

.PHONY: $(build_dirs)
