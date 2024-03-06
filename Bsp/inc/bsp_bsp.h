#ifndef __BSP_BSP_H
#define __BSP_BSP_H
#include "main.h"

typedef enum _set_temp_value{

     select_disp_temp,
	 select_set_temp_fun,
	 select_temp_by_set,


}set_temp_value_name;


void TFT_Pocess_Command_Handler(void);


void TFT_Display_Timer_Timing_Value(uint8_t disp);

void TFT_Disp_Set_TimerTime_Init(void);


#endif 

