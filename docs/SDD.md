# Software Design Document (SDD)

| **Item**           | **Value**                      |
| ------------------ | ------------------------------ |
| **Project**        | FreeRTOS Sensor Data Logger    |
| **Document**       | Software Design Document (SDD) |
| **Version**        | 0.1                            |
| **Status**         | Draft                          |
| **Author**         | Prathveesh N S                 |
| **Target Release** | v0.1.0                         |
| **Last Updated**   | 2026-07-06                     |

---

# 1. Introduction

This document describes the detailed software design for the **FreeRTOS Sensor Data Logger** project.

The purpose of this document is to define the software modules, their responsibilities, interfaces, dependencies, and design philosophy before implementation begins.

This document is derived from:

* Requirements.md
* SWAD.md

The implementation (`.c` and `.h` files) shall follow the design described in this document.

---

# 2. Purpose

The Software Design Document (SDD) provides the detailed design of each software module.

The objectives are to:

* Define module responsibilities.
* Define module boundaries.
* Define module interactions.
* Minimize coupling between modules.
* Provide a blueprint for implementation.
* Enable design reviews before coding.

---

# 3. Scope

This document covers the software modules required for Release **v0.1.0**.

The following modules are included:

* Main Application
* Logger
* Sensor Manager
* Command Line Interface (CLI)
* UART Driver

Future modules such as GPIO, I²C, Storage, DMA, and BSP are intentionally excluded from this revision.

---

# 4. Design Philosophy

The firmware follows the following design principles.

## DP-001 — Single Responsibility

Each software module shall perform one clearly defined function.

---

## DP-002 — Information Hiding

Internal implementation details shall remain private to each module.

Only public APIs shall be exposed through header files.

---

## DP-003 — Low Coupling

Modules shall communicate only through documented public interfaces.

Direct dependencies between unrelated modules shall be avoided.

---

## DP-004 — Requirement Driven Design

Every software module shall exist because at least one approved functional requirement justifies its existence.

---

## DP-005 — Incremental Development

The software design shall evolve alongside the project requirements.

Additional modules shall only be introduced when justified.

---

# 5. Module Overview

The following modules are included in Release v0.1.0.

| Module         | Responsibility                           |
| -------------- | ---------------------------------------- |
| Main           | System startup and initialization        |
| Sensor Manager | Sensor acquisition and sensor management |
| Logger         | Logging and runtime message generation   |
| CLI            | User command processing                  |
| UART Driver    | UART peripheral communication            |

---

# 6. Module Design

---

# 6.1 Main Application

## Purpose

Acts as the firmware entry point.

Responsible for initializing the system, creating application tasks, and starting the FreeRTOS scheduler.

---

## Responsibilities

* System startup
* Module initialization
* Driver initialization
* FreeRTOS initialization
* Task creation
* Scheduler startup

---

## Dependencies

* Logger
* Sensor Manager
* CLI
* UART Driver
* FreeRTOS

---

## Public Interface

The application entry point is the standard C `main()` function.

No public header file is required.

---

## Future Enhancements

* Bootloader support
* Startup diagnostics
* Power-on self-test

---

# 6.2 Logger Module

## Purpose

Provides a centralized interface for generating runtime log messages.

---

## Responsibilities

* Logger initialization
* Log formatting
* Runtime logging
* Error logging

---

## Dependencies

* UART Driver

---

## Public Interface

Defined in:

```text
logger/logger.h
```

Detailed interface specification shall be provided in the Logger Interface Control Document (ICD).

---

## Future Enhancements

* Log levels
* Timestamp support
* DMA transmission
* SD card backend

---

# 6.3 Sensor Manager

## Purpose

Provides a centralized interface for acquiring sensor data.

---

## Responsibilities

* Sensor initialization
* Periodic sensor acquisition
* Sensor validation
* Sensor error reporting

---

## Dependencies

* Logger
* Hardware Interface (future sensor drivers)

---

## Public Interface

Defined in:

```text
sensor_manager/sensor_manager.h
```

Detailed interface specification shall be provided in the Sensor Manager ICD.

---

## Future Enhancements

* Multiple sensors
* Sensor registration framework
* Sensor calibration

---

# 6.4 Command Line Interface (CLI)

## Purpose

Provides user interaction through UART.

---

## Responsibilities

* Receive user commands
* Parse command strings
* Execute supported commands
* Display responses

---

## Dependencies

* UART Driver
* Logger

---

## Public Interface

Defined in:

```text
cli/cli.h
```

Detailed interface specification shall be provided in the CLI ICD.

---

## Future Enhancements

* Command history
* Auto-completion
* Configuration commands

---

# 6.5 UART Driver

## Purpose

Provides register-level access to the STM32 UART peripheral.

---

## Responsibilities

* UART initialization
* UART transmission
* UART reception
* UART configuration

---

## Dependencies

* CMSIS
* STM32 peripheral registers

---

## Public Interface

Defined in:

```text
drivers/uart/uart.h
```

Detailed interface specification shall be provided in the UART ICD.

---

## Future Enhancements

* Interrupt mode
* DMA support
* Ring buffer
* Multiple UART instances

---

# 7. Module Interaction

The software modules interact according to the following dependency model.

```text
                +------------------+
                |      main        |
                +---------+--------+
                          |
        +-----------------+-----------------+
        |                 |                 |
        v                 v                 v
+---------------+  +---------------+  +---------------+
| SensorManager |  |    Logger     |  |      CLI      |
+-------+-------+  +-------+-------+  +-------+-------+
        |                  |                  |
        +------------------+------------------+
                           |
                           v
                    +--------------+
                    | UART Driver  |
                    +--------------+
                           |
                           v
                  STM32 CMSIS / Registers
```

---

# 8. Interface Control Documents (ICD)

Every software module shall have a corresponding Interface Control Document.

The ICD defines the software interface before implementation.

Each ICD shall include:

* Purpose
* Dependencies
* Include Files
* Public Macros
* Enumerations
* Structures
* Typedefs
* Public APIs
* API Description
* Function Parameters
* Return Values
* Valid Values
* Error Codes
* Usage Examples

The ICD is the authoritative specification for the module interface.

Header files and Doxygen comments shall be derived from the ICD.

---

# 9. Coding Guidelines

The implementation shall follow the following guidelines.

* Embedded C (C99)
* Practical MISRA C compliance where applicable
* One responsibility per module
* Separate interface (`.h`) and implementation (`.c`)
* Static functions for private implementation
* Public APIs documented using Doxygen
* Minimize global variables
* Prefer explicit initialization
* Keep hardware access inside the Hardware Interface Layer

---

# 10. Future Evolution

Future revisions of this document may introduce designs for:

* GPIO Driver
* I²C Driver
* DMA Support
* Storage Manager
* SD Card Logging
* Configuration Manager
* Power Management
* Bootloader Integration

These modules will be added only when supported by new functional requirements.

---

# 11. Revision History

| Version | Date       | Author         | Changes                                    |
| ------- | ---------- | -------------- | ------------------------------------------ |
| 0.1     | 2026-07-06 | Prathveesh N S | Initial software design for Release v0.1.0 |
