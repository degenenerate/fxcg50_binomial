#include "../include/menu.h"

void reset_menu_data(menu_data_t *menu_data)
{
    memsetZero(menu_data, sizeof(menu_data_t));

    menu_data->page = MENU_PAGE_SELECT;

    menu_data->input_data.a_n = 1;
    menu_data->input_data.a_d = 1;
    menu_data->input_data.b_n = 1;
    menu_data->input_data.b_d = 1;
    menu_data->input_data.p_n = 1;
    menu_data->input_data.p_d = 1;

    menu_data->input_group.fields = menu_data->fields;
    menu_data->input_group.count = 0;
    menu_data->input_group.top = 2;
    menu_data->input_group.height = 6;
    menu_data->input_group.cursor = 0;
    menu_data->input_group.cursor_top = 0;
    menu_data->input_group.editing = false;
}

void handle_menu(menu_data_t *menu_data, int key)
{
    Bdisp_AllClr_VRAM();
    handle_menu_input(menu_data, key);
    draw_menu(menu_data);
}

void draw_menu(menu_data_t *menu_data)
{
    switch(menu_data->page) {
    case MENU_PAGE_SELECT:
        PrintXY(1, 1, "--Binomial Expansion", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        PrintXY(1, 5, "--Select Type", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 6, "--F1: Simple", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 7, "--F2: Complex", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        break;

    case MENU_PAGE_SIMPLE:
        PrintXY(1, 1, "--(ax+b)^p", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        PrintXY(1, 3, "--Select Type", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 4, "--F1: Ascending  ..n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 5, "--F2: Descending ..n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 6, "--F3: Full Expansion", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 7, "--F4: Expansion n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        break;

    case MENU_PAGE_COMPLEX:
        PrintXY(1, 1, "--a(1+bx)^p", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        PrintXY(1, 5, "--Select Type", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 6, "--F1: Until ..n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        PrintXY(1, 7, "--F2: Expansion n", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
        break;

    case MENU_PAGE_INPUT:
        if(menu_data->input_type <= SIMPLE_N) {
            PrintXY(1, 1, "--(ax+b)^p", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        } else {
            PrintXY(1, 1, "--a(1+bx)^p", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
        }

        draw_input_group(&menu_data->input_group);
        break;

    case MENU_PAGE_OUTPUT:
        DisplayMBString((unsigned char*)menu_data->output, menu_data->output_start, menu_data->output_cursor, 1, 8);
        break;
    }
}

void handle_menu_input(menu_data_t *menu_data, int key)
{
    switch(menu_data->page) {
    case MENU_PAGE_SELECT:
        switch(key) {
        case KEY_CTRL_F1:
            menu_data->page = MENU_PAGE_SIMPLE;
            break;

        case KEY_CTRL_F2:
            menu_data->page = MENU_PAGE_COMPLEX;
            break;
        }
        break;

    case MENU_PAGE_SIMPLE:
        switch(key) {
        case KEY_CTRL_EXIT:
            menu_data->page = MENU_STATE_SELECT;
            break;
        
        case KEY_CTRL_F1:
            menu_data->page = MENU_PAGE_INPUT;
            menu_data->input_type = SIMPLE_ASCENDING;
            menu_data->input_group.count = 6;
            menu_data->input_fields[0] = (input_field_t){"a_n", &menu_data->input_data.a_n};
            menu_data->input_fields[1] = (input_field_t){"a_d", &menu_data->input_data.a_d};
            menu_data->input_fields[2] = (input_field_t){"b_n", &menu_data->input_data.b_n};
            menu_data->input_fields[3] = (input_field_t){"b_d", &menu_data->input_data.b_d};
            menu_data->input_fields[4] = (input_field_t){"p",   &menu_data->input_data.p_n};
            menu_data->input_fields[5] = (input_field_t){"n",   &menu_data->input_data.n};
            break;

        case KEY_CTRL_F2:
            menu_data->page = MENU_PAGE_INPUT;
            menu_data->input_type = SIMPLE_DESCENDING;
            menu_data->input_group.count = 6;
            menu_data->input_fields[0] = (input_field_t){"a_n", &menu_data->input_data.a_n};
            menu_data->input_fields[1] = (input_field_t){"a_d", &menu_data->input_data.a_d};
            menu_data->input_fields[2] = (input_field_t){"b_n", &menu_data->input_data.b_n};
            menu_data->input_fields[3] = (input_field_t){"b_d", &menu_data->input_data.b_d};
            menu_data->input_fields[4] = (input_field_t){"p",   &menu_data->input_data.p_n};
            menu_data->input_fields[5] = (input_field_t){"n",   &menu_data->input_data.n};
            break;

        case KEY_CTRL_F3:
            menu_data->page = MENU_PAGE_INPUT;
            menu_data->input_type = SIMPLE_FULL;
            menu_data->input_group.count = 5;
            menu_data->input_fields[0] = (input_field_t){"a_n", &menu_data->input_data.a_n};
            menu_data->input_fields[1] = (input_field_t){"a_d", &menu_data->input_data.a_d};
            menu_data->input_fields[2] = (input_field_t){"b_n", &menu_data->input_data.b_n};
            menu_data->input_fields[3] = (input_field_t){"b_d", &menu_data->input_data.b_d};
            menu_data->input_fields[4] = (input_field_t){"p",   &menu_data->input_data.p_n};
            break;

        case KEY_CTRL_F4:
            menu_data->page = MENU_PAGE_INPUT;
            menu_data->input_type = SIMPLE_N;
            menu_data->input_group.count = 6;
            menu_data->input_fields[0] = (input_field_t){"a_n", &menu_data->input_data.a_n};
            menu_data->input_fields[1] = (input_field_t){"a_d", &menu_data->input_data.a_d};
            menu_data->input_fields[2] = (input_field_t){"b_n", &menu_data->input_data.b_n};
            menu_data->input_fields[3] = (input_field_t){"b_d", &menu_data->input_data.b_d};
            menu_data->input_fields[4] = (input_field_t){"p",   &menu_data->input_data.p_n};
            menu_data->input_fields[5] = (input_field_t){"n",   &menu_data->input_data.n};
            break;
        }
        break;

    case MENU_PAGE_COMPLEX:
        switch(key) {
        case KEY_CTRL_EXIT:
            menu_data->page = MENU_PAGE_SELECT;
            break;

        case KEY_CTRL_F1:
            menu_data->page = MENU_PAGE_INPUT;
            menu_data->input_type = COMPLEX_UNTIL;
            menu_data->input_group.count = 7;
            menu_data->input_fields[0] = (input_field_t){"a_n", &menu_data->input_data.a_n};
            menu_data->input_fields[1] = (input_field_t){"a_d", &menu_data->input_data.a_d};
            menu_data->input_fields[2] = (input_field_t){"b_n", &menu_data->input_data.b_n};
            menu_data->input_fields[3] = (input_field_t){"b_d", &menu_data->input_data.b_d};
            menu_data->input_fields[4] = (input_field_t){"p_n", &menu_data->input_data.p_n};
            menu_data->input_fields[5] = (input_field_t){"p_d", &menu_data->input_data.p_d};
            menu_data->input_fields[6] = (input_field_t){"n",   &menu_data->input_data.n};
            break;

        case KEY_CTRL_F2:
            menu_data->page = MENU_PAGE_INPUT;
            menu_data->input_type = COMPLEX_N;
            menu_data->input_group.count = 7;
            menu_data->input_fields[0] = (input_field_t){"a_n", &menu_data->input_data.a_n};
            menu_data->input_fields[1] = (input_field_t){"a_d", &menu_data->input_data.a_d};
            menu_data->input_fields[2] = (input_field_t){"b_n", &menu_data->input_data.b_n};
            menu_data->input_fields[3] = (input_field_t){"b_d", &menu_data->input_data.b_d};
            menu_data->input_fields[4] = (input_field_t){"p_n", &menu_data->input_data.p_n};
            menu_data->input_fields[5] = (input_field_t){"p_d", &menu_data->input_data.p_d};
            menu_data->input_fields[6] = (input_field_t){"n",   &menu_data->input_data.n};
            break;
        }

        break;

    case MENU_PAGE_INPUT:
        handle_input_field_input(&menu_data->input_group, &key);
        switch(key) {
        case KEY_CTRL_EXIT:
            if(menu_data->input_type <= SIMPLE_N) {
                menu_data->page = MENU_PAGE_SIMPLE;
            } else {
                menu_data->page = MENU_PAGE_COMPLEX;
            }
            break;

        case KEY_CTRL_EXE:
            // ban divide by zeroes, neg. powers on simple expansions, etc.
            menu_data->binomial_info.a = fraction_create(menu_data->input_data.a_n, menu_data->input_data.a_d);
            menu_data->binomial_info.b = fraction_create(menu_data->input_data.b_n, menu_data->input_data.b_d);
            menu_data->binomial_info.p = fraction_create(menu_data->input_data.p_n, menu_data->input_data.p_d);
            if(menu_data->input_type <= SIMPLE_N) {
                uint pow = menu_data->binomial_info.p.numer;

                if(menu_data->input_type == SIMPLE_ASCENDING) {
                    menu_data->binomial_info.n_start = 0;
                    menu_data->binomial_info.n_incr  = +1;
                    menu_data->binomial_info.n_count = menu_data->input_data.n;
                }
                else if(*menu_state == MENU_STATE_SIMPLE_DESCENDING) {
                    menu_data->binomial_info.n_start = pow + 1;
                    menu_data->binomial_info.n_incr  = -1;
                    menu_data->binomial_info.n_count = menu_data->input_data.n;
                }
                else if(*menu_state == MENU_STATE_SIMPLE_FULL) {
                    menu_data->binomial_info.n_start = 0;
                    menu_data->binomial_info.n_incr  = +1;
                    menu_data->binomial_info.n_count = pow + 1;
                }
                else {
                    menu_data->binomial_info.n_start = menu_data->input_data.n;
                    menu_data->binomial_info.n_incr  = 0;
                    menu_data->binomial_info.n_count = 1;
                }

                if(menu_data->binomial_info.a.denom == 0 
                || menu_data->binomial_info.b.denom == 0) {
                    DisplayMessageBox((unsigned char*)"Divide By Zero");
                    return;
                } else 
                if(menu_data->binomial_info.n_start < 0 
                || menu_data->binomial_info.n_start > pow 
                || menu_data->binomial_info.n_count <= 0 
                || menu_data->binomial_info.n_count > pow + 1) {
                    DisplayMessageBox((unsigned char*)"Invalid n");
                    return;
                } else if(menu_data->input_data.p_n < 0) {
                    DisplayMessageBox((unsigned char*)"Invalid power");
                    return;
                }

                fraction_t *coefs = binomial_expansion(&menu_data->binomial_info); 
                format_expansion(menu_data->output_buf, coefs, &menu_data->binomial_info);
                free(coefs);
            } else {
                if(menu_data->binomial_info.a.denom == 0 
                || menu_data->binomial_info.b.denom == 0 
                || menu_data->binomial_info.p.denom == 0) {
                    DisplayMessageBox((unsigned char*)"Divide By Zero");
                    return;
                } else if(menu_data->input_data.n < 0) {
                    DisplayMessageBox((unsigned char*)"Invalid n");
                    return;
                }

                if(*menu_state == MENU_STATE_COMPLEX_UNTIL) {
                    menu_data->binomial_info.n_start = 0;
                    menu_data->binomial_info.n_incr  = +1;
                    menu_data->binomial_info.n_count = menu_data->input_data.n;
                }
                else {
                    menu_data->binomial_info.n_start = menu_data->input_data.n;
                    menu_data->binomial_info.n_incr  = 0;
                    menu_data->binomial_info.n_count = 1;
                }
                fraction_t *coefs = binomial_expansion(&menu_data->binomial_info); 
                format_expansion(menu_data->output_buf, coefs, &menu_data->binomial_info);
                free(coefs);
            }

            menu_data->page = MENU_PAGE_OUTPUT;
            menu_data->output_start = 0;
            menu_data->output_cursor = 0;
            break;
        }
        break;

    case MENU_PAGE_OUTPUT:
        switch(key) {
        case KEY_CTRL_LEFT:
        case KEY_CTRL_RIGHT:
            EditMBStringCtrl(
                    (unsigned char*)menu_data->output_buf, 
                    MAX_BINOMIAL_OUTPUT, 
                    &menu_data->output_start, 
                    &menu_data->output_cursor, 
                    &key, 
                    1, 8);
            break;
        case KEY_CTRL_EXIT:
            Cursor_SetFlashOff();
            menu_data->page = MENU_PAGE_INPUT;
        case KEY_CTRL_EXE:
            Cursor_SetFlashOff();
            menu_data->page = MENU_STATE_SELECT;
            break;
        }
        break;
    }
}
