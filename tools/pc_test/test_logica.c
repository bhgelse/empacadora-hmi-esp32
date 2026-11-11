/* Prueba en PC de la lógica real de main.c y control_logic.c con una planta simulada (no usa hardware) */
#include "stub.h"
#include <stdlib.h>
#include <string.h>
static int64_t T_US=0; static int in_lvl[40], out_lvl[40];
static int hook_get(int p){return in_lvl[p];}
static int hook_set(int p,int l){out_lvl[p]=l;return 0;}
#define gpio_get_level(p) hook_get(p)
#define gpio_set_level(p,l) hook_set(p,l)
#define esp_timer_get_time() T_US
static int tick_hook(void); static int hq_recv(void*i); static int hq_send(const void*i); static int hq_uw(const void*b,int l);
#define ulTaskNotifyTake(a,b) tick_hook()
#define xQueueReceive(q,i,t) hq_recv(i)
#define xQueueSend(q,i,t) hq_send(i)
#undef uart_write_bytes
#define uart_write_bytes(p,b,l) hq_uw(b,l)
#include "../../firmware/src/control_logic.c"
#include "../../firmware/src/main.c"
static cmd_t Q[16]; static int qn=0,qh=0; static char last[400];
static int hq_recv(void*i){ if(qh<qn){memcpy(i,&Q[qh++],sizeof(cmd_t));return 1;} qh=qn=0; return 0;}
static int hq_send(const void*i){ if(qn<16){memcpy(&Q[qn++],i,sizeof(cmd_t));} return 1;}
static int hq_uw(const void*b,int l){ if(l>399)l=399; memcpy(last,b,l); last[l]=0; return l;}
static int getn(const char*k){char p[24];snprintf(p,sizeof p,"\"%s\":",k);char*q=strstr(last,p);return q?atoi(q+strlen(p)):-1;}
static int ph=0,k=0,t0=0,freeze=0,fails=0; static float W1,W2;
#define CHECK(c,msg) do{ if(!(c)){printf("  FALLA: %s\n",msg);fails++;} else printf("  ok: %s\n",msg);}while(0)
static int tick_hook(void){
  T_US+=10000; k++;
  /* planta: caudal grueso 12 kg/s, fino 2,5 kg/s, descarga 25 kg/s */
  float dt=.01f; if(out_lvl[18]) g_raw=g_raw+12*dt; if(out_lvl[19]) g_raw=g_raw+2.5f*dt;
  if(out_lvl[21]){ g_raw=g_raw-25*dt; if(g_raw<0)g_raw=0; }
  if(!freeze){ g_raw_ms=(uint32_t)(T_US/1000); g_raw_ok=true; }
  int now=k;
  switch(ph){
  case 0: if(k==2){g_raw=0; parse_cmd("{\"cmd\":\"start\"}"); ph=1;t0=now;} break;
  case 1: if(out_lvl[18]&&out_lvl[19]){printf("1) INICIO: abren grueso y fino juntos\n");ph=2;} else if(now-t0>200){CHECK(0,"abren grueso+fino");ph=2;} break;
  case 2: if(!out_lvl[18]&&out_lvl[19]){W1=g_raw;printf("2) cierra el grueso en %.2f kg y sigue el fino\n",W1);CHECK(W1>=39.0f&&W1<=40.5f,"corte de grueso cerca de 39,5");ph=3;} break;
  case 3: if(!out_lvl[19]){W2=g_raw;printf("3) cierra el fino en %.2f kg\n",W2);CHECK(W2>=49.4f&&W2<=50.2f,"cierre del fino cerca de 49,7");CHECK(getn("estado")==2,"estado LLENO esperando pedal");ph=4;t0=now;} break;
  case 4: if(now-t0>100){CHECK(out_lvl[21]==0,"sin pedal NO descarga (100 pasos)"); in_lvl[15]=0; ph=5;t0=now;} break;
  case 5: if(out_lvl[21]){printf("4) pedal pisado: descarga abierta\n");} if(now-t0>=5){in_lvl[15]=1;ph=6;t0=now;} break; /* suelta el pedal a los 50 ms */
  case 6: if(now-t0>20){CHECK(out_lvl[21]==1,"suelto el pedal y la descarga CONTINÚA"); ph=7;} break;
  case 7: if(!out_lvl[21]){printf("5) descarga terminó con peso %.2f kg\n",g_raw);CHECK(g_raw<=1.0f,"balde vacío al terminar"); ph=8;t0=now;} break;
  case 8: if(out_lvl[18]&&out_lvl[19]){printf("6) INICIO sostenido (HMI): vuelve a llenar solo\n");ph=9;t0=now;} else if(now-t0>300){CHECK(0,"reinicia llenado");ph=9;t0=now;} break;
  case 9: if(now-t0>50){ in_lvl[33]=0; ph=10;} break;                       /* PARO físico */
  case 10: CHECK(!out_lvl[18]&&!out_lvl[19]&&!out_lvl[21],"PARO: salidas en 0 en el MISMO ciclo (10 ms)"); CHECK(getn("estado")==0,"estado detenida"); in_lvl[33]=1; ph=11;t0=now; break;
  case 11: if(now-t0>20){ g_raw=60; ph=12;t0=now;} break;                    /* sobrellenado */
  case 12: if(now-t0>5){CHECK(alarma==ALM_SOBRE,"sobrellenado: alarma 1"); CHECK(!out_lvl[18]&&!out_lvl[19],"llenado bloqueado");
            parse_cmd("{\"cmd\":\"ack\"}"); ph=13;t0=now;} break;
  case 13: if(now-t0>5){CHECK(alarma==ALM_NONE,"RECONOCER limpia la alarma (aunque el peso siga alto)");
            parse_cmd("{\"cmd\":\"start\"}"); ph=14;t0=now;} break;
  case 14: if(now-t0>20){CHECK(!out_lvl[18]&&!out_lvl[19],"con peso alto el llenado sigue bloqueado y no se re-dispara la alarma");
            parse_cmd("{\"cmd\":\"stop\"}"); g_raw=7; ph=15;t0=now;} break;
  case 15: if(now-t0>10){ parse_cmd("{\"cmd\":\"vaciar\"}"); ph=16;t0=now;} break;
  case 16: if(now-t0>10){CHECK(getn("purga")==1&&getn("estado")==2,"VACIAR: espera el pedal"); in_lvl[15]=0; ph=17;t0=now;} break;
  case 17: if(out_lvl[21]){in_lvl[15]=1;ph=18;t0=now;} else if(now-t0>100){CHECK(0,"vaciar descarga con pedal");ph=18;t0=now;} break;
  case 18: if(!out_lvl[21]&&now-t0>20){CHECK(getn("estado")==0&&getn("purga")==0,"VACIAR terminó y no reinició el llenado"); parse_cmd("{\"cmd\":\"start\"}"); ph=19;t0=now;} break;
  case 19: if(now-t0>20){ freeze=1; ph=20;t0=now;} break;                    /* el IND236 deja de enviar */
  case 20: if(alarma==ALM_SIN_PESO){printf("7) sin lectura de peso: alarma 2 a los %d ms\n",(now-t0)*10);CHECK((now-t0)*10<=620,"alarma antes de ~600 ms");CHECK(!out_lvl[18]&&!out_lvl[19],"llenado cerrado");
            printf("\nRESULTADO: %s\n",fails?"HAY FALLAS":"TODO OK"); exit(fails?1:0);} else if(now-t0>200){CHECK(0,"alarma sin peso");exit(1);} break;
  }
  return 0;
}
int main(void){ for(int i=0;i<40;i++) in_lvl[i]=1; task_control(NULL); return 0; }
esp_err_t ind236_init(void){return 0;}
esp_err_t ind236_read_continuous(float*p,TickType_t e){(void)p;(void)e;return ESP_ERR_TIMEOUT;}
