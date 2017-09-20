/* ###################################################################
**     Filename    : main.c
**     Project     : KL02_mesoEaxon
**     Processor   : MKL02Z32VFM4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-09-19, 10:19, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/

//Master branch: mejorar ADC
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "Isource1.h"
#include "BitIoLdd1.h"
#include "Isource2.h"
#include "BitIoLdd2.h"
#include "RedLED.h"
#include "BitIoLdd3.h"
#include "BlueLED.h"
#include "BitIoLdd4.h"
#include "GreenLED.h"
#include "BitIoLdd5.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
//Para ADC
static uint16_t value;
static float voltage;
volatile bool AD_finished;
volatile bool CAL_finished; //Calibration finished flag
volatile uint16_t CAL_error = 0; //Calibration error byte
volatile byte CAL_status = 0; //Calibration status byte
//Para GPIO
LDD_TDeviceData *MyGPIO1Ptr;

int main(void)
{
  PE_low_level_init(); // Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! 
  bool ERROR_global = FALSE; //error global del sistema
  GPIOB_PDOR = 0b10011000000U; // Todos los leds apagados
  
  // Proceso de calibración
  CAL_error = AD1_Calibrate(TRUE);// Guarda en CAL_error el uint16 de Error en calibración (0== todo ok). 
  CAL_status = AD1_GetCalibrationStatus();
  if (CAL_error != 0) ERROR_global = TRUE;
  if (CAL_status != 0) ERROR_global = TRUE;
  
  RedLED_ClrVal(); //Enciende solo LED rojo
  
  if (!ERROR_global){ //si no hay error global
	  /*int a;	  
	  for( a = 0; a < 200; a = a + 1 ){
		  //HACE ADQUISICIÓN 10 VECES
		  AD_finished = FALSE; // reset flag 
		  (void)AD1_Measure(FALSE); // AD_finished will be set to TRUE once 
		  while(!AD_finished) {
			  // do something else here... 
		  }
		  // AD_finished set to TRUE by the interrupt to indicate the result is ready 
		  (void)AD1_GetValue16(&value); //* get the result into value variable 
		  Isource1_NegVal(); //Para revisar la velocidad de conversión del ADC!
		  voltage = value*3.3/1024; //Voltage = value*3.3/2^10
		 }
	  
	  RedLED_SetVal(); //Apaga led rojo
	  GreenLED_ClrVal(); //Enciende led verde
	  */
	  
	 
	  for(;;) { //Endless loop
		  AD_finished = FALSE; // reset flag 
		  (void)AD1_Measure(FALSE); // AD_finished will be set to TRUE once 
		  while(!AD_finished) {
			  // do something else here... 
		  }
		  // AD_finished set to TRUE by the interrupt to indicate the result is ready 
		  (void)AD1_GetValue16(&value); // get the result into value variable 
		  voltage = value*3.3/1024; //Voltage = value*3.3/2^10
	  }
  }// end if error global

  
  
  
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
