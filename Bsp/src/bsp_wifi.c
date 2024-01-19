#include "bsp.h"

uint8_t sub_send_power_on_times;
uint8_t get_rx_beijing_time_enable;


static void MainBoard_Self_Inspection_PowerOn_Fun(void);
static void RunWifi_Command_Handler(void);
static void AutoReconnect_Wifi_Neware_Function(void);


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
    static uint8_t self_power_on_flag=0,send_power_off_flag=0;
    

	if(self_power_on_flag==0){
        self_power_on_flag ++ ;
	
        Buzzer_KeySound();

    
		InitWifiModule_Hardware();//InitWifiModule();
		HAL_Delay(1000);
        SmartPhone_TryToLink_TencentCloud();
		if(wifi_link_net_state()==1){
			
			wifi_t.runCommand_order_lable= wifi_tencent_subscription_data;//04
	
			//SendWifiData_To_Cmd(0x01) ;
            //HAL_Delay(5);
          }
       
    }

	 if(wifi_link_net_state()==1 && power_on_state()  !=power_on ){
       
           if(send_power_off_flag==0){
            send_power_off_flag++;
		    //run_t.RunCommand_Label=power_off;
		   // pro.rx_command_tag= power_off;
			//wifi_t.runCommand_order_lable = wifi_publish_update_tencent_cloud_data
			//SendWifiData_To_Cmd(0x01) ;
			HAL_Delay(50);
               
           }
   			
	}
    
   
}
/***********************************************
   *
   *Function Name: void Wifi_RunCmd(void)
   *Funciton : separately update value 
   *
   *
***********************************************/
static void RunWifi_Command_Handler(void)
{
  
	
    static uint8_t first_sub,sub_to_tencent_flag;

	static uint8_t  get_bj_times=0;

     switch(wifi_t.runCommand_order_lable){

         
	    case wifi_has_been_connected:
		  first_sub=0;

		  wifi_t.get_rx_beijing_time_enable=0;
		 
		 
		 
	     if(wifi_link_net_state()==1){
		  	wifi_t.linking_tencent_cloud_doing=0;
	
	       
			wifi_t.has_been_login_flag = 1;
			wifi_t.get_rx_beijing_time_enable=0;
			wifi_t.runCommand_order_lable = wifi_tencent_publish_init_data;//wifi_tencent_subscription_data;
			
				
		  }

		break;

        case wifi_link_tencent_cloud: //02

		   if(power_on_state() == power_on){
			
			 
			Wifi_SoftAP_Config_Handler();
	        SmartPhone_LinkTencent_Cloud();
	     
	      if(wifi_link_net_state()==1){
			
				wifi_t.get_rx_beijing_time_enable=0;
			    wifi_t.runCommand_order_lable = wifi_tencent_publish_init_data;
                
				
			}
		   }
           
           if(wifi_link_net_state()==0){
             if(wifi_t.gTimer_linking_tencen_counter < 166){
                 wifi_t.runCommand_order_lable = wifi_link_tencent_cloud;
             }
             else{
              wifi_t.runCommand_order_lable = wifi_null;
              wifi_t.wifi_run_set_restart_flag =0;
              }
           
           }
	    break;

	  	
	  	case wifi_tencent_publish_init_data://03
		  
			do{
			  
				 MqttData_Publish_SetOpen(0x01);
		         HAL_Delay(200);
		         Publish_Data_ToTencent_Initial_Data();
				 HAL_Delay(350);

				Subscriber_Data_FromCloud_Handler();
				HAL_Delay(350);
	           

			   
			     sub_to_tencent_flag=0;
				
				wifi_t.runCommand_order_lable= wifi_tencent_subscription_data;
	           
			}while(sub_to_tencent_flag);
		
		 
       	break;

		
		case wifi_tencent_subscription_data://04
           
		   wifi_t.runCommand_order_lable= wifi_publish_update_tencent_cloud_data;
					
			
		break;

	   	case wifi_publish_update_tencent_cloud_data://05
            
		      while(wifi_t.beijing_time_flag == 1 && power_on_state() ==power_on){
				wifi_t.beijing_time_flag ++;
				wifi_t.gTimer_get_beijing_time=0;
				wifi_t.get_rx_beijing_time_enable=0;//disenable get beijing timing

				if(get_bj_times < 2){
				get_bj_times++;
				wifi_t.runCommand_order_lable= wifi_get_beijing_time;
				wifi_t.set_beijing_time_flag =1;

				}

//				if(wifi_t.real_hours < 25 && wifi_t.real_minutes < 61){

//				SendData_Real_GMT(wifi_t.real_hours);
//				HAL_Delay(10);
//				SendData_Real_GMT_Minute(wifi_t.real_minutes);
//				HAL_Delay(10);
//				SendData_Real_GMT_Second(wifi_t.real_seconds);
//				HAL_Delay(10);
//				}

			  }

              if(wifi_t.gTimer_publish_dht11 >138){
				  wifi_t.gTimer_publish_dht11=0;

				wifi_t.runCommand_order_lable= wifi_tencent_publish_dht11_data;
			}

			if(wifi_t.gTimer_auto_detected_net_link_state > 9){		

				  wifi_t.gTimer_auto_detected_net_link_state=0;

			      AutoReconnect_Wifi_Neware_Function();
					
			 
			}
			 

	   break;



	   case wifi_tencent_publish_dht11_data://6
	   
		wifi_t.get_rx_beijing_time_enable=0;
		if(power_on_state() == power_on){
			if(wifi_t.app_timer_power_off_flag == 0 && power_on_state() ==power_on && (wifi_t.app_timer_power_on_flag==0||wifi_t.app_timer_power_on_flag==3)){
			Update_Dht11_Totencent_Value();
			HAL_Delay(300);

			}


			if(wifi_t.gTimer_get_beijing_time > 423 && power_on_state() ==power_on){ //&& gctl_t.power_on_send_bejing_times==0){ //
			wifi_t.gTimer_get_beijing_time=0;

			wifi_t.set_beijing_time_flag=1; //set beijing times .
			wifi_t.runCommand_order_lable= wifi_get_beijing_time;


			}
			else{

			wifi_t.runCommand_order_lable= wifi_publish_update_tencent_cloud_data;

			}

		}
		else{

		wifi_t.runCommand_order_lable= wifi_publish_update_tencent_cloud_data;

		}

	   break;

	   case wifi_get_beijing_time://7

	    if(power_on_state()==power_on ){
	 
		 wifi_t.linking_tencent_cloud_doing =0;
	   	 if(wifi_t.set_beijing_time_flag ==1){   //&& wifi_t.gTimer_beijing_time>1){
			 wifi_t.set_beijing_time_flag ++;
		     wifi_t.get_rx_beijing_time_enable=1; //enable beijing times
		     wifi_t.wifi_uart_counter=0;
             Get_BeiJing_Time_Cmd();
			 HAL_Delay(1000); //200
			 wifi_t.gTimer_read_beijing_time=0;
	   	 	}

		 
	       if(wifi_t.gTimer_read_beijing_time > 2 && wifi_t.gTimer_read_beijing_time < 4){
				wifi_t.gTimer_read_beijing_time=0;
			   	Get_Beijing_Time();
				HAL_Delay(300);
			    wifi_t.beijing_time_flag = 1;
				
			  	wifi_t.real_hours = (wifi_t.wifi_data[134]-0x30)*10 + wifi_t.wifi_data[135]-0x30;
				wifi_t.real_minutes =(wifi_t.wifi_data[137]-0x30)*10 + wifi_t.wifi_data[138]-0x30;
			     wifi_t.real_seconds = (wifi_t.wifi_data[140]-0x30)*10 + wifi_t.wifi_data[141]-0x30;
			     wifi_t.get_rx_beijing_time_enable=0; //enable beijing times
				
		         wifi_t.runCommand_order_lable=wifi_publish_update_tencent_cloud_data;
	        }
		   if(wifi_t.gTimer_read_beijing_time > 3){

		       wifi_t.runCommand_order_lable=wifi_publish_update_tencent_cloud_data;

		   }

			
		  }
		 else{

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
	*Functin Name:static void AutoReconnect_Wifi_Neware_Function(void)
	*Functin :
	*Input Ref: NO
	*Return Ref:NO
	*
********************************************************************************/
static void AutoReconnect_Wifi_Neware_Function(void)
{
  
     static uint8_t det_no_wifi_net=0;
			 
	if(wifi_t.wifi_reconnect_read_flag == 1 && det_no_wifi_net==0){

		det_no_wifi_net++;
		wifi_t.auto_link_cloud_flag=0;
		wifi_t.esp8266_login_cloud_success=0;
		gctl_t.wifi_flag = 0;

	}

	if(wifi_t.wifi_reconnect_read_flag == 1 && wifi_t.auto_link_cloud_flag==0 ){

		AutoRepeate_Link_Tencent_Cloud();
		wifi_t.runCommand_order_lable= wifi_publish_update_tencent_cloud_data;
	}

	if(det_no_wifi_net==1){

		if(wifi_link_net_state()==1){
			det_no_wifi_net=0;
			
			wifi_t.reconnect_tencent_cloud_flag=0;
			wifi_t.auto_link_cloud_flag=0xff;
			wifi_t.linking_tencent_cloud_doing =0;

			//SendWifiData_To_Cmd(0x01) ;
			HAL_Delay(30);


			Subscriber_Data_FromCloud_Handler();
			HAL_Delay(300);

			Publish_Data_ToTencent_Update_Data();
			HAL_Delay(300);
		}
	}

}


