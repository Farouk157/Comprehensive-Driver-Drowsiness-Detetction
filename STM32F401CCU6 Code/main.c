/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   Main			      */
/*      Date    :   4/11/2023                         */
/*      version :       1.00                          */
/******************************************************/


/* Include Section */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/RCC/RCC_int.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/NVIC/NVIC_int.h"
#include "MCAL/EXTI/EXTI_interface.h"
#include "MCAL/SYSTICK/STK_interface.h"
#include "MCAL/UART/UART_int.h"
#include "MCAL/ADC/ADC_int.h"
#include "HAL/FSR/FSR_interface.h"
#include "HAL/TFT/TFT_int.h"
#include "HAL/BUZZER/Buzzer_Int.h"
#include "HAL/Vib_Motor/VibMotor_Int.h"
#include "HAL/PushButton/PushButton_Int.h"
#include "Warning_Pic.h"


/* Some configurations that done in the configuration file and used here*/
extern USART_InitType uart1_cfg;
extern USART_InitType uart2_cfg;
extern GPIO_cfg_t Tx_UART_1;
extern GPIO_cfg_t Rx_UART_1;
extern GPIO_cfg_t Tx_UART_2;
extern GPIO_cfg_t Rx_UART_2;
extern GPIO_cfg_t led_test;



/* Functions Prototype section*/
void vTurn_On_Alerting_System(void);
void vTurn_Off_Alerting_System(void);
void No_Respond_Time_Out(void);
void vTurn_On_Eye_Alerting_System(void);

/* Global variables section */
u8 Global_u8DriverState = 'A';
u8 Global_flag = 0;


/* Entry Point */
int main(void)
{
	/* Local Variables */

	volatile u16 Local_u16FSR_1 = 0;
	volatile u16 Local_u16FSR_2 = 0;

	/* Initialization of RCC for our needed peripherals */
	MRCC_vInit();
	MRCC_vEnableClock(RCC_AHB1, RCC_EN_GPIOA);
	MRCC_vEnableClock(RCC_AHB1, RCC_EN_GPIOB);
	MRCC_vEnableClock(RCC_APB1, RCC_EN_UART2);
	MRCC_vEnableClock(RCC_APB2, RCC_EN_UART1);
	MRCC_vEnableClock(RCC_APB2, RCC_EN_SYSCFG);
	MRCC_vEnableClock(RCC_APB2,RCC_EN_SPI1);
	MRCC_vEnableClock(RCC_APB2,RCC_EN_ADC1) ;

	/* Initialization of the SYSTICK Timer */
	STK_voidInit();

	/* Initialization of the ADC */
	MADC_vInit();

	/* Initialization of USARTS used */
	MGPIO_vInit(&Tx_UART_1);
	MGPIO_vInit(&Rx_UART_1);
	MGPIO_vInit(&Tx_UART_2);
	MGPIO_vInit(&Rx_UART_2);
	MNVIC_vEnableInteruptPeripheral(NVIC_USART2);
	MUSART2_vSetCallBack(vTurn_On_Eye_Alerting_System);
	MUSART_vInit(&uart1_cfg, USART1);
	MUSART_vInit(&uart2_cfg, USART2);
	MUSART_vEnable(USART1);
	MUSART_vEnable(USART2);
	MUSART_RxIntSetStatus(USART2, ENABLE);

	/* Initialization of External Interrupt */
	EXTI_voidInit();
	EXTI_vSetCallBack(vTurn_Off_Alerting_System);
	EXTI_voidEnableLine(EXTI_LINE_0, EXTI_FALLING);
	MNVIC_vEnableInteruptPeripheral(NVIC_EXTI0);

	/* Initialization of the HAL drivers and components needed */
	Buzzer_voidInit();
	VibMotor_voidInit();
	PushButton_voidInit();
	HTFT_vInit();
	FSR_Init();
	GSM_init();
	GPS_init();
	MGPIO_vInit(&led_test);

	

	while(1)
	{
		/* check on the grip strength of the driver and the reading of the FSR Sensor */
		Local_u16FSR_1 = FSR_Read_1(ADC_CHANNAL_8);
		Local_u16FSR_2 = FSR_Read_2(ADC_CHANNAL_9);
		if((Local_u16FSR_1 < THRESHOLD_VALUE) && (Local_u16FSR_2 < THRESHOLD_VALUE))
		{
			vTurn_On_Alerting_System();
		}

	}

	return 0;
}

/*
 *brief: this function turns on the alerting system
 *des. : this function being executed when the USART2 being received drowsy state from the Raspberry pi and camera
 *ret  : Nothing
 *param: Nothing
*/
void vTurn_On_Eye_Alerting_System(void)
{
	u8 Local_u8ReadingVal = MUSART_u8ReadDataRegisterAsynch(USART2);
	if( (Local_u8ReadingVal == 'D') && (Global_flag == 0))
	{
		Buzzer_voidTurnOn();
		VibMotor_voidTurnOn();
		HTFT_vDisplayPicture(&image_data_warnpic);
		STK_voidSetInterval_Periodic(12000000, No_Respond_Time_Out);
		Global_flag = 1;
	}
}

/*
 *brief: this function turns on the alerting system
 *des. : this function being called and executed when the driver grip strength is lower than the threshold
 *ret  : Nothing
 *param: Nothing
*/
void vTurn_On_Alerting_System(void)
{
	if(Global_flag == 0)
	{
		Buzzer_voidTurnOn();
		VibMotor_voidTurnOn();
		HTFT_vDisplayPicture(&image_data_warnpic);
		STK_voidSetInterval_Periodic(12000000, No_Respond_Time_Out);
		Global_flag = 1;
	}

}

/*
 *brief: this function turns off the alerting system
 *des. : this function being executed when the driver presses the push button and makes an external interrupt
 *ret  : Nothing
 *param: Nothing
*/
void vTurn_Off_Alerting_System(void)
{
	STK_voidStopTimer();
	Buzzer_voidTurnOff();
	VibMotor_voidTurnOff();
	HTFT_vInit();
	Global_flag = 0;
}

/*
 *brief: this function turns on the GSM and GPS
 *des. : this function being executed when the time over without any action from the driver to stop the alerting system
 	 	 so this function activates the GPS and GSM to send as indication for very dangerous situation and send warning
 	 	 message and location for the emergency road and services
 *ret  : Nothing
 *param: Nothing
*/
void No_Respond_Time_Out(void)
{
	u32 remain_time;
	remain_time = STK_u32GetRemainingTime();
	if( (remain_time < 1000000) && (remain_time > 0) )
	{
		//no send from the GSM
	}
	else{
		STK_voidStopTimer();
		SMS();
		Send_SMS();
		MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN12, GPIO_HIGH);
	}
}

