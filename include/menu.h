#ifndef MENU_H
#define MENU_H

#include <string.h>
#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include "binomial.h"
#include "ui_input_field.h"

typedef enum {
    MENU_STATE_SELECT,

    MENU_STATE_SIMPLE_INPUT,
    MENU_STATE_SIMPLE_ASCENDING,
    MENU_STATE_SIMPLE_DESCENDING,
    MENU_STATE_SIMPLE_FULL,
    MENU_STATE_SIMPLE_N,

    MENU_STATE_COMPLEX_INPUT,
    MENU_STATE_COMPLEX_UNTIL,
    MENU_STATE_COMPLEX_N,

    MENU_STATE_OUTPUT,
} menu_state_t;

typedef struct {
    input_field_group_t input_field;
    input_field_t fields[7];
    int a_n; int a_d;
    int b_n; int b_d;
    int p_n; int p_d;
    int n;
    char output[512];
    int output_start;
    int output_cursor;
} menu_data_t;

void reset_menu_data(menu_data_t *menu_data);
void handle_menu(menu_state_t *menu_state, menu_data_t *menu_data, int key);
void draw_menu(menu_state_t menu_state, menu_data_t *menu_data);
void handle_menu_input(menu_state_t *menu_state, menu_data_t *menu_data, int key);

#endif
