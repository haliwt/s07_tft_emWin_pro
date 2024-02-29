#include "bsp.h"

uint8_t sub_send_power_on_times;
uint8_t get_rx_beijing_time_enable;

uint8_t step_flag;
uint8_t beijing_step;
uint8_t auto_det_flag;



static void MainBoard_Self_Inspection_PowerOn_Fun(void);
static void RunWifi_Command_Handler(void);
static void auto_repeat_link_netware_fun(void);
static void auto_repeat_init_link_net(void);
static void auto_repeat_tencnet_net(void);





/********************************************************************************
	*
	*Functin Name:void WIFI_Process_Handler(void)
	*Functin :
	*Input Ref: NO
	*Return Ref:NO
	*
********************************************************************************/
void WIFI_Process_Handler(void)
{
  	MainBoard_Self_Inspection_PowerOn_Fun();
    RunWifi_Command_Handler();
    if(wifi_t.get_rx_beijing_time_enable==0){
     Tencent_Cloud_Rx_Handler();
	 Json_Parse_Command_Fun();
    }
}
/**********************************************************************
	*
	*Functin Name: void MainBoard_Itself_PowerOn_Fun(void)
	*Function :
	*Input Ref:  key of value
	*Return Ref: NO
	*
**********************************************************************/
static void MainBoard_Self_Inspection_PowerOn_Fun(void)
{
    static uint8_t self_power_on_flag=0,send_power_off_flag;
    
   
	if(wifi_t.first_power_on_link_net==0 && wifi_t.power_on_login_tencent_cloud_flag !=5){
        //Buzzer_KeySound();
		InitWifiModule_Hardware();//InitWifiModule();
        SmartPhone_TryToLink_TencentCloud();
		if(wifi_link_net_state()==1){
			wifi_t.runCommand_order_lable= wifi_publish_update_tencent_cloud_data;//04
	    }
       
    }

	if(wifi_link_net_state() ==1 && send_power_off_flag !=3 && pro_t.gPower_On== power_off){

	      if(send_power_off_flag==0){
			  send_power_off_flag++;
		     MqttData_Publish_PowerOff_Ref();
			 wifi_t.gTimer_power_first_link_tencent =0;

		    }

		    if(send_power_off_flag==1 && wifi_t.gTimer_power_first_link_tencent >0){
			  send_power_off_flag++;

			    Subscriber_Data_FromCloud_Handler();
			    wifi_t.gTimer_power_first_link_tencent =0;

		    }

			if(send_power_off_flag==2 && wifi_t.gTimer_power_first_link_tencent >0){

				  send_power_off_flag=3;
				  wifi_t.gTimer_power_first_link_tencent=0;
            }

			
			
		  
	}
}
/********************************************************************************
   *
   *Function Name: void Wifi_RunCmd(void)
   *Funciton : separately update value 
   *Input Ref:NO
   *Return Ref:NO
   *
*********************************************************************************/
static void RunWifi_Command_Handler(void)
{
  
    static uint8_t first_sub,sub_to_tencent_flag,disp_beijing;

	static uint8_t  update_data_to_tencent_cloud_flag;
	uint8_t i;

     switch(wifi_t.runCommand_order_lable){

         
	    case wifi_has_been_connected:
		  first_sub=0;

		  wifi_t.get_rx_beijing_time_enable=0;
		 
		 
		 
	     if(wifi_link_net_state()==1){
		 
		  	wifi_t.linking_tencent_cloud_doing=0;
	        wifi_t.has_been_login_flag = 1;
			wifi_t.get_rx_beijing_time_enable=0;
			wifi_t.gTimer_main_pro_times =0;
			wifi_t.runCommand_order_lable = wifi_tencent_publish_init_data;//wifi_tencent_subscription_data;
			step_flag =1;
			
				
		  }

		break;

        case wifi_link_tencent_cloud: //02

		   if(power_on_state() == power_on){
			
			Wifi_Fast_Led_Blink(); 
			Wifi_SoftAP_Config_Handler();
	        SmartPhone_LinkTencent_Cloud();
	     
	      if(wifi_link_net_state()==1){
			   
				wifi_t.get_rx_beijing_time_enable=0;
			    wifi_t.runCommand_order_lable = wifi_tencent_publish_init_data;
                wifi_t.gTimer_publish_dht11=0;
				wifi_t.gTimer_auto_detected_net_state_times =0;
			    step_flag=1;
				
			}
		   }
           
           if(wifi_link_net_state()==0){
             if(wifi_t.gTimer_linking_tencent_duration < 166){
                 wifi_t.runCommand_order_lable = wifi_link_tencent_cloud;
             }
             else{
              wifi_t.runCommand_order_lable = wifi_null;
              
              }
           
           }
	    break;

	  	
	  	case wifi_tencent_publish_init_data://03
			
		    if(step_flag==1){
				step_flag++;
		        Update_Dht11_Totencent_Value();
				wifi_t.gTimer_publish_dht11=0;
			}
		
		  
			 if(wifi_t.gTimer_publish_dht11>0){
                  wifi_t.runCommand_order_lable= wifi_publish_update_tencent_cloud_data;
                  wifi_t.gTimer_auto_detected_net_state_times =0;
	            }
	
		
		 
       	break;


	   	case wifi_publish_update_tencent_cloud_data://04
            
		      if(power_on_state() ==power_on && wifi_t.gTimer_get_beijing_time > 180 && (wifi_link_net_state()==1 && wifi_t.get_rx_auto_repeat_net_enable==0)){
			  	wifi_t.beijing_time_flag =1;
			    wifi_t.gTimer_auto_detected_net_state_times =0;
				wifi_t.gTimer_get_beijing_time=0;
				wifi_t.get_rx_beijing_time_enable=0;//disenable get beijing timing
                if(wifi_t.get_rx_auto_repeat_net_enable==0){
			           wifi_t.runCommand_order_lable= wifi_get_beijing_time;
					   wifi_t.set_beijing_time_flag =1;
                }
				else{


				}
				

				}

			  if(wifi_t.real_hours < 25 && wifi_t.real_minutes < 61 && beijing_step ==3){

				beijing_step ++;
				gctl_t.disp_works_hours   = wifi_t.real_hours;
				
				gctl_t.disp_works_minutes = wifi_t.real_minutes;
				
				gctl_t.gTimer_ctl_disp_second= wifi_t.real_seconds;
				TFT_Only_Disp_Timing();

				}
 
			   if(wifi_t.gTimer_auto_detected_net_state_times > 30){
				
				 wifi_t.gTimer_auto_detected_net_state_times=0;
				
				
				 wifi_t.wifi_uart_counter=0;
				  

				
				  if(wifi_t.auto_link_login_tencent_cloud_flag==0){
				  	    wifi_t.get_rx_auto_repeat_net_enable=1;
				        Wifi_Link_Tencent_Net_State();
				        wifi_t.gTimer_publish_dht11=0;

				  }
				  else{
                    //  Wifi_Reconnect_Tencent_Net();
                      wifi_t.get_rx_auto_repeat_net_enable=0;
					  wifi_t.power_on_login_tencent_cloud_flag =0;
					  wifi_t.gTimer_publish_dht11=1;
					  auto_det_flag=1 ;
					 


				  }
				  
				
				   wifi_t.runCommand_order_lable= wifi_auto_repeat_link_cloud;

            }
			

		  break;

		  case wifi_auto_repeat_link_cloud://06

		      if(wifi_t.gTimer_publish_dht11 >0){

		        switch(wifi_t.auto_link_login_tencent_cloud_flag){


				case 0:  //link net is ok

				

                    Wifi_Rx_Auto_Link_Net_Handler();
				    wifi_t.get_rx_auto_repeat_net_enable=0;
				    wifi_t.gTimer_publish_dht11=0;
				    wifi_t.runCommand_order_lable = wifi_tencent_publish_init_data;
                 
                break;

				case 1:  //don't link to tencet cloud net.
				      
				       auto_repeat_link_netware_fun();
//				   //   Wifi_Rx_Auto_Link_Net_Handler();
//					 wifi_t.get_rx_auto_repeat_net_enable=0;
//				    wifi_t.gTimer_publish_dht11=0;
				    wifi_t.runCommand_order_lable = wifi_tencent_publish_init_data;


				break;
			 
			}

		   }

	   break;

        case wifi_tencent_publish_dht11_data://05
	   
		wifi_t.get_rx_beijing_time_enable=0;
		if(power_on_state() == power_on){
			
           if(update_data_to_tencent_cloud_flag == 1){
		   	   update_data_to_tencent_cloud_flag++;
               Update_Dht11_Totencent_Value();
		   
			  wifi_t.gTimer_publish_dht11=0;

		  }
			
		  if(update_data_to_tencent_cloud_flag==2 && wifi_t.gTimer_publish_dht11 > 0){
			  update_data_to_tencent_cloud_flag++;

		      wifi_t.runCommand_order_lable= wifi_publish_update_tencent_cloud_data;

		  }
		}
	   break;

	   case wifi_get_beijing_time://6

	 
		 wifi_t.linking_tencent_cloud_doing =0;
	   	 if(wifi_t.set_beijing_time_flag ==1){   //&& wifi_t.gTimer_beijing_time>1){
			 wifi_t.set_beijing_time_flag ++;
		     wifi_t.get_rx_beijing_time_enable=1; //enable beijing times
		     wifi_t.wifi_uart_counter=0;
             Get_BeiJing_Time_Cmd();
			 wifi_t.gTimer_read_beijing_time=0;
			 beijing_step =1;
			 
	   	 	}

		   //if(wifi_t.gTimer_read_beijing_time > 2 && wifi_t.gTimer_read_beijing_time < 4){
	       if(wifi_t.gTimer_read_beijing_time > 0 && beijing_step ==1){//
			    beijing_step =2;
				wifi_t.beijing_time_flag =0;
			   	Get_Beijing_Time();
				wifi_t.gTimer_read_beijing_time=0;
				

	       }

		    if(beijing_step ==2 && wifi_t.gTimer_read_beijing_time > 2){
				
				beijing_step =3;
			    wifi_t.beijing_time_flag = 1;
               
				  	wifi_t.real_hours = (wifi_t.wifi_data[134]-0x30)*10 + wifi_t.wifi_data[135]-0x30;
					wifi_t.real_minutes =(wifi_t.wifi_data[137]-0x30)*10 + wifi_t.wifi_data[138]-0x30;
				    wifi_t.real_seconds = (wifi_t.wifi_data[140]-0x30)*10 + wifi_t.wifi_data[141]-0x30;
				
			        wifi_t.get_rx_beijing_time_enable=0; //enable beijing times

				
				
		         wifi_t.runCommand_order_lable=wifi_publish_update_tencent_cloud_data;
	       }
		   else if(beijing_step== 3){
		   	     

		       wifi_t.runCommand_order_lable=wifi_publish_update_tencent_cloud_data;
               wifi_t.get_rx_beijing_time_enable=0; //enable beijing times
		   }

			
		
		
    
	    break;

	   
	  default:

	   break;
	 
     }
  
}
 
/********************************************************************************
	*
	*Functin Name:static void auto_repeat_link_netware_fun(void)
	*Functin :
	*Input Ref: NO
	*Return Ref:NO
	*
********************************************************************************/

static void auto_repeat_link_netware_fun(void)
{

  
  if(auto_det_flag==1 && wifi_t.power_on_login_tencent_cloud_flag !=5){
        //Buzzer_KeySound();
      
		//InitWifiModule_Hardware();//InitWifiModule();
        auto_repeat_init_link_net();
        //SmartPhone_TryToLink_TencentCloud();
        auto_repeat_tencnet_net();
  }

    if(wifi_link_net_state()==1){

		  wifi_t.runCommand_order_lable= wifi_publish_update_tencent_cloud_data;//04
		  auto_det_flag=0;
            
		  wifi_t.gTimer_auto_detected_net_state_times=0;  
	 }

	if(wifi_t.power_on_login_tencent_cloud_flag==5){
		wifi_t.gTimer_auto_detected_net_state_times=0;
  
		wifi_t.get_rx_auto_repeat_net_enable=0;
		wifi_t.gTimer_publish_dht11=0;
		wifi_t.runCommand_order_lable = wifi_tencent_publish_init_data;

	}
	
   
}


void Wifi_Rx_Auto_Link_Net_Handler(void)
{

       uint8_t i;
	   strncpy((char *)wifi_t.auto_det_data, (const char *)wifi_t.wifi_data,150);
	   wifi_t.get_rx_auto_repeat_net_enable =1;


	
	   
	   if(strstr((const char*)wifi_t.auto_det_data,"QTTSTATE:0")){

			 wifi_t.esp8266_login_cloud_success=0;
             wifi_t.gTimer_auto_detected_net_state_times=0;
		     wifi_t.auto_link_login_tencent_cloud_flag =1;
				  
	    }
		else if(strstr((const char*)wifi_t.auto_det_data,"+TCMQTTRECONNECTING")){

			 wifi_t.esp8266_login_cloud_success=0;
             wifi_t.gTimer_auto_detected_net_state_times=0;
		     wifi_t.auto_link_login_tencent_cloud_flag =1;
				  
	    }
		else if(strstr((const char*)wifi_t.auto_det_data,"ONNECTING")){

			 wifi_t.esp8266_login_cloud_success=0;
             wifi_t.gTimer_auto_detected_net_state_times=0;
		     wifi_t.auto_link_login_tencent_cloud_flag =1;
				  
	    }
		
		else if(strstr((const char*)wifi_t.auto_det_data,"QTTSTATE:1")){

		   wifi_t.esp8266_login_cloud_success= 1;
		   wifi_t.auto_link_login_tencent_cloud_flag =0;


       }
       
         wifi_t.wifi_uart_counter=0;
		
         wifi_t.gTimer_auto_detected_net_state_times=0;
		
    
}


static void auto_repeat_init_link_net(void)
{
	    WIFI_IC_DISABLE();
		HAL_Delay(1000);
		//HAL_Delay(1000);
		//HAL_Delay(1000);
		WIFI_IC_ENABLE();
		//at_send_data("AT+RESTORE\r\n", strlen("AT+RESTORE\r\n"));
		at_send_data("AT+RST\r\n", strlen("AT+RST\r\n"));
		HAL_Delay(1000);



}

static void auto_repeat_tencnet_net(void)
{
            wifi_t.linking_tencent_cloud_doing =1;
          
			wifi_t.wifi_uart_counter=0;
	        wifi_t.soft_ap_config_flag =0;
	        HAL_UART_Transmit(&huart2, "AT+TCMQTTCONN=1,5000,240,0,1\r\n", strlen("AT+TCMQTTCONN=1,5000,240,0,1\r\n"), 5000);//开始连接
		    HAL_Delay(1000);
			HAL_Delay(1000);
			HAL_Delay(1000);
		
		
		 


}

