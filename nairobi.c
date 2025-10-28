#include "pico/stdlib.h"
#include <stdio.h>
#include <math.h>
#include "hardware/adc.h"

#define THERMISTOR_PIN 27
#define BUZZER_PIN 16
#define LED_PIN PICO_DEFAULT_LED_PIN
#define TEMP_THRESHOLD -3 //celsius 
//thermistor at GP 28, ADC 2
#define R_FIXED 10000.0 // resistor value
#define BETA 3950.0
#define T0 298.15 //25C in Kelvin
#define R0 10000.0

//convert thermistor ADC value to resistance
float adc_to_resistance(uint16_t adc_val) {
    float v = adc_val * 3.3 / 4095.0;
    return R_FIXED * (3.3 / v - 1.0); //thermistor first 
    //return R_FIXED * (v / (3.3 - v)); //resistor first 

}

//converts to kelvins -> celsius 
float resistance_to_celsius(float resis){
    float tempK = 1.0 / ( 1.0 / T0 + log(resis / R0)/BETA );
    return tempK - 273.15;
}

int main() {
    stdio_init_all();

    //initialize buzzer, pin, test if working
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, true);
    sleep_ms(2000);
    gpio_put(BUZZER_PIN, false);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, true);
    sleep_ms(2000);
    gpio_put(LED_PIN, false);

    adc_init();
    adc_gpio_init(THERMISTOR_PIN);
    adc_select_input(1);

    

    while (true) {
        uint16_t adc_val = adc_read();
        printf("ADC Value: %d\n", adc_val);
        float resistance = adc_to_resistance(adc_val);
        float temp = resistance_to_celsius(resistance);

        printf("Temperature: %.2f C\n", temp);

        if (temp >= TEMP_THRESHOLD) {
            gpio_put(BUZZER_PIN, true);
            gpio_put(LED_PIN, true);
            printf("above threshold\n"); 
        } else {
            gpio_put(BUZZER_PIN, false);
            gpio_put(LED_PIN, false);
        }

        sleep_ms(1000);
    }

    return 0;
}