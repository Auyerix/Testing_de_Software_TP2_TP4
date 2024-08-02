/**
 * @file leds.h
 * @author Gustavo Auyero
 * @brief Declaración de funciones para el manejo de leds
 * @version 0.1
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Inicia la configuración del puerto y apaga todos los leds
 *
 * @param puerto dirección del puerto
 */
void leds_init(uint16_t * puerto);

/**
 * @brief Prende el led pasado como parámetro
 *
 * @param led número que se desea prender (1-16)
 */
void leds_turn_on(int led);

/**
 * @brief apaga el led pasado como parámetro
 *
 * @param led número que se desea apagar (1-16)
 */
void leds_turn_off(int led);

/**
 * @brief Consulta si el led pasado como parámetro está prendido
 *
 * @param led número que se desea consultar(1-16)
 * @return true
 * @return false
 */
bool leds_is_turned_on(int led);

/**
 * @brief Prende todos los leds
 *
 */
void leds_turn_on_all(void);

/**
 * @brief Apaga todos los leds
 *
 */
void leds_turn_off_all(void);

#endif