/******************************************************************************
 * @file    uart.c
 * @brief   UART Driver implementation.
 *
 * @details
 * This file implements the UART Driver using direct register access through
 * CMSIS. The driver provides blocking transmit and receive functionality
 * for USART2 on the STM32F303 Discovery board.
 ******************************************************************************/

/* Includes */

#include "uart.h"

// #include "stm32f407xx.h"

/* Private Macros */

/* USART Instance */
#define UART_INSTANCE (USART2)

/* GPIO Port */
#define UART_GPIO_PORT (GPIOA)

/* GPIO Pin Configuration */
#define UART_TX_PIN (2U)
#define UART_RX_PIN (3U)

/* GPIO Alternate Function */
#define UART_GPIO_AF (7U)

/* UART Configuration */
#define UART_BAUDRATE (115200U)

/*
 * NOTE:
 *
 * For Release v1.0 we assume the APB1 peripheral clock driving USART2
 * is configured to 8 MHz.
 *
 * BRR = PCLK / BaudRate
 *
 * 8000000 / 115200 = 69 (0x45)
 *
 * This value will later be calculated automatically once the Clock Driver
 * is introduced into the project.
 */
#define UART_BRR_VALUE (69U)

/* Private Function Prototypes */

static void UART_EnablePeripheralClock(void);

static void UART_ConfigureGPIO(void);

static void UART_ConfigureUSART(void);

static UART_Status_t UART_WriteByte(uint8_t data);

/* Public Function Definitions */

UART_Status_t UART_Init(void) {
  UART_EnablePeripheralClock();

  UART_ConfigureGPIO();

  UART_ConfigureUSART();

  return UART_STATUS_OK;
}