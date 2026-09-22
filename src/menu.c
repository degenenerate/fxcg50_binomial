#include "../include/menu.h"

void reset_menu_data(menu_data_t *menu_data)
{
    if(sizeof(menu_data_t) == 0) return;
    memsetZero(menu_data, sizeof(menu_data_t));

    menu_data->input_field.input_fields = menu_data->fields;
    menu_data->input_field.count = 0;
    menu_data->input_field.top = 2;
    menu_data->input_field.height = 6;
    menu_data->input_field.cursor = 0;
    menu_data->input_field.cursor_top = 0;
    menu_data->input_field.editing = false;
}

void handle_menu(menu_state_t *menu_state, menu_data_t *menu_data, int key)
{
    Bdisp_AllClr_VRAM();
    handle_menu_input(menu_state, menu_data, key);
    draw_menu(*menu_state, menu_data);
}

void draw_menu(menu_state_t menu_state, menu_data_t *menu_data)
{
    switch(menu_state) {
    case MENU_STATE_SELECT:
        PrintXY(1, 1, "--Binomial Expansion", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        PrintXY(1, 5, "--Select Type", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 6, "--F1: Simple", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 7, "--F2: Complex", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        break;

    case MENU_STATE_SIMPLE_INPUT:
        PrintXY(1, 1, "--(ax+b)^p", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        PrintXY(1, 3, "--Select Type", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 4, "--F1: Ascending  ..n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 5, "--F2: Descending ..n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 6, "--F3: Full Expansion", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 7, "--F4: Expansion n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        break;

    case MENU_STATE_COMPLEX_INPUT:
        PrintXY(1, 1, "--a(1+bx)^p", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        PrintXY(1, 5, "--Select Type", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 6, "--F1: Until ..n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 7, "--F2: Expansion n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        break;

    case MENU_STATE_SIMPLE_ASCENDING:
    case MENU_STATE_SIMPLE_DESCENDING:
    case MENU_STATE_SIMPLE_FULL:
    case MENU_STATE_SIMPLE_N:
    case MENU_STATE_COMPLEX_UNTIL:
    case MENU_STATE_COMPLEX_N:
        if(menu_state <= MENU_STATE_SIMPLE_N) {
            PrintXY(1, 1, "--(ax+b)^p", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        } else {
            PrintXY(1, 1, "--a(1+bx)^p", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        }

        draw_input_field(&menu_data->input_field);
        break;
    case MENU_STATE_OUTPUT:
        DisplayMBString((unsigned char*)menu_data->output, menu_data->output_start, menu_data->output_cursor, 1, 8);
        //PrintXY(1, 8, menu_data->output, TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        break;
    }
}

void handle_menu_input(menu_state_t *menu_state, menu_data_t *menu_data, int key)
{
    switch(*menu_state) {
    case MENU_STATE_SELECT:
        switch(key) {
        case KEY_CTRL_F1:
            *menu_state = MENU_STATE_SIMPLE_INPUT;
            reset_menu_data(menu_data);
            break;

        case KEY_CTRL_F2:
            *menu_state = MENU_STATE_COMPLEX_INPUT;
            reset_menu_data(menu_data);
            break;
        }

        break;

    case MENU_STATE_SIMPLE_INPUT:
        switch(key) {
        case KEY_CTRL_EXIT:
            *menu_state = MENU_STATE_SELECT;
            break;
        
        case KEY_CTRL_F1:
            *menu_state = MENU_STATE_SIMPLE_ASCENDING;
            menu_data->input_field.count = 6;
            menu_data->fields[0] = (input_field_t){"a_n", &menu_data->a_n};
            menu_data->fields[1] = (input_field_t){"a_d", &menu_data->a_d};
            menu_data->fields[2] = (input_field_t){"b_n", &menu_data->b_n};
            menu_data->fields[3] = (input_field_t){"b_d", &menu_data->b_d};
            menu_data->fields[4] = (input_field_t){"p", &menu_data->p_n};
            menu_data->fields[5] = (input_field_t){"n", &menu_data->n};
            break;

        case KEY_CTRL_F2:
            *menu_state = MENU_STATE_SIMPLE_DESCENDING;
            menu_data->input_field.count = 6;
            menu_data->fields[0] = (input_field_t){"a_n", &menu_data->a_n};
            menu_data->fields[1] = (input_field_t){"a_d", &menu_data->a_d};
            menu_data->fields[2] = (input_field_t){"b_n", &menu_data->b_n};
            menu_data->fields[3] = (input_field_t){"b_d", &menu_data->b_d};
            menu_data->fields[4] = (input_field_t){"p", &menu_data->p_n};
            menu_data->fields[5] = (input_field_t){"n", &menu_data->n};
            break;

        case KEY_CTRL_F3:
            *menu_state = MENU_STATE_SIMPLE_FULL;
            menu_data->input_field.count = 5;
            menu_data->fields[0] = (input_field_t){"a_n", &menu_data->a_n};
            menu_data->fields[1] = (input_field_t){"a_d", &menu_data->a_d};
            menu_data->fields[2] = (input_field_t){"b_n", &menu_data->b_n};
            menu_data->fields[3] = (input_field_t){"b_d", &menu_data->b_d};
            menu_data->fields[4] = (input_field_t){"p", &menu_data->p_n};
            break;

        case KEY_CTRL_F4:
            *menu_state = MENU_STATE_SIMPLE_N;
            menu_data->input_field.count = 6;
            menu_data->fields[0] = (input_field_t){"a_n", &menu_data->a_n};
            menu_data->fields[1] = (input_field_t){"a_d", &menu_data->a_d};
            menu_data->fields[2] = (input_field_t){"b_n", &menu_data->b_n};
            menu_data->fields[3] = (input_field_t){"b_d", &menu_data->b_d};
            menu_data->fields[4] = (input_field_t){"p", &menu_data->p_n};
            menu_data->fields[5] = (input_field_t){"n", &menu_data->n};
            break;
        }

        break;

    case MENU_STATE_COMPLEX_INPUT:
        switch(key) {
        case KEY_CTRL_EXIT:
            *menu_state = MENU_STATE_SELECT;
            break;

        case KEY_CTRL_F1:
            *menu_state = MENU_STATE_COMPLEX_UNTIL;
            menu_data->input_field.count = 7;
            menu_data->fields[0] = (input_field_t){"a_n", &menu_data->a_n};
            menu_data->fields[1] = (input_field_t){"a_d", &menu_data->a_d};
            menu_data->fields[2] = (input_field_t){"b_n", &menu_data->b_n};
            menu_data->fields[3] = (input_field_t){"b_d", &menu_data->b_d};
            menu_data->fields[4] = (input_field_t){"p_n", &menu_data->p_n};
            menu_data->fields[5] = (input_field_t){"p_d", &menu_data->p_d};
            menu_data->fields[6] = (input_field_t){"n", &menu_data->n};
            break;

        case KEY_CTRL_F2:
            *menu_state = MENU_STATE_COMPLEX_N;
            menu_data->input_field.count = 7;
            menu_data->fields[0] = (input_field_t){"a_n", &menu_data->a_n};
            menu_data->fields[1] = (input_field_t){"a_d", &menu_data->a_d};
            menu_data->fields[2] = (input_field_t){"b_n", &menu_data->b_n};
            menu_data->fields[3] = (input_field_t){"b_d", &menu_data->b_d};
            menu_data->fields[4] = (input_field_t){"p_n", &menu_data->p_n};
            menu_data->fields[5] = (input_field_t){"p_d", &menu_data->p_d};
            menu_data->fields[6] = (input_field_t){"n", &menu_data->n};
            break;
        }

        break;

    case MENU_STATE_SIMPLE_ASCENDING:
    case MENU_STATE_SIMPLE_DESCENDING:
    case MENU_STATE_SIMPLE_FULL:
    case MENU_STATE_SIMPLE_N:
    case MENU_STATE_COMPLEX_UNTIL:
    case MENU_STATE_COMPLEX_N:
        handle_input_field_input(&menu_data->input_field, &key);
        switch(key) {
        case KEY_CTRL_EXIT:
            if(*menu_state <= MENU_STATE_SIMPLE_N) {
                *menu_state = MENU_STATE_SIMPLE_INPUT;
            } else {
                *menu_state = MENU_STATE_COMPLEX_INPUT;
            }
            break;

        case KEY_CTRL_EXE: {
            // ban divide by zeroes, neg. powers on simple expansions, etc.
            fraction_t a = fraction_create(menu_data->a_n, menu_data->a_d);
            fraction_t b = fraction_create(menu_data->b_n, menu_data->b_d);
            fraction_t p = fraction_create(menu_data->p_n, menu_data->p_d);
            int n_start; int n_incr; int n_count;
            if(*menu_state <= MENU_STATE_SIMPLE_N) {
                uint pow = p.numer;

                if(*menu_state == MENU_STATE_SIMPLE_ASCENDING) {
                    n_start = 0;
                    n_incr = +1;
                    n_count = menu_data->n;
                }
                else if(*menu_state == MENU_STATE_SIMPLE_DESCENDING) {
                    n_start = pow + 1;
                    n_incr = -1;
                    n_count = menu_data->n;
                }
                else if(*menu_state == MENU_STATE_SIMPLE_FULL) {
                    n_start = 0;
                    n_incr = +1;
                    n_count = pow + 1;
                }
                else {
                    n_start = menu_data->n;
                    n_incr = 0;
                    n_count = 1;
                }

                if(a.denom == 0 || b.denom == 0) {
                    DisplayMessageBox((unsigned char*)"Divide By Zero");
                    return;
                } else if(0 > n_start || n_start > pow || n_count <= 0 || n_count > pow + 1) {
                    DisplayMessageBox((unsigned char*)"Invalid n");
                    return;
                } else if(menu_data->p_n < 0) {
                    DisplayMessageBox((unsigned char*)"Invalid power");
                    return;
                }

                fraction_t *coefs = binomial_expansion(BINOMIAL_SIMPLE, a, b, p, n_start, n_incr, n_count); 
                format_simple_expansion(coefs, menu_data->output, pow, n_start, n_incr, n_count);
                free(coefs);
            } else {
                if(a.denom == 0 || b.denom == 0 || p.denom == 0) {
                    DisplayMessageBox((unsigned char*)"Divide By Zero");
                    return;
                } else if(menu_data->n < 0) {
                    DisplayMessageBox((unsigned char*)"Invalid n");
                    return;
                }

                if(*menu_state == MENU_STATE_COMPLEX_UNTIL) {
                    n_start = 0;
                    n_incr = +1;
                    n_count = menu_data->n;
                }
                else {
                    n_start = menu_data->n;
                    n_incr = 0;
                    n_count = 1;
                }
                fraction_t *coefs = binomial_expansion(BINOMIAL_COMPLEX, a, b, p, n_start, n_incr, n_count); 
                format_complex_expansion(coefs, menu_data->output, n_start, n_incr, n_count);
                free(coefs);
            }
            *menu_state = MENU_STATE_OUTPUT;
            menu_data->output_start = 0;
            menu_data->output_cursor = 0;
            }
            break;
        }
        break;

    case MENU_STATE_OUTPUT:
        switch(key) {
        case KEY_CTRL_LEFT:
        case KEY_CTRL_RIGHT:
            EditMBStringCtrl((unsigned char*)menu_data->output, 512, &menu_data->output_start, &menu_data->output_cursor, &key, 1, 8);
            break;
        case KEY_CTRL_EXIT:
        case KEY_CTRL_EXE:
            Cursor_SetFlashOff();
            *menu_state = MENU_STATE_SELECT;
            break;
        }
        break;

    }
}
