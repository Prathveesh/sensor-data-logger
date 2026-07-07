/******************************************************************************
 * @file    main.c
 * @brief   Application entry point for UART hardware bring-up.
 *
 * @details
 * Minimal firmware entry point for validating the UART driver on the
 * STM32F407G-DISC1. Initializes USART2 and transmits a startup banner
 * to confirm the hardware bring-up is successful.
 *
 * This file will be expanded as additional modules are introduced.
 ******************************************************************************/

/* Includes */

#include "uart.h"

#include <stdint.h>
#include <string.h>

/* Private Macros */

#define STARTUP_BANNER \
  "\r\n" \
  "================================================\r\n" \
  "  FreeRTOS Sensor Data Logger v0.1.0\r\n" \
  "  Target: STM32F407G-DISC1\r\n" \
  "  UART Bring-Up Successful\r\n" \
  "================================================\r\n" \
  "\r\n"

/* Private Function Prototypes */

static void App_TransmitBanner(void);

/* Application Entry Point */

int main(void) {
  UART_Init();

  App_TransmitBanner();

  /* Main loop — no application logic for this milestone */
  for (;;) {
    /* Idle */
  }
}

/* Private Function Definitions */

/**
 * @brief Transmit the startup banner over UART.
 */
static void App_TransmitBanner(void) {
  const char *banner = STARTUP_BANNER;

  UART_Write((const uint8_t *)banner, (uint32_t)strlen(banner));
}
