options ?=new
project ?=app
version ?=v01
subversion ?=V01
bulid_type ?=release

build_dirs += $(project)

all: $(build_dirs)


$(build_dirs):
	mingw32-make -C $@ $(options) 

.PHONY: $(build_dirs)
