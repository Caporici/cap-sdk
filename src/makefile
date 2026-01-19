# =====================================================
# Project
# =====================================================
PROJECT := cap_os_sdk
TARGET  := $(PROJECT)

# =====================================================
# Directories
# =====================================================
ROOT_DIR := ..
SRC_DIR  := .
OBJ_DIR  := obj

BIN_DIR  := /home/victor/CAP_OS_SDK/build

INC_DIRS := \
    $(ROOT_DIR)/include \
    $(SRC_DIR)/include

# =====================================================
# Toolchain e Sysroot
# =====================================================
TOOLCHAIN_DIR := /home/victor/CAP_OS_SDK/bin/arm-poky-linux-gnueabi

CC := $(TOOLCHAIN_DIR)/arm-poky-linux-gnueabi-gcc
LD := $(CC)

SYSROOT := /home/victor/CAP_OS_SDK/sysroots/cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi

GCC_INC := /home/victor/CAP_OS_SDK/lib/arm-poky-linux-gnueabi/gcc/arm-poky-linux-gnueabi/13.4.0/include

# =====================================================
# Flags (Configuradas para Cortex-A7 Hard Float)
# =====================================================
CSTD       := -std=c11
WARNINGS   := -Wall -Wextra -Wpedantic
OPT        := -O2
DEBUG      := -g
ARCH_FLAGS := -mfloat-abi=hard -mfpu=neon-vfpv4 -mcpu=cortex-a7

INCLUDES := $(addprefix -I,$(INC_DIRS)) -isystem $(GCC_INC)

CFLAGS  := $(CSTD) $(WARNINGS) $(OPT) $(DEBUG) $(INCLUDES) --sysroot=$(SYSROOT) $(ARCH_FLAGS)
LDFLAGS := --sysroot=$(SYSROOT) $(ARCH_FLAGS)
LDLIBS  :=

# =====================================================
# Sources / Objects
# =====================================================
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# =====================================================
# Phony targets
# =====================================================
.PHONY: all clean info dirs

# =====================================================
# Default target
# =====================================================
all: info dirs $(BIN_DIR)/$(TARGET)

# =====================================================
# Info / sanity check
# =====================================================
info:
	@echo "CC      = $(CC)"
	@echo "SYSROOT = $(SYSROOT)"
	@echo "GCC_INC = $(GCC_INC)"
	@echo "BUILD  = $(BIN_DIR)/$(TARGET)"

# =====================================================
# Directories
# =====================================================
dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# =====================================================
# Link
# =====================================================
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# =====================================================
# Compile
# =====================================================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# =====================================================
# Clean
# =====================================================
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET)