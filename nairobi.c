#include <stdio.h>
#include "pico/stdlib.h"


int main()
{
    /*stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }*/
   gpio_init(PICO_DEFAULT_LED_PIN);
   gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

   while(true) {
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(500);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    sleep_ms(500);  
   }
}
