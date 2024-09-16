/*
 * @file main.c
 * @brief Timer0 and ADC example
 *
 * This program uses Timer0 to periodically trigger ADC conversions by configuring a "match" event.
 * Specifically, Timer0 is set up to generate an interrupt every 60 seconds. When the match event
 * occurs (on Match Channel 0), the ADC is triggered to sample the temperature from the analog
 * sensor connected to channel 7. This process, referred to as "enganchar" (linking), is accomplished
 * by setting the Timer0 Match Register (MR0) to trigger the ADC Start Command (ADC_START_ON_MAT01).
 * The ADC will then automatically start conversions at each match event, eliminating the need for
 * manual triggering within the main loop.
 *
 * The LEDs indicate the oven's temperature status: Green for < 40°C, Yellow for < 70°C, and Red
 * for temperatures above 70°C.
 *
 * Steps to "enganchar" the ADC with the Timer Match event:
 * 1. Configure Timer0 to generate a match interrupt every 60 seconds.
 * 2. Set the ADC to trigger conversions on Timer0 match events using ADC_START_ON_MAT01.
 * 3. The ADC conversion result is then processed in the ADC interrupt handler to update the LEDs.
 *
 * @note This code is compatible with CMSIS and MCUXpresso libraries.
 *
 * @author Mugni Juan Mauricio - Mauricho -
 * @date 2024-09-16
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#ifdef __USE_MCUEXPRESSO
#include <cr_section_macros.h> /* MCUXpresso-specific macros */
#endif

#include "lpc17xx_adc.h"    /* ADC library */
#include "lpc17xx_gpio.h"   /* GPIO library */
#include "lpc17xx_pinsel.h" /* Pin Configuration library */
#include "lpc17xx_timer.h"  /* Timer0 library */

/* Pin Definitions */
#define GREEN_LED  ((uint32_t)(1 << 20)) /* P0.20 connected to Green LED */
#define YELLOW_LED ((uint32_t)(1 << 21)) /* P0.21 connected to Yellow LED */
#define RED_LED    ((uint32_t)(1 << 22)) /* P0.22 connected to Red LED */
#define ADC_INPUT  ((uint32_t)(1 << 2))  /* P0.2 connected to ADC channel */

/* Temperature Thresholds */
#define GREEN_TMP  40 /**< Threshold for Green LED (< 40°C) */
#define YELLOW_TMP 70 /**< Threshold for Yellow LED (< 70°C) */

/* GPIO Direction Definitions */
#define INPUT  0 /**< GPIO pin direction for input */
#define OUTPUT 1 /**< GPIO pin direction for output */

/** Timer Configuration Values */
#define ADC_FREQ        100000 /* ADC sampling frequency: 100 kHz */
#define PRESCALER_VALUE 100    /* Timer prescaler value (100 µs resolution) */
#define MATCH_VALUE     60     /* Match value to trigger every 60 seconds */
#define MATCH_CHANNEL   0      /* Match on channel 0 */
#define SECOND          10000  /* miliSegundos */

/** ADC Configuration Values */
#define N_SAMPLE 7 /**< Number of samples to average */

/* Global variable to store the temperature */
static uint32_t temperature = 0;

/* Function declarations */
void configure_port(void);
void configure_adc(void);
void configure_timer_and_match(void);
void configure_priority(void);
void start_timer(void);
void turn_on_led(void);
void _exit(int);

/**
 * @brief Initialize the GPIO pins for the LEDs and input pin for ADC.
 */
void configure_port(void)
{
    PINSEL_CFG_Type pin_cfg_struct; /* Pin configuration structure */

    /* Configure P0.20, P0.21, and P0.22 as GPIO for LED outputs */
    pin_cfg_struct.Portnum = PINSEL_PORT_0;
    pin_cfg_struct.Funcnum = PINSEL_FUNC_0;           /* GPIO function */
    pin_cfg_struct.Pinmode = PINSEL_PINMODE_PULLUP;   /* Enable pull-up resistor */
    pin_cfg_struct.OpenDrain = PINSEL_PINMODE_NORMAL; /* Normal operation */

    /* Configure Green LED (P0.20) */
    pin_cfg_struct.Pinnum = PINSEL_PIN_20;
    PINSEL_ConfigPin(&pin_cfg_struct);

    /* Configure Yellow LED (P0.21) */
    pin_cfg_struct.Pinnum = PINSEL_PIN_21;
    PINSEL_ConfigPin(&pin_cfg_struct);

    /* Configure Red LED (P0.22) */
    pin_cfg_struct.Pinnum = PINSEL_PIN_22;
    PINSEL_ConfigPin(&pin_cfg_struct);

    /* Configure ADC input pin (P0.23) */
    pin_cfg_struct.Pinnum = PINSEL_PIN_23;
    pin_cfg_struct.Funcnum = PINSEL_FUNC_1; /* Set as ADC function */
    pin_cfg_struct.Pinmode = PINSEL_PINMODE_TRISTATE;
    PINSEL_ConfigPin(&pin_cfg_struct);

    /* Set LEDs as outputs */
    GPIO_SetDir(PINSEL_PORT_0, GREEN_LED | YELLOW_LED | RED_LED, OUTPUT);
}

/**
 * @brief Set the priority for Timer0 and ADC interrupts.
 */
void configure_priority(void)
{
    NVIC_SetPriority(TIMER0_IRQn, 0); /* Set Timer0 interrupt priority */
    NVIC_SetPriority(ADC_IRQn, 1);    /* Set ADC interrupt priority */
}

/**
 * @brief Configure the ADC to sample the temperature sensor at 100 kHz.
 * ADC will be triggered by the Timer Match.
 */
void configure_adc(void)
{
    ADC_Init(LPC_ADC, ADC_FREQ);                    /* Initialize ADC with 100 kHz frequency */
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_7, ENABLE); /* Enable ADC channel 7 (P0.23) */
    ADC_IntConfig(LPC_ADC, ADC_CHANNEL_7, ENABLE);  /* Enable interrupt for ADC channel 7 */

    /* Start ADC conversion on Timer Match (Match 0 Channel 1). This is the "enganchar" part. */
    ADC_StartCmd(LPC_ADC, ADC_START_ON_MAT01); /* Trigger ADC on Timer0 match event */

    NVIC_EnableIRQ(ADC_IRQn); /* Enable ADC interrupt */
}

/**
 * @brief Configure Timer0 to trigger an interrupt every 60 seconds.
 */
void configure_timer_and_match(void)
{
    TIM_TIMERCFG_Type timer_cfg_struct; /* Timer configuration structure */

    timer_cfg_struct.PrescaleOption = TIM_PRESCALE_USVAL; /* Use microsecond values */
    timer_cfg_struct.PrescaleValue = PRESCALER_VALUE;     /* Prescaler value (100 µs resolution) */

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timer_cfg_struct); /* Initialize Timer0 */

    TIM_MATCHCFG_Type match_cfg_struct; /* Match configuration structure */

    match_cfg_struct.MatchChannel = MATCH_CHANNEL;                  /* Use Match channel 0 */
    match_cfg_struct.IntOnMatch = ENABLE;                           /* Enable interrupt on match */
    match_cfg_struct.StopOnMatch = DISABLE;                         /* Continue counting after match */
    match_cfg_struct.ResetOnMatch = ENABLE;                         /* Reset timer on match */
    match_cfg_struct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;     /* No external action */
    match_cfg_struct.MatchValue = (uint32_t)(MATCH_VALUE * SECOND); /* 60 seconds match value */

    TIM_ConfigMatch(LPC_TIM0, &match_cfg_struct); /* Configure the match register */
}

/**
 * @brief Start Timer0 to begin counting.
 */
void start_timer(void)
{
    TIM_Cmd(LPC_TIM0, ENABLE);   /* Enable the timer */
    NVIC_EnableIRQ(TIMER0_IRQn); /* Enable the Timer0 interrupt */
}

// ----------------- Interrupt Handler Functions -----------------

/**
 * @brief Timer0 interrupt handler.
 * This triggers the ADC conversion when the match event occurs.
 */
void TIMER0_IRQHandler(void)
{
    if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)) /* Check if match 0 interrupt occurred */
    {
        TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); /* Clear interrupt flag */
        ADC_StartCmd(LPC_ADC, ADC_START_NOW);       /* Start ADC conversion immediately */
    }
}

/**
 * @brief ADC interrupt handler.
 * This averages N_SAMPLE ADC readings and updates the LED state.
 */
void ADC_IRQHandler(void)
{
    NVIC_DisableIRQ(ADC_IRQn); /* Disable ADC interrupt to prevent conflicts */

    temperature = 0; /* Reset temperature value */

    for (uint32_t i = 0; i < N_SAMPLE; ++i) /* Average N_SAMPLE ADC readings */
    {
        while (!(ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_7, ADC_DATA_DONE)))
            ;                                                      /* Wait for the conversion to finish */
        temperature += ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_7); /* Accumulate ADC readings */
    }

    temperature /= N_SAMPLE;  /* Calculate the average temperature */
    turn_on_led();            /* Update the LED status based on the temperature */
    NVIC_EnableIRQ(ADC_IRQn); /* Re-enable ADC interrupt */
}

/**
 * @brief Turn on the appropriate LED based on the temperature value.
 * Green: < 40°C, Yellow: < 70°C, Red: > 70°C.
 */
void turn_on_led(void)
{
    if (temperature <= GREEN_TMP)
    {
        GPIO_SetValue(PINSEL_PORT_0, GREEN_LED);              /* Turn on Green LED */
        GPIO_ClearValue(PINSEL_PORT_0, RED_LED | YELLOW_LED); /* Turn off others */
    }
    else if (temperature <= YELLOW_TMP)
    {
        GPIO_SetValue(PINSEL_PORT_0, YELLOW_LED);            /* Turn on Yellow LED */
        GPIO_ClearValue(PINSEL_PORT_0, RED_LED | GREEN_LED); /* Turn off others */
    }
    else
    {
        GPIO_SetValue(PINSEL_PORT_0, RED_LED);                  /* Turn on Red LED */
        GPIO_ClearValue(PINSEL_PORT_0, YELLOW_LED | GREEN_LED); /* Turn off others */
    }
}

/**
 * @brief Main function.
 */
int main(void)
{
    SystemInit();                /* Initialize the system clock (default: 100 MHz) */
    configure_port();            /* Configure GPIO ports for LEDs and ADC input */
    configure_priority();        /* Set the priority*/
    configure_adc();             /* Configure the ADC for temperature sensing */
    configure_timer_and_match(); /* Configure Timer0 for 60s interrupts */
    start_timer();               /* Start Timer0 */

    while (1)
        ; /* Wait for interrupts */

    return 0; /* Program should never reach this point */
}

/**
 * I am put this function for a warning.
 */
void _exit(int status) {
    while (1); // Bucle infinito
}