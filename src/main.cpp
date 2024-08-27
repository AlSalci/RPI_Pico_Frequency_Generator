#include <iostream>
//#include "../include/Memory.hpp"
#include "hardware/i2c.h"
#include "lwipopts.h"
#include "hardware/gpio.h"
#include "pico/stdio.h"
#include "../include/Wifi.hpp"
#include "hardware/flash.h" 
#include "hardware/sync.h" 

#define MEMORY_OFFSET (256*1024*4)


std::vector<int> frequency::outputs =
{
1 //GPIO frequency output
};
std::vector<int> frequency::inputs =
{
    16// GPIO interrupt for reseting credentials
};
//Frequency Initializations==========================================
uint frequency::period = 1000/2;
//===================================================================


//Wifi Credentials=============================================
credentials wifi_creds;//Non-volitile storage of wifi credentials
bool shouldConfigure = false;
//=============================================================


//Memory Storage Funtions 
bool wifi_info_to_memory();
void read_wifi_info_memory();
void print_buf(uint length);
const uint8_t* flash_target_contents = (const uint8_t*) (XIP_BASE + MEMORY_OFFSET);
//=========================================================================================================================

//MENU functions============================================================
MENU frequency::menu_state = CONFIG;
void display_menu();
void reset_info();
//=========================================================================================


int main()
{
    stdio_init_all();
    sleep_ms(1000);
    frequency freq;
    reset_info();
    display_menu(); // Initial display to either print confgure menu or reset menu

    //Web Server Initialization=================================
    server wifi;
    wifi.server_initialization(wifi_creds.SSID, wifi_creds.PASSWORD);
    //=========================================================

   



   
    while(true)
    {
        frequency::run_frequency();
    
    }
    return 0;

}


//MEMORY DEFINITIONS====================================================================================================================
bool wifi_info_to_memory()
{
    
    const uint8_t* temp = (const uint8_t*) (&wifi_creds);// Information as bytes
    unsigned int data_size = sizeof(wifi_creds);//Stores the size of the data to be stored
    int write_size = (data_size/FLASH_PAGE_SIZE)+1;//number of flash pages to write to
    int sector_count = ((write_size*FLASH_PAGE_SIZE)/FLASH_SECTOR_SIZE)+1;//How many sectors are used
    
    printf("Storing Information...\n");

    uint32_t interrupts = save_and_disable_interrupts();
      printf("Erasing Information...\n");
    flash_range_erase(MEMORY_OFFSET, FLASH_SECTOR_SIZE*sector_count);
   // print_buf(FLASH_PAGE_SIZE);
    
     printf("Writting Information...\n");
    flash_range_program(MEMORY_OFFSET, temp, FLASH_PAGE_SIZE*write_size);
     
    restore_interrupts(interrupts);
    printf("\nStorage Complete\n");
   // print_buf(FLASH_PAGE_SIZE);
    

    return true;
}

void read_wifi_info_memory()
{
    
    // print_buf(FLASH_PAGE_SIZE);
    memcpy(&wifi_creds,flash_target_contents,sizeof(wifi_creds));
}

void print_buf(uint length)
{
    for(int i = 0; i < length;i++)
    {
        printf("%d       ",flash_target_contents[i]);
        if(i %10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n");
}
//========================================================================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++==
//MENU DEFINITIONS============================================================================================================
void display_menu()
{
    switch(frequency::menu_state)
    {
    case IDLE:

    break;
    
    case RESET:
    printf("Enter SSID\n");
    std::cin>>wifi_creds.SSID;
    printf("%s\n",wifi_creds.SSID);
    printf("Enter Password\n");
    std::cin>>wifi_creds.PASSWORD;
    printf("%s\n",wifi_creds.PASSWORD);
    wifi_info_to_memory();

    
    break;
    
    case CONFIG:
    
     read_wifi_info_memory();
    printf("Configured\n");
    
    printf("%s\n",wifi_creds.SSID);
     printf("%s\n",wifi_creds.PASSWORD);
      break;
    }
}

void reset_info()
{
    printf("HOLD BUTTON TO RESET\n");
    sleep_ms(8000); //RESET PERIOD
    if(gpio_get(frequency::inputs[0]) == 1)
    {
        frequency::menu_state = RESET;
    }
  

}
//=======================================================================================================================
