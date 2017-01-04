#ifndef __I2C_H
#define __I2C_H
#include "stm8l15x.h"

/* Exported macros -----------------------------------------------------------*/
#define I2C_PORT        GPIOC
#define I2C_SCL_PIN     GPIO_Pin_1
#define I2C_SDA_PIN     GPIO_Pin_0
#define I2C_DELAY       DelayUS(0) 

#define QN8006
#define DEVICE_ADDR     0x56

/* Exported function -----------------------------------------------*/
void I2C_Init(void);
void I2C_WriteByte(uint8_t write_addr, uint8_t data);
void I2C_Read(uint8_t* pbuff, uint8_t write_addr, uint16_t num_byte);
void I2C_Write(const uint8_t* pbuff, uint8_t write_addr, uint16_t num_byte);
#endif			

/************************************ End of file **********************************/

