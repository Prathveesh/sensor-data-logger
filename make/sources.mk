# ==============================================================================
# sources.mk — Source Files, Include Paths, and Preprocessor Definitions
#
# Lists all C sources, assembly sources, include directories, and
# preprocessor definitions required for the build.
#
# Included by the top-level Makefile.
#
# When adding a new module, append its source files and include paths here.
# ==============================================================================

# --------------------------------------------------------------------------
# Preprocessor Definitions
# --------------------------------------------------------------------------

C_DEFS = \
  -DSTM32F407xx

# --------------------------------------------------------------------------
# Include Paths
# --------------------------------------------------------------------------

C_INCLUDES = \
  -Idrivers/uart \
  -Iconfig/cmsis/device/Include \
  -Iconfig/cmsis/core/Include

# --------------------------------------------------------------------------
# C Source Files
# --------------------------------------------------------------------------

C_SOURCES = \
  apps/main.c \
  drivers/uart/uart.c \
  config/cmsis/device/Source/Templates/system_stm32f4xx.c

# --------------------------------------------------------------------------
# Assembly Source Files
# --------------------------------------------------------------------------

ASM_SOURCES = \
  config/cmsis/device/Source/Templates/gcc/startup_stm32f407xx.s

# --------------------------------------------------------------------------
# Linker Script
# --------------------------------------------------------------------------

LDSCRIPT = config/STM32F407VGTx_FLASH.ld
