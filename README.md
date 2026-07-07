# FreeRTOS Sensor Data Logger

A production-style embedded firmware project built from scratch using **Embedded C**, **FreeRTOS**, and the **STM32F407G-DISC1 (STM32F407VGT6)** development board.

This repository documents the complete firmware development process—from requirements analysis and software architecture to implementation, testing, debugging, and documentation—following practices commonly used in professional embedded software teams.

---

# Project Overview

A **Sensor Data Logger** is an embedded system that periodically acquires data from one or more sensors, processes the collected information, and makes it available for monitoring or analysis.

For the initial release (**v0.1.0**), this project focuses on:

* Periodic sensor acquisition
* UART-based data logging
* UART Command Line Interface (CLI)
* FreeRTOS task-based firmware
* Modular firmware architecture
* Register-level peripheral programming

The project is intentionally developed incrementally, with every stage documented and committed to Git.

---

# Project Objectives

The primary objectives of this project are to:

* Learn professional embedded firmware development.
* Design a modular and maintainable firmware architecture.
* Develop reusable register-level peripheral drivers.
* Learn FreeRTOS task design and inter-task communication.
* Build the project using GNU Make and the GNU ARM Toolchain.
* Follow professional Git workflows.
* Produce engineering documentation alongside the implementation.

---

# Target Hardware

| Component            | Details            |
| -------------------- | ------------------ |
| Development Board    | STM32F407G-DISC1   |
| MCU                  | STM32F407VGT6      |
| Core                 | ARM Cortex-M4F     |
| Programming Language | Embedded C (C99)   |
| RTOS                 | FreeRTOS           |
| Compiler             | arm-none-eabi-gcc  |
| Build System         | GNU Make           |
| IDE                  | Visual Studio Code |
| Debugger             | ST-Link GDB        |
| Version Control      | Git & GitHub       |

---

# Current Software Architecture

The firmware follows a lightweight three-layer architecture.

```text
+------------------------------------------------------+
|                  Application Layer                   |
|------------------------------------------------------|
| main                                                 |
| Sensor Manager                                       |
| Logger                                               |
| CLI                                                  |
+------------------------------------------------------+
|              Hardware Interface Layer                |
|------------------------------------------------------|
| UART Driver                                          |
+------------------------------------------------------+
|             CMSIS / STM32 Hardware Layer             |
|------------------------------------------------------|
| CMSIS                                                |
| Startup Files                                        |
| Linker Script                                        |
| STM32F407 Registers                                  |
+------------------------------------------------------+
```

### Design Philosophy

The architecture is intentionally lightweight.

Every software module exists because a functional requirement justifies it.

No abstraction layer or driver is introduced until it is required by the project.

---

# Repository Structure

```text
freertos-sensor-data-logger/
│
├── apps/
│   ├── main.c
│   ├── logger/
│   ├── sensor_manager/
│   └── cli/
│
├── drivers/
│   └── uart/
│
├── freertos/
│
├── config/
│
├── docs/
│   ├── Requirements.md
│   └── Architecture.md
│
├── make/
│
├── README.md
├── LICENSE
└── .gitignore
```

---

# Current Features (v0.1.0)

The first release targets the following functionality:

* Hardware initialization
* FreeRTOS initialization
* Periodic sensor acquisition
* UART-based logging
* UART Command Line Interface
* Runtime error reporting
* Modular firmware organization

---

# Planned Features

The following capabilities are planned for future releases:

* Additional peripheral drivers
* I²C sensor support
* GPIO abstraction
* SD Card logging
* External Flash logging
* DMA-based UART
* USB CDC
* CAN communication
* Configuration persistence
* LittleFS integration
* Low-power support
* Bootloader integration
* CI/CD
* Unit testing

---

# Documentation

Project documentation is maintained alongside the firmware implementation.

| Document          | Description                                     |
| ----------------- | ----------------------------------------------- |
| `Requirements.md` | Functional requirements for the current release |
| `Architecture.md` | Firmware architecture and module organization   |

Additional documents will be added as development progresses.

---

# Development Principles

This project follows a few simple engineering principles throughout its development:

* Requirements drive the architecture.
* Architecture drives the implementation.
* Every module has a single responsibility.
* Hardware access is isolated from application logic.
* No source file or folder exists without a clear purpose.
* Documentation evolves together with the code.
* Git history should reflect the engineering process.

---

# Build Environment Setup

### Supported Host OS
* Ubuntu
* WSL2 Ubuntu
* Native Linux

*(Note: Windows users are recommended to use WSL2 for the best experience).*

### Required Packages
To compile and flash the firmware, you will need to install the following packages:

```bash
sudo apt update

sudo apt install \
    build-essential \
    make \
    gcc-arm-none-eabi \
    gdb-multiarch \
    openocd \
    git
```

### Verify Installation
You can verify your installation using the following commands:

```bash
arm-none-eabi-gcc --version
arm-none-eabi-gdb --version
openocd --version
make --version
```

### Build Instructions
To build the project, run:

```bash
make
```

**Expected outputs:**
* `firmware.elf`
* `firmware.hex`
* `firmware.bin`

### Flash Instructions
To flash the firmware to the board using OpenOCD:

```bash
make flash
```

### Debug Instructions
To start the OpenOCD GDB server for debugging, run:

```bash
make debug
```

Debugging is performed using:
* ST-Link
* OpenOCD
* GDB
* VS Code Cortex-Debug extension

---

# Project Status

> 🚧 **In Development**

### Completed Milestones
* ✅ Project Initialization
* ✅ Requirements Document
* ✅ SWAD Document
* ✅ SDD Document
* ✅ ICD Documents
* ✅ UART Driver Implementation
* ✅ CMSIS Integration
* ✅ GNU Make Build System
* ✅ Startup Code Integration
* ✅ Linker Script Integration
* ✅ Firmware Build Generation

### In-Progress
* ⏳ UART Hardware Bring-up

### Future Milestones
* ⏳ Logger Module
* ⏳ CLI Module
* ⏳ Sensor Manager
* ⏳ FreeRTOS Integration
* ⏳ Application Layer

---

# License

This project is released under the **MIT License**.
