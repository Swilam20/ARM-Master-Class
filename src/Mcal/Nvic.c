/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Nvic.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable and Disable Navic Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Nvic.h"
#include "Mcu_hw.h"
#include "Nvic_Cfg.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

#define NVIC_GROUPING_SYSTEM_XXX    4
#define NVIC_GROUPING_SYSTEM_XXY    5
#define NVIC_GROUPING_SYSTEM_XYY    6
#define NVIC_GROUPING_SYSTEM_YYY    7
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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
void NVIC_init(void)
{
	NVIC_IntType IntNum;
	unsigned char LocGroup,LocSubGroup;
	unsigned long divd_Int;
	unsigned long*ptr_PRI0;
	/*TODO COnfigure Grouping\SubGrouping System in APINT register in SCB*/
	APINT= 0xFA050000|(NVIC_GROUPING_SYSTEM<<8);
	;
	
	for(unsigned char i=0;i< NVIC_ACTIVATED_INT_SIZE;i++)
	{
		IntNum = Nvic_Cfg[i].Interrupt_Number;
		LocGroup = Nvic_Cfg[i].Group_Priority;
		LocSubGroup = Nvic_Cfg[i].SubGroup_Priority;
		ptr_PRI0 = &PRI0;
		/*TODO : Enable\Disable based on user configurations in ENx Nvic Registers */
	
		            /*which NVIC_ENx Register*/			 /*	which Bit in this Register	*/	
					
				if		(IntNum >0 && IntNum <32)		{					ENB0=(1U<<IntNum);	}
				
				else if (IntNum >31 && IntNum <64)		{IntNum=IntNum-32;	ENB1=(1U<<IntNum);	}
				
				else if (IntNum >63 && IntNum <96)		{IntNum=IntNum-64;	ENB2=(1U<<IntNum);	}
				
				else if (IntNum >95 && IntNum <128) 	{IntNum=IntNum-96;	ENB3=(1U<<IntNum);	}
				
				else									{IntNum=IntNum-128;	ENB4=(1U<<IntNum);	}
				
		
		           
		
		
		/*TODO : Assign Group\Subgroup priority in PRIx Nvic Registers*/
			divd_Int = IntNum / 4;			/*integer number*/
			
			ptr_PRI0 = ptr_PRI0 +  divd_Int;		/*as all register arranged so i move to next reg based on integer result of (/)*/	
			
		 #if NVIC_GROUPING_SYSTEM==4
			switch(IntNum%4){
				case 0:*ptr_PRI0|=(LocGroup<<5);break;
				case 1:*ptr_PRI0|=(LocGroup<<13);break;
				case 2:*ptr_PRI0|=(LocGroup<<21);break;
				case 3:*ptr_PRI0|=(LocGroup<<29);break;
			}
		 #elif NVIC_GROUPING_SYSTEM==5
		 switch(IntNum%4){
				case 0:*ptr_PRI0|=(LocGroup<<6);*ptr_PRI0|=(LocSubGroup<<5);break;
				case 1:*ptr_PRI0|=(LocGroup<<14);*ptr_PRI0|=(LocSubGroup<<13);break;
				case 2:*ptr_PRI0|=(LocGroup<<22);*ptr_PRI0|=(LocSubGroup<<21);break;
				case 3:*ptr_PRI0|=(LocGroup<<30);*ptr_PRI0|=(LocSubGroup<<29);break;
			}
		 #elif NVIC_GROUPING_SYSTEM==6
		 switch(IntNum%4){
				case 0:*ptr_PRI0|=(LocGroup<<7);*ptr_PRI0|=(LocSubGroup<<5);break;
				case 1:*ptr_PRI0|=(LocGroup<<15);*ptr_PRI0|=(LocSubGroup<<13);break;
				case 2:*ptr_PRI0|=(LocGroup<<23);*ptr_PRI0|=(LocSubGroup<<21);break;
				case 3:*ptr_PRI0|=(LocGroup<<31);*ptr_PRI0|=(LocSubGroup<<29);break;
			}
		 #elif	NVIC_GROUPING_SYSTEM==7 
			 switch(IntNum%4){
				case 0:*ptr_PRI0|=(LocSubGroup<<5);break;
				case 1:*ptr_PRI0|=(LocSubGroup<<13);break;
				case 2:*ptr_PRI0|=(LocSubGroup<<21);break;
				case 3:*ptr_PRI0|=(LocSubGroup<<29);break;
			}
		 #endif
	}

	
}

/**********************************************************************************************************************
 *  END OF FILE: Nvic.c
 *********************************************************************************************************************/
