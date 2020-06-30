/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Mcu.c
 *        \brief  Microcontroller Unit Driver
 *                
 *      \details The MCU driver provides services for basic microcontroller initialization, 
 *               Clock Control and reset
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcu.h"
#include "Mcu_hw.h"
#include "Mcu_Cfg.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define LOCKED  	1
#define UNLOCKED	0
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

 const Mcu_ConfigType* PtrToConfig;

 unsigned char clockSource;
 unsigned char frequency;
 unsigned char pllUse;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Mcu_Init ( const Mcu_ConfigType* ConfigPtr )        
* \Description     : This service initializes the MCU driver.                                                                                                               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr       Pointer to MCU driver configuration set.                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Mcu_Init ( const Mcu_ConfigType* ConfigPtr)
{
	PtrToConfig=ConfigPtr;
	
}
/*************************************/
Mcu_RawResetType Mcu_GetResetRawValue( void ){
	unsigned char i;
	for(i=0;i<6;i++){
		if((RESC &(1u<i))!=0)
		{
			RESC|=0u<i;
			return i;
		}
	}
	return 0xf;
}
/*************************************/
void Mcu_PerformReset(void){

	APINT |=0x2;
}
/**************************************/
Std_ReturnType Mcu_InitClock( Mcu_ClockType ClockSetting){
	
		/*configurition of modules*/
		RCGCGPIO		|=(1u<<RCGCGPIO_COLCK	-1);		
    RCGCDMA			|=(1u<<RCGCDMA_COLCK-1);			
		RCGCHIB 		|=(1u<<RCGCHIB_COLCK-1);		 
		RCGCUART		|=(1u<<RCGCUART_COLCK-1);		
		RCGCSSI			|=(1u<<RCGCSSI_COLCK-1);		
		RCGCI2C 		|=(1u<<RCGCI2C_COLCK-1);		
		RCGCUSB 		|=(1u<<RCGCUSB_COLCK-1);		
		RCGCCAN			|=(1u<<RCGCCAN_COLCK-1);		
		RCGCADC			|=(1u<<RCGCADC_COLCK-1);		 
		RCGCACMP		|=(1u<<RCGCACMP_COLCK-1);		
		RCGCQEI			|=(1u<<RCGCQEI_COLCK-1);	
		RCGCPWM			|=(1u<<RCGCPWM_COLCK-1);		 
		RCGCEEPROM 	|=(1u<<RCGCEEPROM_COLCK-1);	
		RCGCWTIMER	|=(1u<<RCGCWTIMER_COLCK-1);	
		/*************************/
		clockSource=PtrToConfig[ClockSetting].source;
		pllUse=(PtrToConfig[ClockSetting]).pullUse;
		frequency=(PtrToConfig[ClockSetting]).frequency;

		if(pllUse==DISABLE){
			while((RCC &0x00000100) ==0); /* The PLL is powered down. Care must be taken to ensure that
											another clock source is functioning and that the BYPASS bit is
											set before setting this bit.
											*/
		}
		switch(ClockSetting){

			case 0:RCC|= 0u | (frequency<<23) | (pllUse<<13) |(0<<11) ; return E_OK;
			case 1:RCC|= 0u |  (pllUse<<13) |(0<<11) ; return E_OK;
			case 2:RCC|= 0u |  (pllUse<<13) |(1<<11) | (0<<4); return E_OK;
			default : return E_NOT_OK ;
		}
	

}
/**************************************/
Std_ReturnType Mcu_DistributePllClock( void) {
	if(RCC &0x00002000 ==0)
		{ return E_NOT_OK;}
	else
	{
		RCC|=0x00002000;
		return E_OK;
	}
}
/**************************************/
Mcu_PllStatusType Mcu_GetPllStatus( void){

	if(PLLSTAT==1)
		return LOCKED;
	else
		return UNLOCKED;
}
/**********************************************************************************************************************
 *  END OF FILE: Mcu.c
 *********************************************************************************************************************/
