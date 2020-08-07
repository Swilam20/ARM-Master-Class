/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpt.h
 *       Module:  Gpt.h
 *
 *  Description:  header file for Gpt Module     
 *  
 *********************************************************************************************************************/
#ifndef GPT_H
#define GPT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define		 UPPER_32_BITS					 0xFFFFFFFF00000000
#define		 LOWER_32_BITS					 0x00000000FFFFFFFF 

#define     SYSTEM_CLOCK					16000

#define  	GPT_CH_MODE_CONTINUOUS			 2
#define 	 GPT_CH_MODE_ONESHOT			 1

#define		 GPT_MODE_NORMAL   				 0
#define 	 GPT_MODE_SLEEP					 1

#define		 GPT_BASE_ADDRESS   			 0x40030000
#define 	 GPTMCTL	 			 		 0x00C
#define 	 GPTMIMR				 		 0x018
#define		 GPTMCFG			     		 0x000
#define		 GPTMCTL					     0x00C
#define      GPTMTAILR						 0x028
#define		 GPTMTBILR						 0x02C
#define 	 GPTMTAMR   					 0x004
#define 	 GPTMTBMR						 0x008
#define		 GPTMTAPR					 	 0x038
#define	     GPTMTAR 						 0x048
#define		 GPTMTAMATCHR  					 0x030	
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define GET_GPT_REG(GPT_BASE_ADDRESS,ChannelId,Offset)      *((volatile uint32*)(GPT_BASE_ADDRESS+(ChannelId<<3)+Offset))

#define SHIFT_AMOUNT(systemClock,frequency)										(systemClock/frequency)
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8		Gpt_PredefTimerType;
typedef uint32 	Gpt_ValueType;
typedef uint32  Gpt_Frequency;
typedef uint8	Gpt_ChannelMode;
typedef enum
{
Channel0=0,
Channel1,
Channel2,
Channel3,
Channel4,
Channel5,
Channel6,
Channel7,
Channel8,
Channel9=28,
Channel10=29,
Channel11=30,
Channel12=31,
}Gpt_ChannelType;

typedef struct 
{
	Gpt_ChannelType 	 channelId;
	Gpt_Frequency		 frequency;
	Gpt_ValueType		 maxTick;
	Gpt_ChannelMode		 channelMode;
	/* call back*/

} Gpt_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
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
void Gpt_Init (const Gpt_ConfigType* ConfigPtr);

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
void Gpt_DisableNotification ( Gpt_ChannelType Channel );

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
void Gpt_EnableNotification ( Gpt_ChannelType Channel );

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
Gpt_ValueType Gpt_GetTimeElapsed ( Gpt_ChannelType Channel ) ;

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
Std_ReturnType Gpt_GetPredefTimerValue (Gpt_PredefTimerType PredefTimer,uint32* TimeValuePtr);

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
Gpt_ValueType Gpt_GetTimeRemaining (Gpt_ChannelType Channel);

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
void Gpt_StartTimer ( Gpt_ChannelType Channel, Gpt_ValueType Value ) ;
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
void Gpt_StopTimer ( Gpt_ChannelType Channel );

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
/* void Gpt_Notification_<channel> ( void );*/

 
#endif  /* GPT_H*/

/**********************************************************************************************************************
 *  END OF FILE: Gpt.h
 *********************************************************************************************************************/
