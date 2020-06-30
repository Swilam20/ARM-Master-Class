/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Mcu.h
 *       Module:  Mcu
 *
 *  Description:  Header file for Mcu Module     
 *  
 *********************************************************************************************************************/
#ifndef MCU_H
#define MCU_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef		unsigned char			Mcu_PllStatusType;
typedef 	unsigned char			Mcu_ClockType;
typedef 	unsigned char			Mcu_RawResetType;

/*typedef 	unsigned char			MCU_ClockSource;*/

typedef enum	
{
	_20KHZ=0,
	_16MHZ=1,
	Clock_source_frequency_3 = 0x2,
	Clock_source_frequency_4  ,
	Clock_source_frequency_5  ,
	Clock_source_frequency_6  ,
	Clock_source_frequency_7  ,
	Clock_source_frequency_8  ,
    Clock_source_frequency_9  ,
	Clock_source_frequency_10 , 
	Clock_source_frequency_11 ,
	Clock_source_frequency_12 ,
	Clock_source_frequency_13 ,
	Clock_source_frequency_14 ,
	Clock_source_frequency_15 ,
	Clock_source_frequency_16 
	
	
}MCU_ClockFrequency;


typedef struct 
{
  unsigned char						source;
	unsigned char						pullUse;
	unsigned char						frequency;
	/*TODO Define Struct member to contain configuration parameters*/
}Mcu_ConfigType;


typedef enum{
	MinSource,
	PiOsc,
	SleepOsc,
	
}MCU_ClockSource;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const Mcu_ConfigType Mcu_Cfg[];
extern  const Mcu_ConfigType* ConfigPtr;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
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
void Mcu_Init ( const Mcu_ConfigType* ConfigPtr );
Mcu_RawResetType Mcu_GetResetRawValue( void );
void Mcu_PerformReset(void); 
Std_ReturnType Mcu_InitClock( Mcu_ClockType ClockSetting);
Std_ReturnType Mcu_DistributePllClock( void);
Mcu_PllStatusType Mcu_GetPllStatus( void);
#endif  /* MCU_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
