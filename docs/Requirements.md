# Software Requirements Specification (SRS)

**Project:** FreeRTOS Sensor Data Logger

**Target MCU:** STM32F407VGT6

**Development Board:** STM32F407G-DISC1

**Document Version:** 0.1

**Project Release:** v0.1.0

---

# 1. Introduction

This document defines the software requirements for the first release of the **FreeRTOS Sensor Data Logger** project.

The objective of this release is to develop a modular embedded firmware application capable of periodically acquiring sensor data, logging the collected information over UART, and providing a basic command-line interface (CLI) for user interaction.

This document intentionally defines only the requirements for the first release (v0.1.0). Additional functionality such as SD card logging, DMA support, persistent configuration, and multiple sensor support will be specified in future revisions.

---

# 2. Scope

The firmware shall:

* Initialize the STM32F407G-DISC1 board.
* Initialize the FreeRTOS kernel.
* Periodically acquire sensor data.
* Log sensor data over UART.
* Provide a UART-based CLI.
* Detect and report basic runtime errors.
* Follow a modular software architecture.

The following features are **out of scope** for Release v0.1.0:

* SD Card logging
* External Flash support
* DMA-based UART
* CAN communication
* USB CDC
* BLE
* Ethernet
* OTA updates
* Persistent configuration storage
* Multiple sensor support

---

# 3. Functional Requirements

## REQ-FR-001 — System Initialization

**Requirement**

The firmware shall initialize all required hardware peripherals before starting the application.

**Rationale**

Ensures all hardware resources are configured before application execution begins.

---

## REQ-FR-002 — FreeRTOS Initialization

**Requirement**

The firmware shall initialize the FreeRTOS kernel and create all required application tasks before starting the scheduler.

**Rationale**

Ensures the system enters multitasking mode in a controlled and deterministic manner.

---

## REQ-FR-003 — Periodic Sensor Acquisition

**Requirement**

The firmware shall periodically acquire data from the configured sensor.

**Rationale**

Provides continuous monitoring of sensor data.

---

## REQ-FR-004 — Configurable Sampling Period

**Requirement**

The firmware shall support a configurable sensor sampling interval.

**Rationale**

Allows future runtime adjustment without modifying application logic.

---

## REQ-FR-005 — Sensor Data Logging

**Requirement**

The firmware shall transmit acquired sensor data over the UART interface.

**Rationale**

Provides visibility into system operation and enables external monitoring.

---

## REQ-FR-006 — Logging Sequence Number

**Requirement**

Each logged sensor sample shall include a monotonically increasing sequence number.

**Rationale**

Allows detection of missing or duplicated log entries during debugging.

---

## REQ-FR-007 — UART Command Line Interface

**Requirement**

The firmware shall provide a UART-based command-line interface.

**Rationale**

Allows user interaction without requiring firmware modification.

---

## REQ-FR-008 — System Status Command

**Requirement**

The command-line interface shall provide a command to display current system status.

**Minimum Information**

* Firmware version
* System uptime
* Sampling period
* Number of collected samples

**Rationale**

Provides basic runtime diagnostics.

---

## REQ-FR-009 — Sampling Configuration Command

**Requirement**

The command-line interface shall provide a command for changing the sensor sampling interval.

**Rationale**

Allows runtime configuration for testing and demonstration.

---

## REQ-FR-010 — Invalid Command Handling

**Requirement**

The firmware shall detect invalid CLI commands and return an informative error message without affecting system operation.

**Rationale**

Improves robustness and user experience.

---

## REQ-FR-011 — Sensor Read Failure Detection

**Requirement**

The firmware shall detect failures during sensor acquisition and report an error through the logging interface.

**Rationale**

Provides visibility into hardware or communication failures.

---

## REQ-FR-012 — Runtime Error Reporting

**Requirement**

The firmware shall report application-level runtime errors through the logging interface.

**Rationale**

Facilitates debugging and fault diagnosis.

---

## REQ-FR-013 — Modular Software Design

**Requirement**

The firmware shall organize application functionality into independent software modules with clearly defined public interfaces.

**Rationale**

Improves maintainability, readability, and future extensibility.

---

# 4. Requirement Summary

| Requirement ID | Description                                         |
| -------------- | --------------------------------------------------- |
| REQ-FR-001     | Initialize required hardware                        |
| REQ-FR-002     | Initialize FreeRTOS and application tasks           |
| REQ-FR-003     | Periodically acquire sensor data                    |
| REQ-FR-004     | Support configurable sampling interval              |
| REQ-FR-005     | Log sensor data over UART                           |
| REQ-FR-006     | Include a sequence number in each log entry         |
| REQ-FR-007     | Provide a UART command-line interface               |
| REQ-FR-008     | Display system status through the CLI               |
| REQ-FR-009     | Allow runtime modification of the sampling interval |
| REQ-FR-010     | Handle invalid CLI commands gracefully              |
| REQ-FR-011     | Detect sensor read failures                         |
| REQ-FR-012     | Report runtime errors                               |
| REQ-FR-013     | Maintain a modular firmware architecture            |

---

# 5. Future Requirements

The following capabilities are planned for future releases and are intentionally excluded from Release v0.1.0:

* Multiple sensor support
* SD card logging
* External flash logging
* DMA-based UART transmission
* Configuration persistence
* USB CDC
* CAN communication
* BLE communication
* Ethernet support
* LittleFS integration
* OTA firmware updates
* Power optimization
* Secure boot
* Bootloader integration

---

# Revision History

| Version | Date            | Description                                |
| ------- | --------------- | ------------------------------------------ |
| 0.1     | Initial Release | Functional requirements for Release v0.1.0 |
