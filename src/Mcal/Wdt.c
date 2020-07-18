/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Wdt.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static const Wdt_ConfigType* Wdt_ConfigPtr = NULL_PTR;

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


/*/******************************************************************************
* \Syntax          : void Wdt_Init (const Gpt_ConfigType* ConfigPtr)
                                
* \Description     : Initializes the module.
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr |Pointer to configuration set |                
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Wdg_Init( const Wdg_ConfigType* ConfigPtr)
{
	Wdt_ConfigPtr=ConfigPtr;

    GET_WDT_REG(WDTLOAD)=Wdt_ConfigPtr.WdgInitialTimeout;

    /*Wait for wrc in WDTCTL*/
    while(!WRC_IS_SET()){}									/*Do nothing , poll for wrc to be 1*/
    GET_WDT_REG(WDTCTL)|=2;									/*Watchdog Reset Enable*/

    while(!WRC_IS_SET()){}									/*Do nothing , poll for wrc to be 1*/
    GET_WDT_REG(WDTCTL)|=1;									/*Watchdog Interrupt Enable*/

	while(!WRC_IS_SET()){}									/*Do nothing , poll for wrc to be 1*/
     GET_WDT_REG(WDTCTL)|=(Wdt_ConfigPtr.interruptType<<2);	/*Watchdog Interrupt Type*/

     while(!WRC_IS_SET()){}									/*Do nothing , poll for wrc to be 1*/
    GET_WDT_REG(WDTLOCK )=55; 								/*write any value tp lock  control reg.	*/

}

/*/******************************************************************************
* \Syntax          : void Wdg_SetTriggerCondition( uint16 timeout )
                                
* \Description     :Sets the timeout value for the trigger counter
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : timeout  |Timeout value (milliseconds) for setting the trigger counter. |       
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Wdg_SetTriggerCondition( uint16 timeout )
{	
	uint16 time_conv=timeout*62.5    /*WTD clock is 16 MHZ*/

	if(time_conv>Wdt_ConfigPtr.WdgMaxTimeoutWDT)
	{}
	else if (time_conv==0)
	{GET_WDT_REG(WDTLOAD)=Wdt_ConfigPtr.WdgInitialTimeout;
	}
	else
		{GET_WDT_REG(WDTLOAD)=time_conv;}
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
