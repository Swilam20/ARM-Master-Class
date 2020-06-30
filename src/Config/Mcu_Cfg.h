#ifndef MCU_CFG
#define MCU_CFG


#define ENABLE			1
#define DISABLE			0   
#define MCU_CONFIGURATION_OPTIONS           3

/*configurtion of prepheral clock */
/*By default clock is diabled for all modules , you have to put ur modules number insted of zero to enable its clock
for example if i want to enable GPIO portA  i put 1 in RCGCGPIO_COLCK,GPIO portc  i put 2 in RCGCGPIO_COLCK and so on
*/
/*			peripheral			desired module*/			
#define 	RCGCGPIO_COLCK			0
#define 	RCGCDMA_COLCK				0
#define		RCGCHIB_COLCK 			0 
#define		RCGCUART_COLCK			0 
#define		RCGCSSI_COLCK				0
#define		RCGCI2C_COLCK 			0
#define		RCGCUSB_COLCK 			0
#define		RCGCCAN_COLCK				0
#define		RCGCADC_COLCK				0 
#define		RCGCACMP_COLCK			0
#define		RCGCPWM_COLCK 			0
#define		RCGCQEI_COLCK				0 
#define		RCGCEEPROM_COLCK 		0
#define		RCGCWTIMER_COLCK		0




#endif

