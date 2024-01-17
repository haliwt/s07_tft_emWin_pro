#ifndef __BSP_WIFI_FUN_
#define __BSP_WIFI_FUN_
#include "main.h"


typedef enum{
  
   wifi_AI=0x08 ,wifi_notAI=0x18,wifi_kill=0x04,wifi_notkill=0x14,
   wifi_heat= 0x02,wifi_notheat=0x12


}wifi_mode_t;

typedef enum _wifi_state_t{  
	
    wifi_has_been_connected =0x01,
	wifi_link_tencent_cloud, //2
	wifi_tencent_publish_init_data, //3
	wifi_tencent_subscription_data, //4
	wifi_publish_update_tencent_cloud_data,//5
	wifi_tencent_publish_dht11_data,
	wifi_get_beijing_time,
	wifi_disconnect,
	wifi_null


}wifi_state_t;


/* USER CODE BEGIN Prototypes */
typedef struct usart
{
    unsigned char UART_Data[150]; 
    unsigned char UART_Flag;
    unsigned int wifi_uart_counter;
    unsigned char wifi_inputBuf[1];
}USART_DataBuf;






typedef struct _WIFI_FUN{
	

    uint8_t data[512];
    uint8_t  data_size;
    uint8_t flag;
	uint8_t wifi_RunState;
	uint8_t esp8266_smartphone_flag;
	uint8_t esp8266_link_cloud_flag;
	uint8_t soft_ap_config_success;
	uint8_t esp8266_login_cloud_success;

	uint8_t subscribe_cloud_success;
	
	
	uint8_t esp8266_dynamic_reg_flag;
    uint8_t subscribe_flag;
	uint8_t subscribe_rx_flag;
    uint8_t subscribe_rxCloud_flag;
	uint8_t esp8266_data_rx_success;
	uint8_t rx_data_success ;
	uint8_t  rx_counter ;
	uint8_t  rx_data_state;
	uint8_t getCloudValue_unit ;
	uint8_t getCloudValue_decade;
	uint8_t rx_data_len;
	uint8_t rx_data_name_len;
	uint8_t linking_tencent_cloud_doing;
    uint8_t cmp_flag;
	uint8_t send_tencent_cloud_data_lable;
    uint8_t subscrible_receive_data_label;
    //esp8266 up ref

	uint8_t runCommand_order_lable;
	uint8_t has_been_login_flag;
    uint8_t soft_ap_config_flag;
    uint8_t get_rx_beijing_time_enable;
	
	//wifi
	unsigned char wifi_data[150]; 
	uint8_t wifi_reconnect_read_flag;
	uint8_t wifi_uart_counter;
	uint8_t tencent_cloud_command_power_on;
	uint8_t wifi_run_set_restart_flag;
	uint8_t auto_link_cloud_flag;
	uint8_t response_wifi_signal_label;
    //sensor dht11 
	uint8_t gDht11_temperature;
	uint8_t gDht11_humidity;

    //real time 
    uint8_t real_hours;
	uint8_t real_minutes;
	uint8_t real_seconds;
	uint8_t restart_link_tencent_cloud ;
	uint8_t received_data_from_tencent_cloud ;
	//beijing time
	uint8_t set_beijing_time_flag;
	uint8_t beijing_time_flag ;

	//smart phone of ref
	uint8_t app_timer_power_off_flag;
	uint8_t app_timer_power_on_flag;

	//wifi gtimer
	uint8_t gTimer_read_beijing_time;
	uint8_t gTimer_linking_tencen_counter;
	

  

    uint8_t gTimer_reconnect_wifi_order;
	uint8_t gTimer_beijing_time;
	uint8_t gTimer_reconnect_wifi;
	uint8_t gTimer_power_off;
	uint8_t gTimer_subscriber_send ;
	uint8_t gTimer_publish_dht11;
	uint8_t gTimer_auto_detected_net_link_state;
    uint16_t gTimer_get_beijing_time;
	
		
	
}WIFI_FUN;

extern WIFI_FUN   wifi_t;

extern void (*PowerOn)(void); //函数指针
extern void (*PowerOff)(void);
extern void (*Ai_Fun)(uint8_t sig);
extern void (*SetTimes)(void);
extern void (*SetTemperature)(void);

void PowerOn_Host(void (*poweronHandler)(void));
void PowerOff_Host(void (*poweroffHandler)(void));




void wifiDisplayTemperature_Humidity(void);


void wifiUpdate_SetTimeValue(uint8_t tv);
void wifiUpdate_SetTemperatureValue(uint8_t temp);

void RunWifi_Command_Handler(void);
void GetNTP_Times(void);


#endif 

