# ==============================================================================
# toolchain.mk — Compiler and Toolchain Configuration
#
# Defines the ARM cross-compilation toolchain, CPU architecture flags,
# compiler warnings, optimization level, and linker flags.
#
# Included by the top-level Makefile.
# ==============================================================================

# Toolchain prefix
PREFIX = arm-none-eabi-

CC      = $(PREFIX)gcc
AS      = $(PREFIX)gcc -x assembler-with-cpp
LD      = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
OBJDUMP = $(PREFIX)objdump
SIZE    = $(PREFIX)size

# CPU and architecture flags
CPU = -mcpu=cortex-m4
MCU = $(CPU) -mthumb -mfloat-abi=soft

# C language standard
CSTD = -std=c99

# Warning flags
WARNINGS = -Wall -Wextra -Werror -Wshadow -Wdouble-promotion -Wformat=2 \
           -Wundef -fno-common

# Optimization (debug build by default)
OPT = -Og

# Debug information
DEBUG = -g3 -gdwarf-2

# Code generation
CODEGEN = -ffunction-sections -fdata-sections -fstack-usage

# Assembler flags
ASFLAGS = $(MCU) $(DEBUG) -Wall

# Compiler flags (combined)
CFLAGS = $(MCU) $(CSTD) $(C_DEFS) $(C_INCLUDES) $(OPT) $(DEBUG) \
         $(WARNINGS) $(CODEGEN) -MMD -MP

# Linker flags
LDFLAGS = $(MCU) -T$(LDSCRIPT) -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map,--cref \
          --specs=nano.specs --specs=nosys.specs -lc -lm -lnosys
