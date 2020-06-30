/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Nvic.h
 *       Module:  Nvic
 *
 *  Description:  header file for Nvic Module    
 *  
 *********************************************************************************************************************/
#ifndef NVIC_H
#define NVIC_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Nvic_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	NVIC_GPIO_Port_A,
	NVIC_GPIO_Port_B,
	NVIC_GPIO_Port_C,
	NVIC_GPIO_Port_D,
	NVIC_GPIO_Port_E,
	NVIC_UART0,
	NVIC_UART1,
	NVIC_SSI0,
	NVIC_I2C0,
	NVIC_PWM0_Fault ,
	NVIC_PWM0_Generator_0 ,
	NVIC_PWM0_Generator_1,
	NVIC_PWM0_Generator_2,
	NVIC_QEI0,
	NVIC_ADC0_Sequence ,
	NVIC_ADC1_Sequence ,
	NVIC_ADC2_Sequence,
	NVIC_ADC3_Sequence ,
	NVIC_Watchdog_Timers_0_and_1,
	NVIC_16_32_Bit_Timer_0A,
	NVIC_16_32_Bit_Timer_0B,
	NVIC_16_32_Bit_Timer_1A,
	NVIC_16_32_Bit_Timer_1B,
	NVIC_16_32_Bit_Timer_2A,
	NVIC_16_32_Bit_Timer_2B,
	NVIC_Analog_Comparator_0,
	NVIC_Analog_Comparator_1,
	NVIC_System_Control=28,
	NVIC_lash_Memory_Control_and_EEPROM_Control,
	NVIC_GPIO_Port_F,
	NVIC_UART2 =33,
	NVIC_SSI1,
	NVIC_16_32_Bit_Timer_3A,
	NVIC_16_32_Bit_Timer_3B,
	NVIC_I2C1,
	NVIC_QEI1,
	NVIC_CAN0,
	NVIC_CAN1,
	NVIC_Hibernation_Module=43,
	NVIC_USB,
	NVIC_PWM_Generator_3,
	NVIC_uDMA_Software,
	NVIC_uDMA_Error,
	/*hena kan feh 7aga ha3dlha*/
	NVIC_SSI2=57,
	NVIC_SSI3,
	NVIC_UART3,
	NVIC_UART4,
	NVIC_UART5,
	NVIC_UART6,
	NVIC_UART7,
	NVIC_I2C2=68,
	NVIC_I2C3,
	NVIC_16_32_Bit_Timer_4A,
	NVIC_16_32_Bit_Timer_4B,
	NVIC_16_32_Bit_Timer_5A =92,
	NVIC_16_32_Bit_Timer_5B,
	NVIC_32_64_Bit_Timer_0A,
	NVIC_32_64_Bit_Timer_0B,
	NVIC_32_64_Bit_Timer_1A,
	NVIC_32_64_Bit_Timer_1B,
	NVIC_32_64_Bit_Timer_2A,
	NVIC_32_64_Bit_Timer_2B,
	NVIC_32_64_Bit_Timer_3A,
	NVIC_32_64_Bit_Timer_3B,
	NVIC_32_64_Bit_Timer_4A,
	NVIC_32_64_Bit_Timer_4B,
	NVIC_32_64_Bit_Timer_5A,
	NVIC_32_64_Bit_Timer_5B,
	NVIC_System_Exception_imprecise,
	NVIC_PWM1_Generator =134,
	NVIC_PWM2_Generator ,
	NVIC_PWM3_Generator ,
	NVIC_PWM4_Generator ,
	NVIC_PWM1_Fault,
	
}NVIC_IntType;

typedef struct
{
	NVIC_IntType Interrupt_Number;
	uint8        Group_Priority;
	uint8        SubGroup_Priority;
	
	
}Nvic_CfgType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const Nvic_CfgType Nvic_Cfg[];
 void NVIC_init(void);
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/******************************************************************************
* \Syntax          : void Nvic_Init(void)                                      
* \Description     : initialize Nvic Module by parsing the Configuration 
*                    into Nvic registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Nvic_Init(void);
 
#endif  /* NVIC_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
