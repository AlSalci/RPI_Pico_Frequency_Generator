#include "../include/Wifi.hpp"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
//#include <cmath>
#include "math.h"



server::server()
{
 
    

}


void server::server_initialization(const char *WIFI_SSID,const char *WIFI_PASSWORD)
{
   
     cyw43_arch_init();

    cyw43_arch_enable_sta_mode();

    // Connect to the WiFI network - loop until connected
    while(cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0){
        printf("Attempting to connect...\n");
      
    }
    // Print a success message once connected
    printf("Connected! \n");

      //Prints IP address of device  
      extern cyw43_t cyw43_state;
        auto ip_addr = cyw43_state.netif[CYW43_ITF_STA].ip_addr.addr;
        printf("IP Address: %lu.%lu.%lu.%lu\n", ip_addr & 0xFF, (ip_addr >> 8) & 0xFF, (ip_addr >> 16) & 0xFF, (ip_addr >> 24) & 0x000000FF);
    
    // Initialise web server
    httpd_init();
    printf("Http server initialised\n");

    // Configure SSI and CGI handler
    ssi_init(); 
    printf("SSI Handler initialised\n");
    cgi_init();
    printf("CGI Handler initialised\n");
    
}
//CGI Funtions ========================================================================================================
void server::cgi_init(void)
{

  http_set_cgi_handlers(cgi_handlers, 1);
}

const tCGI server::cgi_handlers[]
{
        
        "/Frequency", server::cgi_handler,
      
};

const char * server::cgi_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
     //EXMAPLE CODE FROM HTML
     if(strcmp(pcParam[0], "freq") == 0)
    {
      if(strcmp(pcValue[0], "0") == 0)
      {
        frequency::period =100000/2; //10hz
      } else if(strcmp(pcValue[0], "1") ==0)
      {
        frequency::period =20000/2;//50hz
        
      } else if(strcmp(pcValue[0], "2") ==0)
      {
       frequency::period =10000/2; //100hz

      } else if(strcmp(pcValue[0], "3") ==0)
      {
        frequency::period =5000/2; //200hz
      } else if(strcmp(pcValue[0], "4") ==0)
      {
       frequency::period =3300/2; //300hz

      } else if(strcmp(pcValue[0], "5") ==0)
      {
         frequency::period =2500/2; //400hz

    
      } else if(strcmp(pcValue[0], "6") ==0)
      {
         frequency::period =2000/2; //500hz

       

      } else if(strcmp(pcValue[0], "7") ==0)
      {
         frequency::period =1600/2; //600hz

    
      } else if(strcmp(pcValue[0], "8") ==0)
      {
        frequency::period =1400/2; //700hz


      } else if(strcmp(pcValue[0], "9") ==0)
      {
         frequency::period =1250/2; //800hz

    
      } else if(strcmp(pcValue[0], "10") ==0)
      {
         frequency::period =1100/2; //900hz


      } else if(strcmp(pcValue[0], "11") ==0)
      {
         frequency::period =1000/2; //1khz

    
      } else if(strcmp(pcValue[0], "12") ==0)
      {
        frequency::period =900/2; //1.1hz


      } else if(strcmp(pcValue[0], "13") ==0)
      {
         frequency::period =800/2; //1.2khz

    
      } else 
      {
       

      }
      
       
    } 

    //Assures that website sends data back
     return "/index.shtml";
}
//==========================================================================================================

//SSI FUNCTIONS=============================================================================================
const char * server::ssi_tags[] = 
{
"TEMP"
};

void server::ssi_init()
{
     http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}

u16_t server::ssi_handler(int iIndex, char *pcInsert, int iInsertLen)
{
  size_t printed;

  //EXAMPLE FROM HTML
  switch(iIndex)
  {
  
    default:
    printed = 0;
    break;
  }
  return (u16_t)printed;
}

//==================================================================================================





