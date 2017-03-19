#include "main.h"
#include "stm32f4xx_hal.h"
__IO uint32_t TimingDelay;
void Delay(__IO uint32_t nTime);
void getdeviceinfo(SPI_HandleTypeDef hspi);
uint8_t Rx1 = 0x00;
uint8_t	Rx2 = 0x00;
uint8_t	Rx3 = 0x00;
uint8_t	Rx4 = 0x00;

extern int mpico(SPI_HandleTypeDef hspi){

  while (1)
  {
  /* INITIALIZE uPICO */
		//SET /TC_EN = LOW
	  HAL_GPIO_WritePin(nTC_EN_GPIO_Port, nTC_EN_Pin, GPIO_PIN_RESET);
		//DELAY(30) = 300ms 
		Delay(30);
		//Check /TC_BUSY & LOOP IF NOT BUSY
		while(nTC_Busy_Pin != 0x00){
			getdeviceinfo(hspi);
		}
		//Wait If /TC_BUSY == 0x01
  }
  /* USER CODE END 3 */

};
void getdeviceinfo(SPI_HandleTypeDef hspi){
		//Get Device Info (INS=0x30 P1=0x01	P2=0x01	LE=0x00)
		uint8_t INS = 0x30;
		uint8_t P1 = 0x01;
		uint8_t P2 = 0x01;
		uint8_t LE = 0x00;
		//Tx
		//SET /TC_CS == LOW
		HAL_GPIO_WritePin(nTC_CS_GPIO_Port, nTC_CS_Pin, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi, &INS, 1, 10);
		HAL_SPI_Transmit(&hspi, &P1, 1, 10);
		HAL_SPI_Transmit(&hspi, &P2, 1, 10);
		HAL_SPI_Transmit(&hspi, &LE, 1, 10);
		//SET /TC_CS == HIGH 
		HAL_GPIO_WritePin(nTC_CS_GPIO_Port, nTC_CS_Pin, GPIO_PIN_SET);
		//Rx
		while(nTC_Busy_Pin != 0x00){
		HAL_SPI_Receive(&hspi, &Rx1, 1, 10);
		HAL_SPI_Receive(&hspi, &Rx2, 1, 10);
		HAL_SPI_Receive(&hspi, &Rx3, 1, 10);
		HAL_SPI_Receive(&hspi, &Rx4, 1, 10);
		}
}		
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;
	while(TimingDelay != 0x00){ 
    TimingDelay--;
  }
return;
}
