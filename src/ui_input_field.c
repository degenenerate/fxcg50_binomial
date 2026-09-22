#include "../include/ui_input_field.h"

void draw_input_field(input_field_group_t *field_group)
{
    const int colonX = 5;
    const int buf_len = 64;
    char print_buf[buf_len];
    print_buf[0] == '-';
    print_buf[1] == '-';
    char *print_start = print_buf + 2;
    for(int i=0; i<field_group->height; ++i) {
        /*
         * We're looping from the group's top to bottom,
         * figuring out the offset and finding the index
        */
        int y = field_group->top + i;
        int index = field_group->cursor_top + i;

        if(index >= field_group->count) break;

        bool on_cursor = (index == field_group->cursor);
        input_field_t field = field_group->input_fields[index];

        int text_mode;
        int text_color = TEXT_COLOR_BLACK;
        if(!on_cursor) {
            text_mode = TEXT_MODE_NORMAL;
        } else {
            text_mode = TEXT_MODE_INVERT;
        }

        //First empty the string, then copy text, data.
        //sprintf includes null terminator
        memset(print_start, ' ', sizeof(char)*(buf_len - 2));
        memcpy(print_start, field.text, sizeof(char)*strlen(field.text));
        sprintf(print_start + colonX, ":%i", *field.data);
        PrintXY(1, y, print_buf, text_mode, text_color);
    }

    struct scrollbar scrlbar = (struct scrollbar){
        0,
        field_group->count,
        field_group->height,
        field_group->cursor_top,
        0,
        378,
        24*(field_group->top - 1),
        24*(field_group->height),
        6,
    };
    Scrollbar(&scrlbar);
}

void handle_input_field_input(input_field_group_t *field_group, int *key_ptr)
{
    //Modifies key to be 0 if used
    int key = *key_ptr;
    bool numeric_input(int key)
    {
        if(key >= KEY_CHAR_0 && key <= KEY_CHAR_9)
            return true;
        if(key == KEY_CHAR_MINUS
        || key == KEY_CHAR_PLUS
        )   return true;

        return false;
    }
    int atoi_int(char *buf)
    {
        if(buf[0] == '\0') return 0;
        //if(buf[0] == '-')
        if((unsigned char)buf[0] == 153) return -atoi(buf+1);
        return atoi(buf);
    }

    if(!field_group->editing) {
        if(key == KEY_CTRL_UP) {
            scroll_input_field(field_group, -1);
        }
        else if(key == KEY_CTRL_DOWN) {
            scroll_input_field(field_group, +1);
        }
        else if(numeric_input(key)) {
            field_group->editing = true;
            field_group->edit_start = 0;
            field_group->edit_cursor = 0;
            field_group->edit_buf[0] = '\0';
            field_group->edit_cursor = EditMBStringChar(
                    (unsigned char*)field_group->edit_buf, 
                    INPUT_FIELD_EDIT_BUF_LEN, 
                    field_group->edit_cursor, 
                    key);
            DisplayMBString((unsigned char*)field_group->edit_buf, 
                    field_group->edit_start, 
                    field_group->edit_cursor, 
                    1, 8);
        }
    } else {
        if(key == KEY_CTRL_EXIT) {
            *key_ptr = KEY_PRGM_NONE;
            field_group->editing = false;
            Cursor_SetFlashOff();
        }
        else if(key == KEY_CTRL_EXE) {
            *key_ptr = KEY_PRGM_NONE;
            field_group->editing = false;
            Cursor_SetFlashOff();
            *(field_group->input_fields[field_group->cursor].data) = atoi_int(field_group->edit_buf);
        }
        else if(key && key < 30000) {
            if(!numeric_input(key)) {
                return;
            }

            field_group->edit_cursor = EditMBStringChar(
                    (unsigned char*)field_group->edit_buf, 
                    INPUT_FIELD_EDIT_BUF_LEN, 
                    field_group->edit_cursor, 
                    key);
            DisplayMBString((unsigned char*)field_group->edit_buf, 
                    field_group->edit_start, 
                    field_group->edit_cursor, 
                    1, 8);
        } else {
            EditMBStringCtrl(
                    (unsigned char*)field_group->edit_buf, 
                    INPUT_FIELD_EDIT_BUF_LEN, 
                    &field_group->edit_start, 
                    &field_group->edit_cursor, 
                    key_ptr, 
                    1, 8);
            DisplayMBString((unsigned char*)field_group->edit_buf, 
                    field_group->edit_start, 
                    field_group->edit_cursor, 
                    1, 8);
        }
    }
}

void scroll_input_field(input_field_group_t *field_group, int offset)
{
    int new_cursor = field_group->cursor + offset;
    if(new_cursor < 0 || new_cursor >= field_group->count) return;

    field_group->cursor = new_cursor;
    if(new_cursor < field_group->cursor_top) {
        field_group->cursor_top = new_cursor;
    }
    if(new_cursor >= field_group->cursor_top+field_group->height) {
        field_group->cursor_top += offset;
    }
}
