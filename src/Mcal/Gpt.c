/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Gpt.c
 *        \brief  General purpose Timer Driver
 *
 *      \details  The GPT driver is part of the microcontroller abstraction layer (MCAL). It initializes
				  and controls the internal General Purpose Timer(s) (GPT) of the microcontroller.

 *
 *               
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Gpt.h"
#include "Gpt_Cfg.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static const Gpt_ConfigType* Gpt_ConfigPtr = NULL_PTR;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define timer16     (*((volatile uint32 *)0x400FE604))
#define timer32     (*((volatile uint32 *)0x400FE608))
#define cfg     	(*((volatile uint32 *)0x40030000))
#define	ctl				(*((volatile uint32 *)0x4003000c))
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
* \Syntax          : void Gpt_Init (const Gpt_ConfigType* ConfigPtr)
                                
* \Description     : Initializes the GPT driver
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_Init (const Gpt_ConfigType* ConfigPtr){
	GET_GPT_REG(0x400FE604,0,0)|=0x1f;
	timer32=0x1f;
Gpt_ConfigPtr=ConfigPtr;
uint16 id;
Gpt_Frequency  frequency;
Gpt_ValueType  maxTick;
Gpt_ChannelMode mode;

/*start predef timers*/
	
/**/
uint8 i;
for(i=0;i<GPT_CONFIGURATION_OPTIONS;i++){

	id	=	Gpt_ConfigPtr[i].channelId;
	frequency	=	Gpt_ConfigPtr[i].frequency;
	maxTick	=	Gpt_ConfigPtr[i].maxTick;
	mode       =	Gpt_ConfigPtr[i].channelMode; 
	
		/*Enable timers*/
	 GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMCTL)|= 0x101;
		
	 /*configure mode and  timer counting up*/
	 GET_GPT_REG(GPT_BASE_ADDRESS,id, GPTMTAMR)|= mode|(1<<4);

	 
		
	 /*configure timer register*/
	 if(id<6)
	 {	
		if (maxTick<0xFFFF)
		 	{	/*cfg=0x4;*/
				
		 		GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMCFG) |= 0x4;
		 		GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMTAMATCHR )|=	maxTick;
		 	}
		 
		else
		 	{
		 		GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMCFG) = 0x0;
		 		GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMTAMATCHR )=	maxTick;

		 	}
	 }

	else /* wide Registers*/
	{
		if(maxTick<0xFFFFFFFF)
			{
				GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMCFG) = 0x4;
				GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMTAMATCHR )=	maxTick;
			}

		else
			{
				GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMCFG) = 0x0;
				GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMTAMATCHR )=	(maxTick & LOWER_32_BITS);
				GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMTAMATCHR )=	(maxTick & UPPER_32_BITS);

			}
	 
	}
	 /*disable all interrupts*/
	 GET_GPT_REG(GPT_BASE_ADDRESS,id,GPTMIMR) =0;
	 
	 
}

}




/******************************************************************************
* \Syntax          : void Gpt_DisableNotification ( Gpt_ChannelType Channel )                                      
* \Description     : Disables the interrupt notification for a channel (relevant in normal mode).     
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant (but not for the same timer channel)
                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_DisableNotification ( Gpt_ChannelType Channel )    {

	GET_GPT_REG(GPT_BASE_ADDRESS,Channel, GPTMTAMR) &= ~(1<<5);

}




/******************************************************************************
* \Syntax          : void Gpt_EnableNotification ( Gpt_ChannelType Channel )                                      
* \Description     : Enables the interrupt notification for a channel (relevant in normal mode).    
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant (but not for the same timer channel)                                           
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_EnableNotification ( Gpt_ChannelType Channel ){

	GET_GPT_REG(GPT_BASE_ADDRESS,Channel, GPTMTAMR) |= (1<<5);
}





/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeElapsed ( Gpt_ChannelType Channel )                                       
* \Description     : Returns the time already elapsed.
		    
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : Return value | Gpt_ValueType Elapsed timer value (in number of ticks)|

*******************************************************************************/
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel ){

	Gpt_ValueType timeElapsed;
	uint8 shitAmount;
	uint8 i;
	for(i=0;i<GPT_CONFIGURATION_OPTIONS;i++)
	{
		if(Channel==Gpt_ConfigPtr[i].channelId)
			break;
	}
	shitAmount=SHIFT_AMOUNT(SYSTEM_CLOCK,Gpt_ConfigPtr[i].frequency);
	timeElapsed= GET_GPT_REG(GPT_BASE_ADDRESS,Channel,GPTMTAPR)|(GET_GPT_REG(GPT_BASE_ADDRESS,Channel,GPTMTAR)>>shitAmount);
	timeElapsed*=1/(Gpt_ConfigPtr[i].frequency);
	return timeElapsed;
}






/******************************************************************************
* \Syntax          : Std_ReturnType Gpt_GetPredefTimerValue (Gpt_PredefTimerType PredefTimer,uint32* TimeValuePtr)
                                       
* \Description     : Delivers the current value of the desired GPT Predef Timer.    
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : PredefTimer |GPT Predef Timer  |                  
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType	 	|E_OK: no error has been detected|
										|E_NOT_OK: aborted due to errors |
*******************************************************************************/
 /*Std_ReturnType Gpt_GetPredefTimerValue (Gpt_PredefTimerType PredefTimer,uint32* TimeValuePtr){

 }
*/





/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeRemaining (Gpt_ChannelType Channel)
                                      
* \Description     : Returns the time remaining until the target time is reached.	     
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                            
* \Parameters (in) : Channel  |Numeric identifier of the GPT channel. |                   
* \Parameters (out): None                                                      
* \Return value:   : Gpt_ValueType 	|Remaining timer value (in number of ticks)|
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeRemaining (Gpt_ChannelType Channel){

	Gpt_ValueType timeRemaining;
	uint8 shitAmount;
	uint8 i;
	for(i=0;i<GPT_CONFIGURATION_OPTIONS;i++)
	{
		if(Channel==Gpt_ConfigPtr[i].channelId)
			break;
	}
	shitAmount=SHIFT_AMOUNT(SYSTEM_CLOCK,Gpt_ConfigPtr[i].frequency);
	timeRemaining= GET_GPT_REG(GPT_BASE_ADDRESS,Channel,GPTMTAPR)|(GET_GPT_REG(GPT_BASE_ADDRESS,Channel,GPTMTAPR)>>shitAmount);
	timeRemaining=(timeRemaining-Gpt_ConfigPtr[i].maxTick)*(1/(Gpt_ConfigPtr[i].frequency));
	return timeRemaining;
}



/******************************************************************************
* \Syntax          : void Gpt_StartTimer ( Gpt_ChannelType Channel, Gpt_ValueType Value )                                      
* \Description     : Starts a timer channel.
    
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant (but not for the same timer channel)
                                          
* \Parameters (in) : Channel 	|Numeric identifier of the GPT channel|
					 Value 		|Target time in number of ticks		  |
                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_StartTimer ( Gpt_ChannelType Channel, Gpt_ValueType Value ) {

GET_GPT_REG(GPT_BASE_ADDRESS,Channel, GPTMCTL)|=0x1;


}





/******************************************************************************
* \Syntax          : void Gpt_StopTimer ( Gpt_ChannelType Channel )
                                      
* \Description     : Stops a timer channel.   
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant (but not for the same timer channel)                                             
* \Parameters (in) : Channel | Numeric identifier of the GPT channel |                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_StopTimer ( Gpt_ChannelType Channel ){
GET_GPT_REG(GPT_BASE_ADDRESS,Channel, GPTMCTL)&=0xFFFFFFFE;

}






/******************************************************************************
* \Syntax          : void Gpt_Notification_<channel> ( void )                                        
* \Description     : --    
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : GPT user implementation dependant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
/*void Gpt_Notification_<channel> ( void ){

}
*/




/**********************************************************************************************************************
 *  END OF FILE: Nvic.c
 *********************************************************************************************************************/
