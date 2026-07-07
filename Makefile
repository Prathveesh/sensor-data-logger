# ==============================================================================
# Makefile — FreeRTOS Sensor Data Logger
#
# Top-level build entry point for the STM32F407G-DISC1 firmware project.
#
# Usage:
#   make          Build the firmware
#   make clean    Remove build artifacts
#   make flash    Program the target via OpenOCD
#   make debug    Start OpenOCD GDB server
#   make size     Print firmware size summary
#
# Prerequisites:
#   - arm-none-eabi-gcc
#   - GNU Make
#   - OpenOCD (for flash/debug targets)
#
# Target Board: STM32F407G-DISC1
# MCU:          STM32F407VGT6
# ==============================================================================

# Project name (used for output filenames)
PROJECT = firmware

# Build output directory
BUILD_DIR = build

# Include build configuration
include make/sources.mk
include make/toolchain.mk
include make/rules.mk
