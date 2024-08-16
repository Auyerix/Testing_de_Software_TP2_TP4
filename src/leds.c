/**
 * @file leds.c
 * @author Gustavo Auyero
 * @brief Driver de manejo de leds
 * @version 0.1
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "leds.h"

#define LED_OFFSET   1       // define la numeración de los bits
#define FIRST_BIT    1       // define desde donde hace el corrimiento
#define ALL_LEDS_OFF 0x0000; // define el apagado de todos los leds
#define ALL_LEDS_ON  0xFFFF; // define el prendido de todos los leds

/**
 * @brief Variable privada para el almacenamiento del puerto
 *
 */
static uint16_t * puerto_virtual;

/* Funciones privadas*/
/**
 * @brief Generación de máscara con posiciones de leds
 *
 * @param led número de led 81-16)
 * @return uint16_t
 */
static uint16_t led_to_mask(int led) {
    return (FIRST_BIT << (led - LED_OFFSET));
}

/*Funciones públicas*/

void leds_init(uint16_t * puerto) {
    puerto_virtual = puerto;
    leds_turn_off_all();
}

void leds_turn_on(int led) {
    *puerto_virtual |= led_to_mask(led);
}

void leds_turn_off(int led) {
    *puerto_virtual &= ~led_to_mask(led);
}

bool leds_is_turned_on(int led) {

    return (*puerto_virtual & (FIRST_BIT << (led - LED_OFFSET)));
}

void leds_turn_on_all(void) {
    *puerto_virtual = ALL_LEDS_ON;
}

void leds_turn_off_all(void) {
    *puerto_virtual = ALL_LEDS_OFF;
}
