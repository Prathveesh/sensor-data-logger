# Software Architecture Document (SWAD)

| **Item**           | **Value**                             |
| ------------------ | ------------------------------------- |
| **Project**        | FreeRTOS Sensor Data Logger           |
| **Document**       | Software Architecture Document (SWAD) |
| **Version**        | 0.1                                   |
| **Status**         | Draft                                 |
| **Author**         | Prathveesh N S                        |
| **Target Release** | v0.1.0                                |
| **Last Updated**   | 2026-07-06                            |

---

# 1. Introduction

This document describes the software architecture for the **FreeRTOS Sensor Data Logger** project.

The purpose of this document is to define how the firmware is organized to satisfy the functional requirements defined in `Requirements.md`.

This document intentionally focuses only on the architecture required for **Release v0.1.0**. As new functionality is introduced, the architecture will evolve and this document will be updated accordingly.

---

# 2. Purpose

The software architecture has been designed with the following objectives:

* Maintain a simple and understandable codebase.
* Clearly separate application logic from hardware access.
* Keep modules independent and reusable.
* Prevent unnecessary abstractions.
* Allow the architecture to evolve naturally as new requirements are introduced.
* Provide a structure that reflects professional embedded firmware development practices.

---

# 3. Scope

This architecture supports the functional requirements for Release **v0.1.0**, including:

* Hardware initialization
* FreeRTOS initialization
* Periodic sensor acquisition
* UART-based logging
* UART Command Line Interface (CLI)
* Runtime error reporting

The following features are intentionally excluded from this architecture:

* Multiple sensor support
* SD card logging
* External Flash support
* DMA
* CAN
* USB
* Ethernet
* Bootloader
* Low-power framework

These capabilities will be incorporated into future revisions as new requirements are introduced.

---

# 4. Design Goals

The firmware architecture has been designed around the following goals.

## Simplicity

The architecture should be easy to understand and maintain.

Only software modules required by the current release are introduced.

---

## Modularity

Each software module shall have a clearly defined responsibility and public interface.

A module should be independently understandable without requiring knowledge of unrelated modules.

---

## Maintainability

The architecture should make it straightforward to modify or extend existing functionality while minimizing changes to other modules.

---

## Scalability

Although the initial release is intentionally small, the architecture should allow additional drivers and application modules to be added without major restructuring.

---

## Low Coupling

Modules should communicate only through their public interfaces.

Implementation details shall remain private to each module.

---

# 5. Architectural Principles

The following principles guide all architectural decisions.

## AP-001 — Requirements Drive the Architecture

Software modules shall only be introduced when required by an approved functional requirement.

---

## AP-002 — Single Responsibility

Each module shall have one clearly defined responsibility.

Examples:

* Logger → Logging
* CLI → Command processing
* UART Driver → UART communication

---

## AP-003 — Encapsulation

Each module shall expose only its public interface.

Internal implementation details shall remain private.

---

## AP-004 — Hardware Isolation

Application modules shall never directly access STM32 peripheral registers.

All hardware access shall be performed through the Hardware Interface Layer.

---

## AP-005 — Incremental Growth

The architecture shall evolve only when justified by new functional requirements.

Premature abstractions shall be avoided.

---

# 6. Software Architecture

The firmware uses a lightweight three-layer architecture.

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

The architecture separates application behavior from hardware-specific implementation while avoiding unnecessary abstraction layers.

---

# 7. Layer Responsibilities

## 7.1 Application Layer

The Application Layer implements the functional behavior of the firmware.

Responsibilities include:

* System initialization
* Sensor management
* Data logging
* Command Line Interface
* FreeRTOS task creation
* Error handling

The Application Layer shall not directly access STM32 peripheral registers.

---

## 7.2 Hardware Interface Layer

The Hardware Interface Layer provides reusable interfaces for accessing hardware peripherals.

For Release **v0.1.0**, the only required hardware interface is:

* UART Driver

Responsibilities include:

* Peripheral initialization
* UART transmission
* UART reception
* Register-level hardware interaction

This layer hides all hardware-specific implementation details from the application.

---

## 7.3 CMSIS / STM32 Hardware Layer

This layer contains vendor-provided MCU support.

Components include:

* CMSIS
* STM32 register definitions
* Startup files
* Linker script

This layer provides direct access to the STM32F303 hardware.

---

# 8. Module Responsibilities

## main

Responsible for:

* System startup
* Hardware initialization
* Module initialization
* FreeRTOS scheduler startup

---

## Sensor Manager

Responsible for:

* Periodic sensor acquisition
* Sensor data collection
* Reporting acquisition failures

---

## Logger

Responsible for:

* Formatting log messages
* Transmitting log data
* Reporting runtime events

---

## CLI

Responsible for:

* Receiving UART commands
* Parsing user input
* Executing supported commands

---

## UART Driver

Responsible for:

* UART peripheral initialization
* UART transmission
* UART reception
* Register-level peripheral access

---

# 9. Dependency Rules

The firmware follows a strict top-down dependency model.

```text
Application
      │
      ▼
Hardware Interface
      │
      ▼
CMSIS / STM32 Hardware
```

Dependencies shall only flow downward.

Lower layers shall never depend on higher layers.

Examples:

✔ Logger → UART Driver

✔ CLI → UART Driver

✔ UART Driver → STM32 Registers

Examples that are not permitted:

✘ UART Driver → Logger

✘ UART Driver → Sensor Manager

✘ CMSIS → Application

---

# 10. Repository Organization

The repository is organized by software modules rather than file type.

```text
freertos-sensor-data-logger/

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
├── config/
├── docs/
└── make/
```

Each module owns its implementation and public interface.

Additional modules shall only be introduced when justified by future requirements.

---

# 11. Design Decisions

The following architectural decisions were made for Release **v0.1.0**.

## Three-Layer Architecture

A lightweight three-layer architecture was selected instead of a larger enterprise architecture.

### Rationale

* Easier to understand.
* Sufficient for current requirements.
* Avoids unnecessary complexity.

### Trade-offs

Advantages:

* Simple.
* Modular.
* Easy to maintain.

Disadvantages:

* Additional abstraction layers may be required if the project expands significantly.

---

## Module-Based Organization

Application modules and drivers are organized by module rather than file type.

### Rationale

* Improves readability.
* Keeps related files together.
* Simplifies future expansion.

---

## Requirement-Driven Module Creation

Software modules are created only when required by an approved functional requirement.

### Rationale

* Prevents unnecessary code.
* Keeps the repository focused.
* Encourages incremental development.

---

# 12. Future Evolution

Future releases may introduce:

* GPIO Driver
* I²C Driver
* Multiple sensor support
* SD card logging
* External Flash support
* DMA
* Additional communication interfaces
* Board Support Package (BSP), if multiple hardware platforms are supported

These additions will be introduced only when supported by new functional requirements.

---

# 13. Revision History

| Version | Date       | Author         | Changes                                          |
| ------- | ---------- | -------------- | ------------------------------------------------ |
| 0.1     | 2026-07-06 | Prathveesh N S | Initial software architecture for Release v0.1.0 |

---

# Appendix A — Architecture Decision Records (ADR)

This appendix records major architectural decisions made during the development of the project.

Future architectural decisions will be documented here as the firmware evolves.

## ADR-001 — Three-Layer Architecture

**Status:** Accepted

**Decision**

Use a lightweight three-layer architecture consisting of:

* Application Layer
* Hardware Interface Layer
* CMSIS / STM32 Hardware Layer

**Reason**

Provides sufficient modularity while avoiding unnecessary abstraction.

---

## ADR-002 — Module-Based Repository Organization

**Status:** Accepted

**Decision**

Each application module and hardware interface shall reside within its own directory.

**Reason**

Improves readability, ownership, and future scalability.

---

## ADR-003 — Requirement-Driven Module Creation

**Status:** Accepted

**Decision**

Software modules shall only be introduced when justified by an approved functional requirement.

**Reason**

Prevents over-engineering and ensures the architecture evolves alongside the project's requirements.
