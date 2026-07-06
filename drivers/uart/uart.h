/******************************************************************************
 * @file    uart.h
 * @brief   Public interface for the UART Driver.
 *
 * @details
 * The UART Driver provides a hardware abstraction for the STM32F303 UART
 * peripheral. It exposes only the interfaces required by higher software
 * layers while hiding all hardware-specific implementation details.
 ******************************************************************************/

#ifndef FSDL_UART_H
#define FSDL_UART_H

/* Includes */

#include <stdint.h>

/* Public Macros */

/* No public macros defined for Release v0.1.0 */

/* Public Enumerations */

/**
 * @brief UART Driver operation status.
 */
typedef enum {
  UART_STATUS_OK = 0U,          /**< Operation completed successfully. */
  UART_STATUS_ERROR,            /**< General driver error. */
  UART_STATUS_INVALID_PARAMETER /**< Invalid function parameter. */

} UART_Status_t;

/* Public Structures */

/* No public structures defined for Release v0.1.0 */

/* Public Typedefs */

/* No public typedefs defined for Release v0.1.0 */

/* Public Function Prototypes */

/**
 * @brief Initialize the UART peripheral.
 *
 * @details
 * Initializes the UART peripheral using the project-defined configuration.
 * This function shall be called once during system initialization before any
 * UART transmit or receive operation is performed.
 *
 * @retval UART_STATUS_OK     UART initialized successfully.
 * @retval UART_STATUS_ERROR  UART initialization failed.
 */
UART_Status_t UART_Init(void);

/**
 * @brief Transmit a buffer over UART.
 *
 * @details
 * Transmits the specified number of bytes using blocking mode.
 * The function returns only after all bytes have been transmitted or an
 * error occurs.
 *
 * @param[in]  buffer  Pointer to the transmit buffer.
 * @param[in]  length  Number of bytes to transmit.
 *
 * @retval UART_STATUS_OK                 Transmission completed successfully.
 * @retval UART_STATUS_ERROR              Transmission failed.
 * @retval UART_STATUS_INVALID_PARAMETER  Invalid input arguments.
 */
UART_Status_t UART_Write(const uint8_t *buffer, uint32_t length);

/**
 * @brief Receive a single byte over UART.
 *
 * @details
 * Receives one byte using blocking mode and stores it in the user-provided
 * memory location.
 *
 * @param[out] data  Pointer to the memory location where the received byte
 *                   shall be stored.
 *
 * @retval UART_STATUS_OK                 Byte received successfully.
 * @retval UART_STATUS_ERROR              Receive operation failed.
 * @retval UART_STATUS_INVALID_PARAMETER  Invalid input arguments.
 */
UART_Status_t UART_ReadByte(uint8_t *data);

#endif /* FSDL_UART_H */
