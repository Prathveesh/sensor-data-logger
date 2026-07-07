/******************************************************************************
 * @file    uart.c
 * @brief   UART Driver implementation.
 *
 * @details
 * This file implements the UART Driver using direct register access through
 * CMSIS. The driver provides blocking transmit and receive functionality
 * for USART2 on the STM32F407 Discovery board.
 *
 * @note This file references STM32F407VGT6 (STM32F407G-DISC1).
 ******************************************************************************/

/* Includes */

#include "uart.h"
#include "stm32f407xx.h"

#include <stddef.h>

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

/* GPIO Mode: Alternate Function (0b10) */
#define UART_GPIO_MODE_AF (2U)

/* GPIO Output Speed: High (0b10) */
#define UART_GPIO_SPEED_HIGH (2U)

/* GPIO Output Type: Push-Pull (0b0) */
#define UART_GPIO_OTYPE_PP (0U)

/* GPIO Pull-Up (0b01) */
#define UART_GPIO_PULL_UP (1U)

/* GPIO Register Field Masks */
#define UART_GPIO_MODE_MASK (0x3U)
#define UART_GPIO_AF_MASK (0xFU)

/* UART Configuration */
#define UART_BAUDRATE (115200U)

/*
 * Assumes HSI (16 MHz) with no PLL and APB1 prescaler = 1.
 * This macro will be replaced once the Clock Driver is introduced.
 */
#define UART_PERIPHERAL_CLOCK_HZ (16000000U)
#define UART_BRR_VALUE (UART_PERIPHERAL_CLOCK_HZ / UART_BAUDRATE)

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

UART_Status_t UART_Write(const uint8_t *buffer, uint32_t length) {
  UART_Status_t status = UART_STATUS_OK;

  if ((buffer == NULL) || (length == 0U)) {
    return UART_STATUS_INVALID_PARAMETER;
  }

  for (uint32_t i = 0U; i < length; i++) {
    status = UART_WriteByte(buffer[i]);

    if (status != UART_STATUS_OK) {
      return status;
    }
  }

  return UART_STATUS_OK;
}

UART_Status_t UART_ReadByte(uint8_t *data) {
  if (data == NULL) {
    return UART_STATUS_INVALID_PARAMETER;
  }

  /* Wait until RXNE (Read Data Register Not Empty) is set */
  while ((UART_INSTANCE->SR & USART_SR_RXNE) == 0U) {
    /* Blocking wait */
  }

  *data = (uint8_t)(UART_INSTANCE->DR & 0xFFU);

  return UART_STATUS_OK;
}

/* Private Function Definitions */

/**
 * @brief Enable peripheral clocks for GPIOA and USART2.
 */
static void UART_EnablePeripheralClock(void) {
  /* Enable GPIOA clock (AHB1) */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  /* Enable USART2 clock (APB1) */
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

  /* Read-back to ensure clocks are active before peripheral access */
  (void)RCC->AHB1ENR;
  (void)RCC->APB1ENR;
}

/**
 * @brief Configure PA2 (TX) and PA3 (RX) as USART2 alternate function pins.
 */
static void UART_ConfigureGPIO(void) {
  /* Configure PA2 (TX) as Alternate Function */
  UART_GPIO_PORT->MODER &= ~(UART_GPIO_MODE_MASK << (UART_TX_PIN * 2U));
  UART_GPIO_PORT->MODER |= (UART_GPIO_MODE_AF << (UART_TX_PIN * 2U));

  /* Configure PA3 (RX) as Alternate Function */
  UART_GPIO_PORT->MODER &= ~(UART_GPIO_MODE_MASK << (UART_RX_PIN * 2U));
  UART_GPIO_PORT->MODER |= (UART_GPIO_MODE_AF << (UART_RX_PIN * 2U));

  /* Set output type to Push-Pull for TX pin */
  UART_GPIO_PORT->OTYPER &= ~(1U << UART_TX_PIN);
  UART_GPIO_PORT->OTYPER |= (UART_GPIO_OTYPE_PP << UART_TX_PIN);

  /* Set output type to Push-Pull for RX pin */
  UART_GPIO_PORT->OTYPER &= ~(1U << UART_RX_PIN);
  UART_GPIO_PORT->OTYPER |= (UART_GPIO_OTYPE_PP << UART_RX_PIN);

  /* Set output speed to High for TX pin */
  UART_GPIO_PORT->OSPEEDR &= ~(UART_GPIO_MODE_MASK << (UART_TX_PIN * 2U));
  UART_GPIO_PORT->OSPEEDR |= (UART_GPIO_SPEED_HIGH << (UART_TX_PIN * 2U));

  /* Set output speed to High for RX pin */
  UART_GPIO_PORT->OSPEEDR &= ~(UART_GPIO_MODE_MASK << (UART_RX_PIN * 2U));
  UART_GPIO_PORT->OSPEEDR |= (UART_GPIO_SPEED_HIGH << (UART_RX_PIN * 2U));

  /* Set pull-up for TX pin */
  UART_GPIO_PORT->PUPDR &= ~(UART_GPIO_MODE_MASK << (UART_TX_PIN * 2U));
  UART_GPIO_PORT->PUPDR |= (UART_GPIO_PULL_UP << (UART_TX_PIN * 2U));

  /* Set pull-up for RX pin */
  UART_GPIO_PORT->PUPDR &= ~(UART_GPIO_MODE_MASK << (UART_RX_PIN * 2U));
  UART_GPIO_PORT->PUPDR |= (UART_GPIO_PULL_UP << (UART_RX_PIN * 2U));

  /* Select AF7 (USART2) for PA2 via AFRL (pins 0-7 use AFR[0]) */
  UART_GPIO_PORT->AFR[0] &= ~(UART_GPIO_AF_MASK << (UART_TX_PIN * 4U));
  UART_GPIO_PORT->AFR[0] |= (UART_GPIO_AF << (UART_TX_PIN * 4U));

  /* Select AF7 (USART2) for PA3 via AFRL */
  UART_GPIO_PORT->AFR[0] &= ~(UART_GPIO_AF_MASK << (UART_RX_PIN * 4U));
  UART_GPIO_PORT->AFR[0] |= (UART_GPIO_AF << (UART_RX_PIN * 4U));
}

/**
 * @brief Configure USART2 for 8N1, 115200 baud, TX/RX enabled.
 */
static void UART_ConfigureUSART(void) {
  /* Disable USART before configuration */
  UART_INSTANCE->CR1 &= ~USART_CR1_UE;

  /* Clear CR1: 8 data bits (M=0), no parity (PCE=0), oversampling 16 (OVER8=0) */
  UART_INSTANCE->CR1 = 0U;

  /* Clear CR2: 1 stop bit (STOP=00) */
  UART_INSTANCE->CR2 = 0U;

  /* Clear CR3: no flow control (CTSE=0, RTSE=0), no DMA */
  UART_INSTANCE->CR3 = 0U;

  /* Set baud rate */
  UART_INSTANCE->BRR = UART_BRR_VALUE;

  /* Enable transmitter and receiver */
  UART_INSTANCE->CR1 |= (USART_CR1_TE | USART_CR1_RE);

  /* Enable USART */
  UART_INSTANCE->CR1 |= USART_CR1_UE;
}

/**
 * @brief Transmit a single byte over USART2 using polling.
 *
 * @param[in] data  Byte to transmit.
 *
 * @retval UART_STATUS_OK  Byte transmitted successfully.
 */
static UART_Status_t UART_WriteByte(uint8_t data) {
  /* Wait until TXE (Transmit Data Register Empty) is set */
  while ((UART_INSTANCE->SR & USART_SR_TXE) == 0U) {
    /* Blocking wait */
  }

  UART_INSTANCE->DR = (uint32_t)data;

  /* Wait until TC (Transmission Complete) is set */
  while ((UART_INSTANCE->SR & USART_SR_TC) == 0U) {
    /* Blocking wait */
  }

  return UART_STATUS_OK;
}