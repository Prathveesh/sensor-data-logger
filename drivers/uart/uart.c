/******************************************************************************
 * @file    uart.c
 * @brief   UART Driver implementation.
 *
 * @details
 * This file implements the UART Driver public interface and contains all
 * private helper functions required to configure and operate the UART
 * peripheral.
 ******************************************************************************/

/* Includes */

#include "uart.h"

// #include "stm32f303xc.h"

/* Private Macros */

/* USART2 Peripheral */
#define UART_INSTANCE USART2

/* GPIO Configuration */
#define UART_GPIO_PORT GPIOA
#define UART_TX_PIN (2U)
#define UART_RX_PIN (3U)
#define UART_GPIO_AF (7U)

/* UART Configuration */
#define UART_BAUDRATE (115200U)

/* Private Function Prototypes */

static void UART_EnableClock(void);
static void UART_ConfigureGPIO(void);
static void UART_ConfigurePeripheral(void);

static UART_Status_t UART_WriteByte(uint8_t data);

/* Public Function Definitions */

UART_Status_t UART_Init(void) {
  /* Implementation */

  return UART_STATUS_OK;
}

UART_Status_t UART_Write(const uint8_t *buffer, uint32_t length) {
  /* Implementation */

  return UART_STATUS_OK;
}

UART_Status_t UART_ReadByte(uint8_t *data) {
  /* Implementation */

  return UART_STATUS_OK;
}

/* Private Function Definitions */

static void UART_EnableClock(void) {}

static void UART_ConfigureGPIO(void) {}

static void UART_ConfigurePeripheral(void) {}

static UART_Status_t UART_WriteByte(uint8_t data) {
  (void)data;

  return UART_STATUS_OK;
}