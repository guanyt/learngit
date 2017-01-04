#include "i2c.h"

/* Private macro -------------------------------------------------------------*/
#define SCL_OUT_HIGH     (I2C_PORT->ODR |= I2C_SCL_PIN)
#define SDA_OUT_HIGH     (I2C_PORT->ODR |= I2C_SDA_PIN)
#define SCL_OUT_LOW      (I2C_PORT->ODR &= ~I2C_SCL_PIN)
#define SDA_OUT_LOW      (I2C_PORT->ODR &= ~I2C_SDA_PIN)
#define READ_SDA_IN      ((BitStatus)(I2C_PORT->IDR & (uint8_t)I2C_SDA_PIN))

/* Private function prototypes -----------------------------------------------*/
static void I2C_Start(void);
static void I2C_Stop(void);
static void I2C_SendData(uint8_t data);
static void I2C_AcknowledgeConfig(FunctionalState NewState);
static uint8_t I2C_ReceiveData(void);
static uint8_t I2C_CheckAcknowledge(void);


/**
 *
 */
void I2C_Init(void)
{
	GPIO_Init(I2C_PORT, I2C_SCL_PIN, GPIO_Mode_Out_OD_Low_Slow);
	GPIO_Init(I2C_PORT, I2C_SDA_PIN, GPIO_Mode_Out_OD_Low_Slow);
	
	GPIO_SetBits(I2C_PORT, I2C_SCL_PIN);	
	GPIO_SetBits(I2C_PORT, I2C_SDA_PIN);	
}


/**
 *
 */
void I2C_WriteByte(uint8_t write_addr, uint8_t data)
{
	I2C_Start();
	
	/* Send Device Address */
	I2C_SendData(DEVICE_ADDR & 0xFE);
	while (I2C_CheckAcknowledge());
	
	/* Send Word Address */
	I2C_SendData(write_addr);
	while (I2C_CheckAcknowledge());
	
	/* Send Data */
	I2C_SendData(data);
	while (I2C_CheckAcknowledge());
	
	I2C_Stop();
}


/**
 *
 */
void I2C_Write(const uint8_t* pbuff, uint8_t write_addr, uint16_t num_byte)
{
	I2C_Start();
	
	/* Send Device Address */
	I2C_SendData(DEVICE_ADDR & 0xFE);
	while (I2C_CheckAcknowledge());
	
	/* Send Word Address */
	I2C_SendData(write_addr);
	while (I2C_CheckAcknowledge());
		
	/* Send Data */
	while (num_byte--) {
		I2C_SendData(*pbuff);
		while (I2C_CheckAcknowledge());
		pbuff++;
	}

	I2C_Stop();
}



/**
 *
 */
void I2C_Read(uint8_t* pbuff, uint8_t write_addr, uint16_t num_byte)
{
	I2C_Start();
	
	/* Send Device Address */
	I2C_SendData(DEVICE_ADDR | 0x01);
	while (I2C_CheckAcknowledge());
	
	/* Send Word Address */
	I2C_SendData(write_addr);
	while (I2C_CheckAcknowledge());
#ifndef QN8006	
	/* Regenerate Start Condition */
	I2C_Start();
	
	/* Send Device Address */
	I2C_SendData(DEVICE_ADDR | 0x01);
	while (I2C_CheckAcknowledge());
#endif
	/* Receive Data */
	while (num_byte) {
		*pbuff = I2C_ReceiveData();
			
		if (num_byte > 1) {
			I2C_AcknowledgeConfig(ENABLE);
    	}
		pbuff++;
		num_byte--;
	}
	
	I2C_AcknowledgeConfig(DISABLE);
	I2C_Stop();
}


/**
 *
 */
static void DelayUS(uint16_t nCount)
{	
	while (nCount--) {
		nop();
	}
}  


/**
 *
 */
static void I2C_Start(void)
{
	SCL_OUT_LOW;
	SDA_OUT_HIGH;
	I2C_DELAY;
	SCL_OUT_HIGH;
	I2C_DELAY;
	SDA_OUT_LOW;
	I2C_DELAY;
}


/**
 *
 */
static void I2C_Stop(void)
{
	SCL_OUT_LOW;
	SDA_OUT_LOW;
	I2C_DELAY;
	SCL_OUT_HIGH;
	I2C_DELAY;
	SDA_OUT_HIGH;
	I2C_DELAY;
}


/**
 *
 */
static void I2C_AcknowledgeConfig(FunctionalState NewState)
{
	if (NewState == ENABLE) {
		SDA_OUT_LOW;
	}else{
		SDA_OUT_HIGH;
	} 
    
	SCL_OUT_HIGH;
	I2C_DELAY;
}


/**
 *
 */
static uint8_t I2C_CheckAcknowledge(void)
{	
    uint8_t state;
	
	SCL_OUT_LOW;
	SDA_OUT_HIGH;
	I2C_DELAY;
  	state = READ_SDA_IN;
	SCL_OUT_HIGH;
	I2C_DELAY;
	
	return state;
}




/**
 *
 */
static void I2C_SendData(uint8_t data)
{
	uint8_t i = 0;
	
	for (i=0; i<8; i++) 
	{
		SCL_OUT_LOW;
		
		if((data << i) & 0x80) {
			SDA_OUT_HIGH;
		}else{			
			SDA_OUT_LOW;
		}
			
		I2C_DELAY;
		SCL_OUT_HIGH;
		I2C_DELAY;
	 }
}


/**
 *
 */
static uint8_t I2C_ReceiveData(void)
{
	uint8_t i = 0, temp = 0;

	SCL_OUT_LOW;
	SDA_OUT_HIGH;
	I2C_DELAY;
	
	for(i=0; i<8; i++) {
		SCL_OUT_HIGH;
		temp |= READ_SDA_IN << (7-i);	
		I2C_DELAY;
		SCL_OUT_LOW;
		I2C_DELAY;
	}
		
	return temp;
}

/************************************ End of file **********************************/










