#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
typedef int esp_err_t; typedef uint32_t TickType_t; typedef void* TaskHandle_t; typedef void* QueueHandle_t; typedef int BaseType_t;
typedef int uart_port_t; typedef uint32_t nvs_handle_t;
#define ESP_OK 0
#define ESP_ERR_TIMEOUT 0x107
#define ESP_ERR_NVS_NO_FREE_PAGES 0x110d
#define ESP_ERR_NVS_NEW_VERSION_FOUND 0x1110
#define pdTRUE 1
#define pdMS_TO_TICKS(x) ((TickType_t)(x))
#define xTaskNotifyGive(h) ((void)(h))
static inline uint32_t ulTaskNotifyTake(int a, TickType_t b){(void)a;(void)b;return 0;}
static inline QueueHandle_t xQueueCreate(int n,size_t s){(void)n;(void)s;return 0;}
static inline BaseType_t xQueueReceive(QueueHandle_t q,void*i,TickType_t t){(void)q;(void)i;(void)t;return 0;}
static inline BaseType_t xQueueSend(QueueHandle_t q,const void*i,TickType_t t){(void)q;(void)i;(void)t;return 1;}
typedef void (*TaskFunction_t)(void*);
static inline BaseType_t xTaskCreatePinnedToCore(TaskFunction_t f,const char*n,uint32_t st,void*a,int p,TaskHandle_t*h,int c){(void)f;(void)n;(void)st;(void)a;(void)p;(void)h;(void)c;return 1;}
static inline BaseType_t xTaskCreate(TaskFunction_t f,const char*n,uint32_t st,void*a,int p,TaskHandle_t*h){(void)f;(void)n;(void)st;(void)a;(void)p;(void)h;return 1;}
enum {UART_NUM_0,UART_NUM_1};
enum {UART_DATA_8_BITS,UART_PARITY_DISABLE,UART_STOP_BITS_1,UART_HW_FLOWCTRL_DISABLE,UART_SCLK_DEFAULT,UART_PIN_NO_CHANGE=-1};
typedef struct{int baud_rate,data_bits,parity,stop_bits,flow_ctrl,source_clk;} uart_config_t;
static inline esp_err_t uart_driver_install(int p,int a,int b,int c,void*d,int e){(void)p;(void)a;(void)b;(void)c;(void)d;(void)e;return 0;}
static inline esp_err_t uart_param_config(int p,const uart_config_t*c){(void)p;(void)c;return 0;}
static inline esp_err_t uart_set_pin(int p,int a,int b,int c,int d){(void)p;(void)a;(void)b;(void)c;(void)d;return 0;}
static inline esp_err_t uart_set_rx_timeout(int p,uint8_t t){(void)p;(void)t;return 0;}
static inline int uart_read_bytes(int p,void*b,uint32_t l,TickType_t t){(void)p;(void)b;(void)l;(void)t;return 0;}
static inline int uart_write_bytes(int p,const void*b,size_t l){(void)p;(void)b;(void)l;return (int)l;}
enum {GPIO_NUM_13=13,GPIO_NUM_15=15,GPIO_NUM_16=16,GPIO_NUM_17=17,GPIO_NUM_18=18,GPIO_NUM_19=19,GPIO_NUM_21=21,GPIO_NUM_25=25,GPIO_NUM_26=26,GPIO_NUM_27=27,GPIO_NUM_32=32,GPIO_NUM_33=33};
enum {GPIO_MODE_OUTPUT,GPIO_MODE_INPUT,GPIO_PULLUP_ENABLE,GPIO_PULLDOWN_DISABLE,GPIO_INTR_DISABLE};
typedef struct{uint64_t pin_bit_mask;int mode,pull_up_en,pull_down_en,intr_type;} gpio_config_t;
static inline esp_err_t gpio_config(const gpio_config_t*c){(void)c;return 0;}
static inline esp_err_t gpio_set_level(int p,uint32_t l){(void)p;(void)l;return 0;}
static inline int gpio_get_level(int p){(void)p;return 1;}
enum {ESP_LOG_NONE};
static inline void esp_log_level_set(const char*t,int l){(void)t;(void)l;}
#define ESP_LOGI(tag,fmt,...) printf(fmt "\n",##__VA_ARGS__)
#define ESP_RETURN_ON_ERROR(x,tag,msg) do{esp_err_t e_=(x);if(e_!=ESP_OK)return e_;}while(0)
static inline int64_t esp_timer_get_time(void){return 0;}
enum {NVS_READONLY,NVS_READWRITE};
static inline esp_err_t nvs_open(const char*n,int m,nvs_handle_t*h){(void)n;(void)m;(void)h;return 0;}
static inline esp_err_t nvs_set_blob(nvs_handle_t h,const char*k,const void*v,size_t l){(void)h;(void)k;(void)v;(void)l;return 0;}
static inline esp_err_t nvs_get_blob(nvs_handle_t h,const char*k,void*v,size_t*l){(void)h;(void)k;(void)v;(void)l;return 0;}
static inline esp_err_t nvs_commit(nvs_handle_t h){(void)h;return 0;}
static inline void nvs_close(nvs_handle_t h){(void)h;}
static inline esp_err_t nvs_flash_init(void){return 0;}
static inline esp_err_t nvs_flash_erase(void){return 0;}
