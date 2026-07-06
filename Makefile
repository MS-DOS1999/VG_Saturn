THIS_ROOT:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

ifeq ($(strip $(YAUL_INSTALL_ROOT)),)
  $(error Undefined YAUL_INSTALL_ROOT (install root directory))
endif

include $(YAUL_INSTALL_ROOT)/share/build.pre.mk

BUILTIN_ASSETS=
VG_EXTRA_FLAGS ?=
VG_BUILD ?= release

ifeq ($(VG_BUILD),debug)
  VG_OPT_FLAGS ?= -O0 -g
  VG_DEBUG_MODE ?= 1
  VG_SATURN_PROFILE ?= 0
else ifeq ($(VG_BUILD),profile)
  VG_OPT_FLAGS ?= -Os -g
  VG_DEBUG_MODE ?= 0
  VG_SATURN_PROFILE ?= 1
else
  VG_OPT_FLAGS ?= -Os -DNDEBUG
  VG_DEBUG_MODE ?= 0
  VG_SATURN_PROFILE ?= 0
endif

VG_SATURN_DEBUG_LOG ?= 0
SH_BUILD_DIR := build/$(VG_BUILD)

SH_PROGRAM:= verdict_guilty_saturn
SH_SRCS:= \
	source/cpp/Font.cpp \
	source/cpp/stdafx.cpp \
	source/saturn/VerdictGuilty_Saturn.cpp \
	source/saturn/cxx_runtime.cpp \
	source/saturn/gl_compat.cpp \
	source/saturn/interface.cpp \
	source/saturn/joypad.cpp \
	source/saturn/kos_compat.cpp \
	source/saturn/libc_compat.cpp \
	source/saturn/saturn_memory.cpp \
	source/saturn/saturn_debug.cpp \
	source/saturn/saturn_fastdraw.cpp \
	source/saturn/saturn_profile.cpp \
	source/saturn/saturn_platform.cpp

VG_COMMON_FLAGS:= \
	$(VG_OPT_FLAGS) \
	-Isource/saturn \
	-Isource/h \
	-Isource/dc \
	-include source/saturn/saturn_compat.h \
	-DSATURN \
	-DDREAMCAST \
	-DDEBUG_MODE=$(VG_DEBUG_MODE) \
	-DVG_SATURN_PROFILE=$(VG_SATURN_PROFILE) \
	-DVG_SATURN_DEBUG_LOG=$(VG_SATURN_DEBUG_LOG) \
	-Wno-unused \
	-Wno-unused-parameter \
	-Wno-unused-variable \
	-Wno-unused-but-set-variable \
	-Wno-sign-compare \
	-Wno-write-strings \
	-Wno-format \
	-Wno-parentheses \
	-Wno-reorder \
	-Wno-shadow \
	-Wno-missing-field-initializers \
	$(VG_EXTRA_FLAGS)

SH_CFLAGS+= $(VG_COMMON_FLAGS)
SH_CXXFLAGS+= $(VG_COMMON_FLAGS) -fpermissive
SH_LDFLAGS+= -T source/saturn/yaul_saturn.ld

IMAGE_DIRECTORY:= cd
IMAGE_1ST_READ_BIN:= A.BIN

IP_VERSION:= V1.000
IP_RELEASE_DATE:= 20260705
IP_AREAS:= JTUBKAEL
IP_PERIPHERALS:= JAMKST
IP_TITLE:= VERDICT GUILTY
IP_MASTER_STACK_ADDR:= 0x06004000
IP_SLAVE_STACK_ADDR:= 0x06001E00
IP_1ST_READ_ADDR:= 0x06004000
IP_1ST_READ_SIZE:= 0

include $(YAUL_INSTALL_ROOT)/share/build.post.iso-cue.mk
