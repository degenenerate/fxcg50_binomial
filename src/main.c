#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/ui_input_field.h"

int main()
{
    menu_state_t menu_state = MENU_STATE_SELECT;
    menu_data_t menu_data;
    menu_data.a_n = 1;
    menu_data.a_d = 1;
    menu_data.b_n = 1;
    menu_data.b_d = 1;
    menu_data.p_n = 1;
    menu_data.p_d = 1;
    menu_data.n = 0;

    draw_menu(menu_state, &menu_data);
    int key;
    while(1) {
        GetKey(&key);
        handle_menu(&menu_state, &menu_data, key);
    }
    
    /*
    input_field_t input_fields[9];
    int p = -7;
    input_fields[0] = (input_field_t){"a", &p};
    input_fields[1] = (input_field_t){"b", &p};
    input_fields[2] = (input_field_t){"c", &p};
    input_fields[3] = (input_field_t){"d", &p};
    input_fields[4] = (input_field_t){"e", &p};
    input_fields[5] = (input_field_t){"f", &p};
    input_fields[6] = (input_field_t){"g", &p};
    input_fields[7] = (input_field_t){"h", &p};
    input_fields[8] = (input_field_t){"i", &p};
    input_field_group_t input_field_group = {
        input_fields, 9,
        1, 6,
        2, 2,
        false,
    };
    int key;
    draw_input_field(&input_field_group);
    while(1) {
        GetKey(&key);
        Bdisp_AllClr_VRAM();
        handle_input_field_input(&input_field_group, &key);
        draw_input_field(&input_field_group);
    }
    */

    //Needed but never reached
    return 0;
}
