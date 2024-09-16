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

#define INPUT               0
#define OUTPUT              1

#define SYSTICK_TIME  1 // 1 miliseg
#define COUNTER_MAX 1000 // 1 seg

#define A_PIN       ((uint32_t)(1<<0))
#define B_PIN       ((uint32_t)(1<<1))
#define C_PIN       ((uint32_t)(1<<2))
#define D_PIN       ((uint32_t)(1<<3))
#define E_PIN       ((uint32_t)(1<<4))
#define F_PIN       ((uint32_t)(1<<5))
#define G_PIN       ((uint32_t)(1<<6))

#define PUERTOS_PIN         ((uint32_t)0x7F)
#define CERO_DISPLAY        ((uint32_t)0x3F)
#define UNO_DISPLAY         ((uint32_t)0x06)
#define DOS_DISPLAY         ((uint32_t)0x5B)
#define TRES_DISPLAY        ((uint32_t)0x4F)
#define CUATRO_DISPLAY      ((uint32_t)0x66)
#define CINCO_DISPLAY       ((uint32_t)0x6D)
#define SEIS_DISPLAY        ((uint32_t)0x7D)
#define SIETE_DISPLAY       ((uint32_t)0x07)
#define OCHO_DISPLAY        ((uint32_t)0x7F)
#define NUEVE_DISPLAY       ((uint32_t)0x67)

#define LENTO       ((uint8_t) 0)
#define RAPIDO      ((uint8_t) 1)
#define STOP        ((uint8_t) 1)
#define RUN         ((uint8_t) 0)

volatile uint32_t systick_counter   = 0;
volatile uint8_t number            = 0;
volatile uint8_t flag_vel           = 0; // 0 es lento; 1 es rápido
volatile uint8_t flag_stop               = 0; // 1 stop, 0 run

void config_port(void);
void config_Systick();
void config_EINT(void);
void cargar_number(uint32_t number);

int main(void)
{
    SystemInit();
    config_port();
    config_Systick();
    config_EINT();
    
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);
    while (1)
    {
        // 
    }

    return 0;
}

void config_port(void){
    PINSEL_CFG_Type pin_cfg;

    pin_cfg.Portnum     = PINSEL_PORT_0;
    pin_cfg.Pinnum      = PINSEL_PIN_0;
    pin_cfg.Funcnum     = PINSEL_FUNC_0;
    pin_cfg.Pinmode     = PINSEL_PINMODE_PULLUP; // PINSEL_PINMODE_PULLDOWN
    pin_cfg.OpenDrain   = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, A_PIN, OUTPUT);
    
    pin_cfg.Pinnum = PINSEL_PIN_1;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, B_PIN, OUTPUT);

    pin_cfg.Pinnum = PINSEL_PIN_2;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, C_PIN, OUTPUT);

    pin_cfg.Pinnum = PINSEL_PIN_3;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, D_PIN, OUTPUT);

    pin_cfg.Pinnum = PINSEL_PIN_4;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, E_PIN, OUTPUT);

    pin_cfg.Pinnum = PINSEL_PIN_5;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, F_PIN, OUTPUT);

    pin_cfg.Pinnum = PINSEL_PIN_6;
    PINSEL_ConfigPin(&pin_cfg);
    GPIO_SetDir(PINSEL_PORT_0, G_PIN, OUTPUT);

    pin_cfg.Portnum = PINSEL_PORT_2;
    pin_cfg.Pinnum = PINSEL_PIN_10;
    pin_cfg.Funcnum = PINSEL_FUNC_1;
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_11;
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_12;
    PINSEL_ConfigPin(&pin_cfg);
}

void config_Systick(){
    SYSTICK_InternalInit(SYSTICK_TIME);
}

void config_EINT(){
    EXTI_InitTypeDef ext_int;
    ext_int.EXTI_Line = EXTI_EINT0;
    ext_int.EXTI_Mode = EXTI_MODE_LEVEL_SENSITIVE; 
    ext_int.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE; 
    EXTI_Config(&ext_int);

    ext_int.EXTI_Line = EXTI_EINT1;
    ext_int.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE; 
    ext_int.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE; 
    EXTI_Config(&ext_int);

    ext_int.EXTI_Line = EXTI_EINT2;
    EXTI_Config(&ext_int);
}

void SysTick_Handler(void)
{
    SYSTICK_ClearCounterFlag();
    if(flag_stop==RUN){
        if(flag_vel == LENTO){
            systick_counter++;
            if(systick_counter>=COUNTER_MAX){
            systick_counter=0;
            number++;
                if(number>9){
                    number = 0;
                }
            }
        } else {
            number++;
            if(number>9){
                number = 0;
            }
        }
        cargar_number(number);
    }
}

void EINT0_IRQHandler(void) {
    EXTI_ClearEXTIFlag(EXTI_EINT0);
    number=0;
}

void EINT1_IRQHandler(void) {
    EXTI_ClearEXTIFlag(EXTI_EINT1);
    if(flag_stop==STOP){
        flag_stop = RUN;
    } else {
        flag_stop = STOP;
    }
}

void EINT2_IRQHandler(void) {
    EXTI_ClearEXTIFlag(EXTI_EINT2);
    if(flag_vel==LENTO){
        flag_vel = RAPIDO;
    } else {
        flag_vel = LENTO;
    }
}

void cargar_number(uint32_t number){
    switch (number)
        {
        case 0:
            GPIO_SetValue(PUERTOS_PIN, A_PIN);
            break;

        case 1:
            GPIO_SetValue(PUERTOS_PIN, B_PIN);
            break;

        case 2:
            GPIO_SetValue(PUERTOS_PIN, C_PIN);
            break;

        case 3:
            GPIO_SetValue(PUERTOS_PIN, D_PIN);
            break;

        case 4:
            GPIO_SetValue(PUERTOS_PIN, E_PIN);
            break;

        case 5:
            GPIO_SetValue(PUERTOS_PIN, F_PIN);
            break;

        case 6:
            GPIO_SetValue(PUERTOS_PIN, G_PIN);
            break;
        
        default:
            GPIO_SetValue(PUERTOS_PIN, 0x00);
            break;
        }
}