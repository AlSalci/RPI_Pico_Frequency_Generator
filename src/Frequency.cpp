#include "../include/Frequency.hpp"
#include "hardware/gpio.h"


frequency::frequency()
{
    gpio_pin_init(outputs, false);
    gpio_pin_init(inputs, true);

    gpio_set_irq_enabled_with_callback(inputs[0], GPIO_IRQ_EDGE_FALL, true, &config_interrupt_callback);
}

 void frequency::config_interrupt_callback(uint gpio,uint32_t event)
{
printf("RESETING WIFI INFO\n");
 menu_state = RESET;
}

void frequency::run_frequency()
{
gpio_put(outputs[0],1);
sleep_us(period);
gpio_put(outputs[0],0);
sleep_us(period);

}