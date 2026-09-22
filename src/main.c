#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/ui_input_field.h"

int main()
{
    menu_data_t menu_data;
    reset_menu_data(&menu_data);
    draw_menu(&menu_data);
    int key;
    while(1) {
        GetKey(&key);
        handle_menu(&menu_data, key);
    }

    //Needed but never reached
    return 0;
}
