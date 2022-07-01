#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

/* Output PWM signals on pin 25 */
#define PICO_DEFAULT_LED_PIN0   0
#define PICO_DEFAULT_LED_PIN1   1

/* Struct para los datos de temperatura */
typedef struct {
  float lm35;
  float pote;
} temperature_data_t;

/* Queue para comunicar los dos nucleos */
queue_t queue;

/* Main para el core 1 */
void core1_main() {

    gpio_set_function(PICO_DEFAULT_LED_PIN0, GPIO_FUNC_PWM);
    gpio_set_function(PICO_DEFAULT_LED_PIN1, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN0);

    /* Default config:
     * - top = 0xffff
     * - clkdiv = 1 
     */
    pwm_config config = pwm_get_default_config();
    /* Set clkdiv to 4 */
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice_num, &config, true);

    while(1) {
        /* Variable para recuperar el dato de la queue */
        temperature_data_t data;
        /* Espera a que esten los datos para recibir */
        queue_remove_blocking(&queue, &data);
        float cuenta =(temp0-temp1); /* cuenta de las datas */
        if (cuenta>10){                     /*todo para no sorbepasar el 10*/
        cuenta=10
        }
        else  if (cuenta<10){
        cuenta=-10
        }
        uint16_t rdt= ((cuenta*65535)/10)  /* reglas de tres */
        if (cuenta>0){
            pwm_set_gpio_level(PICO_DEFAULT_LED_PIN0, rdt); /* prende y apaga uno u otro*/
            pwm_set_gpio_level(PICO_DEFAULT_LED_PIN1, 0);
        }
        else{
            pwm_set_gpio_level(PICO_DEFAULT_LED_PIN0, 0);
            pwm_set_gpio_level(PICO_DEFAULT_LED_PIN1, rdt);
        }
    }
}

/* Main para el core 0 */
int main() {
    
    stdio_init_all();
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    
    /* Inicializa la cola para enviar un unico dato */
    queue_init(&queue, sizeof(temperature_data_t), 1);
    /* Inicializa el core 1 */
    multicore_launch_core1(core1_main);
    const float conversion_factor = 3.3f / (1 << 12);
    while(1) {
        /* Variable para enviar los datos */
        temperature_data_t data;
        adc_select_input (0); 
        uint16_t result0 = adc_read(); 
        adc_select_input (1);
        uint16_t result1 = adc_read();
        float volt0= result0 * conversion_factor;
        float volt1= result1 * conversion_factor;
        float temp0= volt0 * 35 / 3.3; 
        float temp1= volt0 / 0.01; 

        data.lm35 = temp0;
        data.pote = temp1;

        /* Cuando los datos estan listos, enviar por la queue */
        queue_add_blocking(&queue, &data);
        sleep_ms(500);
    }
    
    
}
