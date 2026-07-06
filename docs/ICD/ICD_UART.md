# Interface Control Document (ICD)

# UART Driver

| **Item**           | **Value**                        |
| ------------------ | -------------------------------- |
| **Project**        | FreeRTOS Sensor Data Logger      |
| **Document**       | Interface Control Document (ICD) |
| **Module**         | UART Driver                      |
| **Version**        | 0.1                              |
| **Status**         | Draft                            |
| **Author**         | Prathveesh N S                   |
| **Target Release** | v0.1.0                           |
| **Last Updated**   | 2026-07-06                       |

---

# 1. Introduction

This document defines the public software interface for the UART Driver.

The UART Driver provides a hardware abstraction for the STM32F303 UART peripheral and is responsible for all UART-related register access.

This document is the authoritative specification for the UART Driver interface. The corresponding `uart.h` file shall be derived directly from this document.

---

# 2. Purpose

The UART Driver provides a reusable interface for:

* Initializing the UART peripheral.
* Transmitting data.
* Receiving data.
* Isolating hardware register access from application modules.

The driver shall not contain application-specific logic.

---

# 3. Scope

This document covers the public interface required for Release **v0.1.0**.

Supported functionality:

* UART peripheral initialization
* Blocking transmit
* Blocking receive

Not included in this release:

* DMA
* Interrupt-driven communication
* Ring buffers
* Multiple UART instances
* Flow control
* RS-485 support

---

# 4. Dependencies

## Hardware

* STM32F303VCT6 MCU
* USART peripheral

## Software

* CMSIS
* STM32 Register Definitions

No dependency on application modules is permitted.

---

# 5. Module Responsibilities

The UART Driver shall:

* Configure the UART peripheral.
* Configure UART GPIO pins.
* Configure UART baud rate.
* Transmit bytes.
* Receive bytes.
* Report operation status.

The UART Driver shall **not**:

* Format log messages.
* Parse CLI commands.
* Manage application buffers.
* Perform protocol-specific processing.

---

# 6. Public Include File

```text
drivers/uart/uart.h
```

---

# 7. Public Enumerations

## UART_Status_t

Represents the status returned by public UART APIs.

### Enumeration Values

| Value                         | Description                       |
| ----------------------------- | --------------------------------- |
| UART_STATUS_OK                | Operation completed successfully. |
| UART_STATUS_ERROR             | General driver error.             |
| UART_STATUS_BUSY              | UART peripheral is busy.          |
| UART_STATUS_TIMEOUT           | Operation timed out.              |
| UART_STATUS_INVALID_PARAMETER | Invalid API argument.             |

---

# 8. Public Structures

## UART_Config_t

Stores the UART peripheral configuration.

### Members

| Member    | Description            |
| --------- | ---------------------- |
| baudrate  | UART baud rate         |
| data_bits | Number of data bits    |
| stop_bits | Stop bit configuration |
| parity    | Parity configuration   |

The exact member data types will be defined in `uart.h`.

---

# 9. Public API

## UART_Init()

### Prototype

```c
UART_Status_t UART_Init(const UART_Config_t *config);
```

### Description

Initializes the UART peripheral using the supplied configuration.

### Parameters

| Name   | Direction | Description                  |
| ------ | --------- | ---------------------------- |
| config | IN        | UART configuration structure |

### Returns

| Value                         | Description               |
| ----------------------------- | ------------------------- |
| UART_STATUS_OK                | Initialization successful |
| UART_STATUS_ERROR             | Initialization failed     |
| UART_STATUS_INVALID_PARAMETER | Invalid configuration     |

### Preconditions

* System clock configured.
* Configuration pointer is valid.

### Postconditions

* UART peripheral is initialized.
* UART is ready for transmit and receive.

### Thread Safety

Not thread-safe.

Intended to be called once during system startup.

---

## UART_Write()

### Prototype

```c
UART_Status_t UART_Write(const uint8_t *buffer,
                         uint32_t length);
```

### Description

Transmits a sequence of bytes using blocking mode.

### Parameters

| Name   | Direction | Description                 |
| ------ | --------- | --------------------------- |
| buffer | IN        | Pointer to transmit buffer  |
| length | IN        | Number of bytes to transmit |

### Returns

| Value                         | Description            |
| ----------------------------- | ---------------------- |
| UART_STATUS_OK                | Transmission completed |
| UART_STATUS_ERROR             | Transmission failed    |
| UART_STATUS_INVALID_PARAMETER | Invalid arguments      |

### Preconditions

* UART initialized.
* Buffer pointer valid.
* Length greater than zero.

### Postconditions

* All requested bytes transmitted.

### Thread Safety

Not thread-safe.

Mutual exclusion shall be provided by higher software layers if multiple tasks access the driver.

---

## UART_Read()

### Prototype

```c
UART_Status_t UART_Read(uint8_t *buffer,
                        uint32_t length);
```

### Description

Receives bytes using blocking mode.

### Parameters

| Name   | Direction | Description               |
| ------ | --------- | ------------------------- |
| buffer | OUT       | Receive buffer            |
| length | IN        | Number of bytes requested |

### Returns

| Value               | Description          |
| ------------------- | -------------------- |
| UART_STATUS_OK      | Reception successful |
| UART_STATUS_TIMEOUT | Receive timeout      |
| UART_STATUS_ERROR   | Reception failed     |

### Preconditions

* UART initialized.

### Postconditions

* Requested data stored in buffer.

### Thread Safety

Not thread-safe.

---

# 10. Error Handling

The UART Driver shall detect and report:

* Invalid parameters
* Peripheral initialization failures
* Timeout conditions
* Hardware communication failures

The driver shall not reset or recover the application.

Recovery decisions remain the responsibility of higher software layers.

---

# 11. Usage

Typical initialization sequence:

```text
main()

↓

UART_Init()

↓

Logger_Init()

↓

CLI_Init()

↓

Start Scheduler
```

Typical transmit flow:

```text
Logger

↓

UART_Write()

↓

USART Peripheral

↓

Serial Terminal
```

Typical receive flow:

```text
Serial Terminal

↓

USART Peripheral

↓

UART_Read()

↓

CLI
```

---

# 12. Design Constraints

The driver shall:

* Use Embedded C (C99)
* Follow practical MISRA-C guidelines
* Hide register-level implementation
* Expose only documented public APIs
* Avoid dynamic memory allocation

---

# 13. Future Extensions

The following capabilities are planned for future releases:

* Interrupt-driven UART
* DMA support
* Circular transmit buffer
* Circular receive buffer
* Configurable timeout
* Multiple UART peripheral support

These features are outside the scope of Release v0.1.0.

---

# 14. Traceability

| Requirement ID | Description            | Implemented By            |
| -------------- | ---------------------- | ------------------------- |
| REQ-FR-005     | UART-based logging     | UART_Write()              |
| REQ-FR-007     | UART CLI communication | UART_Read(), UART_Write() |

---

# 15. Revision History

| Version | Date       | Author         | Changes                                 |
| ------- | ---------- | -------------- | --------------------------------------- |
| 0.1     | 2026-07-06 | Prathveesh N S | Initial UART Interface Control Document |
