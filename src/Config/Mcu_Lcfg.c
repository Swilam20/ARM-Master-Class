#include "Mcu_Cfg.h"
#include "Mcu.h"

/*clock source frequency =200Mhz and you can divide it up to Clock source frequency/16 */


const Mcu_ConfigType Mcu_Cfg[MCU_CONFIGURATION_OPTIONS]={
/*  Source					PLL USe					Frequency	*/

	{MinSource,				ENABLE,						Clock_source_frequency_3},
	{SleepOsc,				DISABLE,					_20KHZ},
	{PiOsc,						DISABLE,					_16MHZ}

};

const Mcu_ConfigType* ConfigPtr=Mcu_Cfg;
	

