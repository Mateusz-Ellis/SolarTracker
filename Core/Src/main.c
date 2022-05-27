/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hagl.h"
#include "font6x9.h"
#include "rgb565.h"
#include <string.h>
#include <stdio.h>
#include <wchar.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/*
int __io_putchar(int ch){
	if (ch == '\n') {
	uint8_t ch2 = '\r';
	HAL_UART_Transmit(&huart2, &ch2, 1, HAL_MAX_DELAY);
	}
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return 1;
}
*/

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//int32_t CH1_DC = 100000;
	//int32_t CH2_DC = 133000;
	//int up1 = 1;
	//int up2 = 1;
	uint32_t value[5];

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_ADC_Start_DMA(&hadc1, value, 5);
  lcd_init();
  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  lcd_init();

  for (int i = 0; i < 8; i++) {
    hagl_draw_rounded_rectangle(2+i, 2+i, 158-i, 126-i, 8-i, rgb565(0, 0, i*16));
  }

  hagl_put_text("Hello World!", 40, 55, YELLOW, font6x9);

  lcd_copy();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



	  //printf("1-> %d\n",value[0]);
	  //printf("1-> %d\n",value[1]);
	  //printf("1-> %d\n",value[2]);
	  //printf("1-> %d\n",value[3]);

	  //sprintf(textToWrite,"%lu", value[5]);
	  //wchar_t vOut = (wchar_t)value[5];
	  //hagl_clear_screen();


	  //wchar_t m_reportFileName[256];
	  //char marek[] = "zabawka";
	  //swprintf(m_reportFileName, L"%hs", marek);

	  //swprintf(m_reportFileName, L"%d", robert);
	  //hagl_put_text(m_reportFileName, 40, 55, YELLOW, font6x9);

	  int robert1 = (int)value[0];
	  int robert2 = (int)value[1];
	  int robert3 = (int)value[2];
	  int robert4 = (int)value[3];
	  float robert5 = (int)value[4];
	  robert5 = (robert5 / 65536) * 3.3;
	  char marek1[255];
	  char marek2[255];
	  char marek3[255];
	  char marek4[255];
	  char marek5[255];
	  sprintf(marek1, "%d", robert1);
	  sprintf(marek2, "%d", robert2);
	  sprintf(marek3, "%d", robert3);
	  sprintf(marek4, "%d", robert4);
	  sprintf(marek5, "%f", robert5);

	  hagl_clear_screen();

	  hagl_put_text(marek1, 40, 3, YELLOW, font6x9);
	  hagl_put_text(marek2, 40, 10, YELLOW, font6x9);
	  hagl_put_text(marek3, 40, 17, YELLOW, font6x9);
	  hagl_put_text(marek4, 40, 24, YELLOW, font6x9);
	  hagl_put_text(marek5, 40, 31, YELLOW, font6x9);

	  lcd_copy();
	  HAL_Delay(1000);

	  /*
	  HAL_Delay(10);

	  //up down
	  if(value[0] > value[1]){
		  CH1_DC += 100;
	  }
	  if(value[2] > value[3]){
		  CH1_DC += 100;
	  }
	  if(value[0] < value[1]){
		  CH1_DC -= 100;
	  }
	  if(value[2] < value[3]){
		  CH1_DC -= 100;
	  }


	  //left right
	  if(value[0] > value[2]){
		  CH2_DC += 100;
	  }
	  if(value[1] > value[3]){
		  CH2_DC += 100;
	  }
	  if(value[0] < value[2]){
		  CH2_DC -= 100;
	  }
	  if(value[1] < value[3]){
		  CH2_DC -= 100;
	  }




	  //check
	  if(CH1_DC > 114000){
		  CH1_DC = 114000;
	  }
	  if(CH1_DC < 80000){
		  CH1_DC = 80000;
	  }
	  if(CH2_DC > 205000){
		  CH2_DC = 205000;
	  }
	  if(CH2_DC < 62000){
		  CH2_DC = 62000;
	  }


	  TIM2->CCR1 = CH1_DC;
	  TIM2->CCR2 = CH2_DC;
	  */


	  /*
	  TIM2->CCR1 = CH1_DC;
	  TIM2->CCR2 = CH2_DC;

	  if(up1){
		  TIM2->CCR1 = CH1_DC;
		  CH1_DC += 50;
	  } else{
		  TIM2->CCR1 = CH1_DC;
		  CH1_DC -= 50;
	  }

	  if(up2){
		  TIM2->CCR2 = CH2_DC;
		  CH2_DC += 50;
	  } else {
		  TIM2->CCR2 = CH2_DC;
		  CH2_DC -= 50;
	  }

	  if((CH1_DC > 114000) && up1){
		  up1 = 0;
	  }
	  if((CH1_DC < 80000) && !up1){
	  	  up1 = 1;
	  }

	  if((CH2_DC > 205000) && up2){
		  up2 = 0;
	  }
	  if((CH2_DC < 62000) && !up2){
		  up2 = 1;
	  }

	  HAL_Delay(2);
	  */


	  //uint8_t value;
	  //HAL_UART_Receive(&huart2, &value, 1, HAL_MAX_DELAY);
	  //printf("-> %c\n",value);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
