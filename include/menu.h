#ifndef MENU_H
#define MENU_H

#include <string.h>
#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include "background.h"
#include "binomial.h"
#include "ui_input_field.h"

typedef enum {
    MENU_PAGE_SELECT,
    MENU_PAGE_SIMPLE,
    MENU_PAGE_COMPLEX,
    MENU_PAGE_INPUT,
    MENU_PAGE_OUTPUT,
    MENU_PAGE_HELP,
    MENU_PAGE_CREDITS,
} menu_page_t;

typedef enum {
    SIMPLE_ASCENDING,
    SIMPLE_DESCENDING,
    SIMPLE_FULL,
    SIMPLE_N,

    COMPLEX_UNTIL,
    COMPLEX_N,
} binomial_input_type_t;

typedef struct {
    int a_n; int a_d;
    int b_n; int b_d;
    int p_n; int p_d;
    int n;
} binomial_input_data_t;

typedef struct {
    menu_page_t page;
    binomial_input_type_t input_type;
    binomial_input_data_t input_data;
    input_field_t input_fields[7];
    input_group_t input_group;
    binomial_info_t binomial_info;
    char title_buf[128];
    char bound_buf[128];
    char output_buf[MAX_BINOMIAL_OUTPUT];
    int output_start;
    int output_cursor;
} menu_data_t;

void reset_menu_data(menu_data_t *menu_data);
void handle_menu(menu_data_t *menu_data, int key);
void draw_menu(menu_data_t *menu_data);
void handle_menu_input(menu_data_t *menu_data, int key);

#endif
