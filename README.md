# FreeRTOS Sensor Data Logger

A production-style embedded firmware project built from scratch using **Embedded C**, **FreeRTOS**, and the **STM32F3 Discovery (STM32F303VCT6)** development board.

This project is designed as a learning journey through professional embedded software development rather than a simple coding exercise. Every design decision, module, and implementation follows software engineering practices commonly used in automotive and industrial firmware teams.

---

# Project Overview

A **Sensor Data Logger** is an embedded system that periodically collects data from one or more sensors, processes it if necessary, stores it, and makes it available for monitoring or analysis.

At its core, every data logger answers four questions:

1. What should I measure?
2. When should I measure it?
3. Where should I store it?
4. How should the data be retrieved?

This project will implement a modular, scalable, and reusable sensor data logger using **FreeRTOS**, with an architecture suitable for real-world embedded products.

---

# Objectives

The primary goals of this project are to:

* Design firmware using a layered software architecture.
* Develop reusable register-level drivers without relying on STM32CubeMX-generated application code.
* Learn FreeRTOS task scheduling and inter-task communication.
* Implement modular firmware components that are easy to extend and maintain.
* Build the project using the GNU ARM Toolchain and GNU Make.
* Practice professional Git workflows and repository organization.
* Produce documentation that reflects industry standards.

---

# Target Hardware

| Component            | Details           |
| -------------------- | ----------------- |
| Development Board    | STM32F3 Discovery |
| MCU                  | STM32F303VCT6     |
| Core                 | ARM Cortex-M4F    |
| Programming Language | Embedded C (C99)  |
| RTOS                 | FreeRTOS          |
| Compiler             | arm-none-eabi-gcc |
| Build System         | GNU Make          |
| IDE                  | VS Code           |
| Debugger             | ST-Link GDB       |
| Version Control      | Git & GitHub      |

---

# Why Build a Sensor Data Logger?

Sensor data logging is widely used across multiple industries.

## Automotive

* Engine temperature monitoring
* Battery voltage logging
* Oil pressure monitoring
* Vehicle diagnostics
* CAN bus data recording

## Industrial Automation

* Motor monitoring
* Pump diagnostics
* Vibration analysis
* Pressure and temperature logging
* Predictive maintenance

## Medical Devices

* Heart rate monitoring
* Blood pressure logging
* Temperature measurement
* Oxygen saturation recording

## Agriculture

* Soil moisture monitoring
* Temperature logging
* Humidity measurement
* Environmental data collection

## Aerospace

* Flight telemetry
* Accelerometer logging
* Pressure monitoring
* Sensor diagnostics

## IoT Systems

* Smart home sensors
* Air quality monitoring
* Power consumption logging
* Environmental monitoring

---

# High-Level System Overview

```text
               STM32F303

        +----------------------+
        |  FreeRTOS Scheduler  |
        +----------+-----------+
                   |
      +------------+-------------+
      |            |             |
      v            v             v
 Sensor Task   Logger Task   CLI Task
      |            |             |
      +------------+-------------+
                   |
                   v
             UART / Storage
```

Initially, logged sensor data will be transmitted over UART for easy observation. The architecture will later support additional storage backends such as SD cards or external flash memory.

---

# Why FreeRTOS?

As embedded applications grow, managing multiple independent activities in a single `while(1)` loop becomes increasingly difficult.

FreeRTOS enables the application to be divided into independent tasks such as:

* Sensor acquisition
* Data logging
* Command-line interface
* Future communication services

This results in cleaner, more maintainable, and scalable firmware.

---

# Learning Outcomes

By completing this project, you will gain practical experience with:

## Firmware Architecture

* Layered architecture
* Module boundaries
* API design
* Dependency management

## Embedded C

* Modular programming
* Header/source separation
* Static functions
* Memory ownership
* Reusable interfaces

## FreeRTOS

* Task creation
* Scheduling
* Queues
* Mutexes
* Semaphores
* Event groups
* Software timers
* ISR interaction

## Driver Development

* Register-level programming
* Manual peripheral drivers
* Hardware abstraction
* Portable driver design

## Build Systems

* GNU Make
* Cross-compilation
* Linker scripts
* Compiler flags
* Startup files

## Debugging

* ST-Link
* GDB
* OpenOCD
* HardFault analysis
* Stack overflow detection

## Version Control

* Professional Git workflow
* Feature branches
* Pull requests
* Semantic versioning
* Tagged releases

## Documentation

* README
* Architecture documentation
* Build guides
* Developer documentation
* API documentation

---

# Skills Demonstrated

This project showcases practical firmware engineering skills including:

* Embedded firmware architecture
* Register-level driver development
* FreeRTOS-based multitasking
* Embedded C best practices
* Hardware abstraction
* Concurrent software design
* GNU Make build system
* Professional Git workflow
* Firmware debugging
* Technical documentation

---

# Common Beginner Misconceptions

| Misconception                                  | Reality                                                                        |
| ---------------------------------------------- | ------------------------------------------------------------------------------ |
| FreeRTOS is the entire architecture.           | FreeRTOS is only one layer of the software stack.                              |
| Drivers should know about the application.     | Drivers should remain reusable and independent.                                |
| Global variables solve communication problems. | Proper ownership and encapsulation improve maintainability.                    |
| Code first, design later.                      | Production firmware begins with requirements and architecture.                 |
| If it works, it is complete.                   | Production firmware also requires testing, documentation, and maintainability. |

---

# Engineering Principles

This project emphasizes production-quality firmware development by focusing on:

* Maintainability
* Scalability
* Modularity
* Deterministic behavior
* Resource efficiency
* Portability
* Testability
* Documentation

---

# Repository Roadmap

This project will be developed incrementally through the following stages:

* Project Introduction
* Requirements Analysis
* System Architecture
* Software Design
* FreeRTOS Task Design
* Repository Organization
* Build System
* Git Workflow
* Incremental Implementation
* Testing
* Debugging
* Documentation
* GitHub Portfolio Optimization
* Interview Preparation
* Future Enhancements

---

# Planned Features

* Register-level STM32 peripheral drivers
* FreeRTOS-based multitasking
* Modular sensor framework
* UART logging
* Command Line Interface (CLI)
* Configurable logging intervals
* Scalable storage abstraction
* Future SD card support
* Future DMA integration
* Future CAN support
* Future USB CDC support

---

# Project Status

> 🚧 **Work in Progress**

This repository is being developed chapter by chapter, following a structured firmware engineering process similar to that used in professional embedded software teams.

---

# License

This project will be released under the **MIT License** unless otherwise specified.
