ARMGNU ?= aarch64-linux-gnu
COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude

LIBFDT_soname = libfdt.$(SHAREDLIB_EXT).1
LIBFDT_INCLUDES = fdt.h libfdt.h
LIBFDT_VERSION = version.lds

LIBFDT_SRCS = glibc.c fdt.c fdt_ro.c fdt_wip.c fdt_sw.c fdt_rw.c fdt_strerror.c fdt_empty_tree.c
LIBFDT_OBJS = $(LIBFDT_SRCS:%.c=%.o)


all: libfdt.a

%.o:%.c
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@


libfdt.a: $(LIBFDT_OBJS)
	 ar rcs libfdt.a $(LIBFDT_OBJS)
