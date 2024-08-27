#ifndef FREQUENCY_HPP
#define FREQUENCY_HPP
#include "PicoGPIOLib.hpp"

//Menu enum, defined here so interrupts can easily change information
enum MENU 
{
IDLE,
RESET,
CONFIG
};


class frequency 
{
private:


public:
frequency();

static std::vector<int> outputs;
static std::vector<int> inputs;
static MENU menu_state;

static void config_interrupt_callback(uint gpio,uint32_t event); // Allows wifi credentials to be reset 5 seconds into booting

static uint period;

static void run_frequency();


};

#endif