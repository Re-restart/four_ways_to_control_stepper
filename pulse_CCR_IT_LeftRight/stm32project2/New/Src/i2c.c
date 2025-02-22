/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
#include "gpio.h"
#include "tim.h"
/* PB6 ----->SCL   时钟线
 * PB7------>SDA   数据线
 * HAL_Delay是毫秒延时，不是微秒延时
  */

/* USER CODE END PM */
/* USER CODE BEGIN 1 */
void delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim4, 0);  // 清零了 TIM4 的计数器，因此不再需要 start_time 变量来记录初始时间
    while (__HAL_TIM_GET_COUNTER(&htim4) < us);  // 等待计数达到 us
}



void i2c_end(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	delay_us(2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	delay_us(2);
}

void i2c_start(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	delay_us(2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	delay_us(2);
}

// 等待ack信号
uint8_t wait_ack(void){
	uint8_t waittime = 0; //等待时间
	uint8_t rack = 0; //因为 ACK 成功时 SDA 会被拉低（即 0）
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	delay_us(2);
	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
	{
		waittime++;
		if(waittime > 250)
		{
			i2c_end();
            rack = 1;//接收应答失败
            break;
		}
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	delay_us(2);
    return rack;
}

//应答信号
void i2c_ack(void){
	 /* SCL 0 -> 1  时 SDA = 0,表示应答 */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	delay_us(2);
	//产生一个时钟
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	delay_us(2);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    delay_us(2);//释放SDA线
}

// 发送 NACK 信号，它是为了告诉从设备 不再等待数据的应答
void i2c_nack(void){
	 /* SCL 0 -> 1  时 SDA = 1,表示不应答 */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	delay_us(2);
	//产生一个时钟
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	delay_us(2);
}

void i2c_send_byte(uint8_t data)
{
    uint8_t t;
    for (t = 0; t < 8; t++)
    {	if(((data & 0x80) >> 7)==1){
    		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    	}else {
    		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
    	}
    	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, ((data & 0x80) >> 7) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        delay_us(2);
    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    	delay_us(2);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
        data <<= 1;     /* 左移1位,用于下一次发送 */
    }
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);       /* 发送完成, 主机释放SDA线 */
}

//ack:  ack=1时，发送ack; ack=0时，发送nack
uint8_t i2c_read_byte(uint8_t ack)
{
    uint8_t i, receive = 0;
    for (i = 0; i < 8; i++ )    /* 接收1个字节数据 */
    {
        receive <<= 1;  /* 高位先输出,所以先收到的数据位要左移 */
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        delay_us(2);
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
        {
            receive++;
        }
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
        delay_us(2);
    }
    if (!ack)
    {
        i2c_nack();     /* 发送nACK */
    }
    else
    {
        i2c_ack();      /* 发送ACK */
    }

    return receive;
}
