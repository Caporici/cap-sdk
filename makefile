# =====================================================
# Project
# =====================================================
PROJECT := cap_os_sdk
TARGET  := $(PROJECT)

# =====================================================
# Directories
# =====================================================
ROOT_DIR := /home/victor/Github/cap-os-sdk
# Ajuste aqui conforme sua estrutura real:
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := /home/victor/Github/cap-sdk/build

# Incluímos os diretórios de header
INC_DIRS := \
    $(ROOT_DIR)/include \
    $(SRC_DIR)/include \
    include \
	font \
    osal \
    ui

# =====================================================
# Toolchain e Sysroot
# =====================================================
TOOLCHAIN_DIR := /home/victor/Github/cap-os-sdk/bin/arm-poky-linux-gnueabi
CC := $(TOOLCHAIN_DIR)/arm-poky-linux-gnueabi-gcc
LD := $(CC)

SYSROOT := /home/victor/Github/cap-os-sdk/sysroots/cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
GCC_INC := /home/victor/Github/cap-os-sdk/lib/arm-poky-linux-gnueabi/gcc/arm-poky-linux-gnueabi/13.4.0/include

# =====================================================
# Flags
# =====================================================
CSTD       := -std=gnu11
WARNINGS   := -Wall -Wextra 
OPT        := -O2
DEBUG      := -g
ARCH_FLAGS := -mfloat-abi=hard -mfpu=neon-vfpv4 -mcpu=cortex-a7

INCLUDES := $(addprefix -I,$(INC_DIRS)) -isystem $(GCC_INC)

CFLAGS  := $(CSTD) $(WARNINGS) $(OPT) $(DEBUG) $(INCLUDES) --sysroot=$(SYSROOT) $(ARCH_FLAGS)
LDFLAGS := --sysroot=$(SYSROOT) $(ARCH_FLAGS) -L$(SYSROOT)/usr/lib -L$(SYSROOT)/lib
LDLIBS  := -llvgl -ldrm -lm -lpthread -lrt

# =====================================================
# Sources / Objects - Mapeamento inteligente
# =====================================================
# Buscamos todos os .c no src e nas subpastas osal e ui
SRCS := $(wildcard $(SRC_DIR)/*.c) \
        $(wildcard $(SRC_DIR)/osal/*.c) \
        $(wildcard $(SRC_DIR)/ui/*.c) \
		$(wildcard $(SRC_DIR)/font/*.c) \
        $(wildcard *.c) # Inclui o main.c se estiver na raiz

# Isso transforma src/osal/osal.c em obj/src/osal/osal.o
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# =====================================================
# Phony targets
# =====================================================
.PHONY: all clean info dirs

all: info dirs $(BIN_DIR)/$(TARGET)

info:
	@echo "CC      = $(CC)"
	@echo "SOURCES = $(SRCS)"
	@echo "BUILD   = $(BIN_DIR)/$(TARGET)"

dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# =====================================================
# Link
# =====================================================
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# =====================================================
# Compile - A MÁGICA ESTÁ AQUI
# =====================================================
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)  # Cria a subpasta necessária dentro de obj/ antes de compilar
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)