#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
void delay_us(uint16_t us);
void i2c_end(void);
void i2c_start(void);
uint8_t wait_ack(void);
void i2c_ack(void);
void i2c_nack(void);
void i2c_send_byte(uint8_t data);
uint8_t i2c_read_byte(uint8_t ack);

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
#ifdef __cplusplus
}
#endif

#endif