/**
 * @file test_leds.c
 * @author Gustavo Auyero
 * @brief Archivo de test de driver de leds
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/*
Requerimientos:

Al arrancar el sistema todos los leds tienen que estar apagados.

Despues de arrancar el sistema, con todos los leds apagados, voy a prender un led cualquiera.

Voy a prender un led y volver a apagarlo para ver si se apaga

Prender dos leds, apagar uno, y ver que solo se apaga el que corresponde y que el otro sigue prendido

Prender todos los leds juntos 

Prender y apagar todos los leds juntos 

Prender un led, voy a consultar el estado y tiene que figurar como prendido.
Voy a consultar el estado de un led apagado y tiene que figurar como apagado.

Revisar que los leds estan bien mapeados en la memoria
*/

#include "unity.h"
#include "leds.h"

static uint16_t puerto_virtual;             //global pero solo del test

//Funcion que se ejecuta antes de cada pruebal
void setUp(void){                            //Solo para recordar: hace un refactor para no tener que siempre  
                                             //leds_init y hace uint16_t puerto virtual global para test
    leds_init(&puerto_virtual);
}

//función que se ejecuta luego de cada prueba
void tearDown(void){

}

//Al arrancar el sistema todos los leds tienen que estar apagados.
void test_todos_los_leds_deben_arrancar_apagados(void){
    
    uint16_t puerto_virtual = 0xFFFF;       //acá no uso la global y lo hago mas explícito
                                            //la asignación es parte de la prueba
    leds_init(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

    //TEST_FAIL_MESSAGE("arrancamos..."); (solo para recordar como arrancamos)
}

//Despues de arrancar el sistema, con todos los leds apagados, voy a prender un led cualquiera.
void test_prender_un_solo_led(void){
    
    leds_turn_on(3);
    TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_virtual);

}

//Despues de arrancar el sistema, con todos los leds apagados, Voy a prender un led y volver a apagarlo para ver si se apaga
void test_prender_apagar_un_solo_led(void){
    
    leds_turn_on(3);
    leds_turn_off(3);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

}

//prender dos leds...
void test_prender_dos_leds_y_apagar_un_solo_led(void){
    
    leds_turn_on(3);
    leds_turn_on(7);
    leds_turn_off(3);
    TEST_ASSERT_EQUAL_HEX16(1 << 6, puerto_virtual);
}

//Consultar el estado de un led particular apagado
void test_consultar_estado_led_apagado(void){
    
    TEST_ASSERT_FALSE(leds_is_turned_on(3));

}

//Consultar el estado de un led particular prendido
void test_consultar_estado_led_prendido(void){
    
    leds_turn_on(3);
    TEST_ASSERT_TRUE(leds_is_turned_on(3));

}

// Prender todos los leds
void test_leds_todos_prendidos(void){
    
    leds_turn_on_all();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_virtual);

}

// Prender y apagar todos los leds
void test_leds_todos_prendidos_y_luego_apagados(void){
    
    leds_turn_on_all();
    leds_turn_off_all();
    TEST_ASSERT_EQUAL_HEX16(0, puerto_virtual);

}

// Encender un led fuera de rango y ver que no afecta el encendido de de otros leds
void test_encender_led_fuera_de_rango(void){
        
        leds_turn_on(17);
        TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// Apagar un led fuera del rango y ver que no afecto al resto, que estaban prendidos
void test_apagar_led_fuera_de_rango(void){
        
        leds_turn_on_all();
        leds_turn_off(17);
        TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_virtual);
}