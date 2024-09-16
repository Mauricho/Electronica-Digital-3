#ifdef __USE_CMSIS
#include "LPC17xx.h"  /**< CMSIS header for the LPC17xx microcontroller. */
#endif

#ifdef __USE_MCUEXPRESSO
#include <cr_section_macros.h> /**< Macros specific to the MCUXpresso toolchain. */
#endif

#include <stdint.h>
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_exti.h"

#define INPUT 0
#define OUTPUT 1
#define EDGE_RISING 1
#define MAX_CONTADOR 200
#define SWITCH_PINES ((uint8_t)0x0F)

volatile uint8_t contador = 0;
volatile uint8_t prioridad = 0;
volatile uint8_t numeros[10];


void configure_port(void);
void actualizar_numeros(void);

int main(void)
{
    SystemInit();
    configure_port();
    GPIO_IntCmd(PINSEL_PORT_0, PINSEL_PIN_4, EDGE_RISING);
    while (1)
    {
    }
    return 0;
}

void config_GPIO(void){
    PINSEL_CFG_Type pin_cfg;

    pin_cfg.Portnum = PINSEL_PORT_0;
    pin_cfg.Pinnum = PINSEL_PIN_0;
    pin_cfg.Funcnum = PINSEL_FUNC_0;
    pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE;
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, PINSEL_PIN_0, OUTPUT);

    pin_cfg.Pinnum = PINSEL_PIN_1;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, PINSEL_PIN_1, OUTPUT);

    pin_cfg.Pinnum = PINSEL_PIN_2;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, PINSEL_PIN_2, OUTPUT);

    pin_cfg.Pinnum = PINSEL_PIN_3;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, PINSEL_PIN_3, OUTPUT);

    pin_cfg.Pinnum = PINSEL_PIN_4;
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLDOWN;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, PINSEL_PIN_4, OUTPUT);
}

void EINT3_IRQHandler(void)
{
    // Rutina de servicio SENSOR 1
    if (GPIO_GetIntStatus(PINSEL_PORT_0, PINSEL_PIN_4, EDGE_RISING) == ENABLE)
    {
        // SE ACTIVA EL SENSOR 1, SE ACTIVA LA FLAG DE CERRANDO PUERTA, SE REINICIA EL CONTEO PARA ABRIR MODO SEGURO
        GPIO_ClearInt(PINSEL_PORT_0, PINSEL_PIN_4);
        contador++;
        prioridad++;
        NVIC_SetPriority(EINT3_IRQn, prioridad);
        if(prioridad+1==32){
            NVIC_DisableIRQ(EINT3_IRQn);
        }
        actualizar_numeros();
    }
}

void actualizar_numeros(void){
    for(uint8_t i=9; i>0; i--){
        numeros[i]=numeros[i-1];
    }
    numeros[0] = GPIO_ReadValue(PINSEL_PORT_0)&SWITCH_PINES;
}