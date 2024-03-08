#include "bsp.h"

static void TFT_Donnot_Set_Timer_Time(void);

void TimeTimer_Pro_Handler(void)
{
  static uint8_t timer_blink_times;
  
  switch(pro_t.timer_mode_flag){

	case timer_time: //timer_time 
		if(gctl_t.gTimer_ctl_set_timer_time_senconds >59){
			gctl_t.gTimer_ctl_set_timer_time_senconds =0;

			gctl_t.gSet_timer_minutes --;

			if(gctl_t.gSet_timer_minutes <0){
			gctl_t.gSet_timer_minutes =59;
			gctl_t.gSet_timer_hours --;


			}
			if(gctl_t.gSet_timer_hours < 0){

			pro_t.gPower_On = power_off;
			pro_t.power_off_flag=1;
			pro_t.run_process_step=0xff;

			}
			TFT_Disp_Set_TimerTime(0);
		}

		//TFT_Disp_Set_TimerTime(0);
		TFT_DonnotDisp_Works_Time();
	break;

	case works_time:

		if(gctl_t.gTimer_ctl_disp_second > 59){
			TFT_Display_WorksTime();
		}

		TFT_Donnot_Set_Timer_Time();

	break;

	case timer_set_time:

		if(pro_t.gTimer_pro_mode_key_timer > 3){

		if(pro_t.gTimer_pro_set_timer_time < 6){
		TFT_Disp_Set_TimerTime(1);//1-don't display numbers 0-display numbers
		}
		else {

		TFT_Disp_Set_TimerTime(0); //1-don't display numbers, 0-display numbers //turn off disp timer time
		timer_blink_times++;

		}

		if(timer_blink_times > 0 && gctl_t.mode_key_long_time_flag >0){
			timer_blink_times =0;
			if(gctl_t.gSet_timer_hours >0 ){

				pro_t.timer_mode_flag = timer_time;
				pro_t.mode_key_confirm_flag =0xff;
				gctl_t.gTimer_ctl_set_timer_time_senconds =0;
				gctl_t.timer_time_define_flag = 1;
				gctl_t.gSet_timer_minutes =0;
				gctl_t.mode_key_long_time_flag=0;

			}
			else{
				gctl_t.mode_key_long_time_flag=0;
				gctl_t.timer_time_define_flag = 0;
				pro_t.mode_key_confirm_flag =0xff;
				pro_t.timer_mode_flag = works_time;
				TFT_Display_WorksTime();



			}
		}

		if(timer_blink_times > 0 && gctl_t.mode_key_long_time_flag ==0){ //add key and dec key don't be pressed key
			timer_blink_times =0;
			if(gctl_t.timer_time_define_flag ==1){
				pro_t.timer_mode_flag = timer_time;
				pro_t.mode_key_confirm_flag =0xff;


				}
				else{
				pro_t.mode_key_confirm_flag =0xff;
				pro_t.timer_mode_flag = works_time;
				TFT_Display_WorksTime();
				}
			}

		}

		TFT_DonnotDisp_Works_Time();


	break;
	}



}


/**********************************************************************************************************
    **
    *Function Name:TFT_Donnot_Set_Timer_Time();
    *Function : 记录设置的定时时间，
    *Input Ref:
    *Return Ref:NO
    *
*********************************************************************************************************/
static void TFT_Donnot_Set_Timer_Time(void)
{
    if(gctl_t.timer_time_define_flag == 1){

	if(gctl_t.gTimer_ctl_set_timer_time_senconds >59){
		gctl_t.gTimer_ctl_set_timer_time_senconds =0;

		gctl_t.gSet_timer_minutes --;

		if(gctl_t.gSet_timer_minutes <0){
		gctl_t.gSet_timer_minutes =59;
		gctl_t.gSet_timer_hours --;


		}
		if(gctl_t.gSet_timer_hours < 0){

			pro_t.gPower_On = power_off;

		}

	}

   }

}