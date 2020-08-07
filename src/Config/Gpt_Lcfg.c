
#include "Gpt_Cfg.h"
#include "Gpt.h"

const Gpt_ConfigType Gpt_Confg[GPT_CONFIGURATION_OPTIONS]={

/*		GptChannelId 		GptGptChannelTickFrequency(KHz) 			GptChannelTickValueMax				ChannelMode						Ptr to callback function
			*/				
	{	Channel0,									1000		,														50000    ,  				GPT_CH_MODE_CONTINUOUS 							},
							
	{	Channel5,									2000		,														1000	  , 				GPT_CH_MODE_ONESHOT										},
							
	{	Channel9,									500			,														100000   , 				GPT_CH_MODE_CONTINUOUS 								}
									

};	