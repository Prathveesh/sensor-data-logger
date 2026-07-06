# FreeRTOS Sensor Data Logger

A production-style embedded firmware project built from scratch using **Embedded C**, **FreeRTOS**, and the **STM32F3 Discovery (STM32F303VCT6)** development board.

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
| Development Board    | STM32F3 Discovery  |
| MCU                  | STM32F303VCT6      |
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
| STM32F303 Registers                                  |
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

# Project Status

> 🚧 **In Development**

Current milestone:

* ✅ Project initialization
* ✅ Repository organization
* ✅ Functional requirements
* ✅ Software architecture
* ⏳ Software design
* ⏳ Driver implementation
* ⏳ FreeRTOS integration
* ⏳ Application development
* ⏳ Testing
* ⏳ Documentation

---

# License

This project is released under the **MIT License**.
