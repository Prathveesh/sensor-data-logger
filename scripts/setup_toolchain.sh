#!/bin/bash
# ==============================================================================
# FreeRTOS Sensor Data Logger - Toolchain Setup Script
#
# Installs the required development tools for the STM32F407G-DISC1 project:
#   - GNU Arm Embedded Toolchain (arm-none-eabi-gcc)
#   - GNU Make
#   - OpenOCD
#
# Usage:
#   chmod +x scripts/setup_toolchain.sh
#   sudo ./scripts/setup_toolchain.sh
#
# Supported:
#   - Ubuntu / Debian (apt)
#   - Fedora / RHEL (dnf)
#   - Arch Linux (pacman)
# ==============================================================================

set -euo pipefail

# ------------------------------------------------------------------------------
# Helpers
# ------------------------------------------------------------------------------

banner() {
    echo ""
    echo "==============================================================================="
    echo "  $1"
    echo "==============================================================================="
    echo ""
}

check_root() {
    if [ "$(id -u)" -ne 0 ]; then
        echo "[ERROR] This script must be run as root."
        echo "        Usage: sudo ./scripts/setup_toolchain.sh"
        exit 1
    fi
}

detect_package_manager() {
    if command -v apt-get &> /dev/null; then
        PKG_MANAGER="apt"
    elif command -v dnf &> /dev/null; then
        PKG_MANAGER="dnf"
    elif command -v pacman &> /dev/null; then
        PKG_MANAGER="pacman"
    else
        echo "[ERROR] No supported package manager found (apt, dnf, pacman)."
        exit 1
    fi
    echo "[OK] Package manager: $PKG_MANAGER"
}

install_packages() {
    case "$PKG_MANAGER" in
        apt)
            apt-get update -qq
            apt-get install -y gcc-arm-none-eabi make openocd
            ;;
        dnf)
            dnf install -y arm-none-eabi-gcc-cs arm-none-eabi-newlib make openocd
            ;;
        pacman)
            pacman -Sy --noconfirm arm-none-eabi-gcc arm-none-eabi-newlib make openocd
            ;;
    esac
}

verify_tool() {
    local name="$1"
    local cmd="$2"

    if command -v "$cmd" &> /dev/null; then
        local version
        version=$("$cmd" --version 2>&1 | head -n 1)
        echo "[OK] $name: $version"
    else
        echo "[MISSING] $name ($cmd)"
        MISSING=1
    fi
}

# ------------------------------------------------------------------------------
# Main
# ------------------------------------------------------------------------------

banner "FreeRTOS Sensor Data Logger - Toolchain Setup"

check_root
detect_package_manager

banner "Installing Development Tools"

install_packages

banner "Verification"

MISSING=0

verify_tool "ARM GCC"  "arm-none-eabi-gcc"
verify_tool "GNU Make" "make"
verify_tool "OpenOCD"  "openocd"

echo ""

if [ "$MISSING" -eq 0 ]; then
    echo "All tools installed successfully."
    echo "You may now run 'make' from the project root."
else
    echo "Some tools are missing. Check the output above."
fi

echo ""
