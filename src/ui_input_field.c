#include "../include/ui_input_field.h"

void draw_input_group(input_group_t *group)
{
    const int colonX = 5;
    const int buf_len = 64;
    char print_buf[buf_len];
    print_buf[0] = '-';
    print_buf[1] = '-';
    char *print_start = print_buf + 2;
    for(int i=0; i<group->height; i++) {
        /*
         * We're looping from the group's top to bottom,
         * figuring out the offset and finding the index
        */
        int y = group->top + i;
        int index = group->cursor_top + i;

        if(index >= group->count) break;

        bool on_cursor = (index == group->cursor);
        input_field_t field = group->fields[index];

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
        group->count,
        group->height,
        group->cursor_top,
        0,
        378,
        24*(group->top - 1),
        24*(group->height),
        6,
    };
    Scrollbar(&scrlbar);
}

void handle_input_group_input(input_group_t *group, int *key_ptr)
{
    //key_ptr set to 0 if used during editing
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

    if(!group->editing) {
        if(key == KEY_CTRL_UP) {
            scroll_input_group(group, -1);
        }
        else if(key == KEY_CTRL_DOWN) {
            scroll_input_group(group, +1);
        }
        else if(numeric_input(key)) {
            group->editing = true;
            group->edit_start = 0;
            group->edit_cursor = 0;
            group->edit_buf[0] = '\0';
            group->edit_cursor = EditMBStringChar(
                    (unsigned char*)group->edit_buf, 
                    INPUT_FIELD_EDIT_BUF_LEN, 
                    group->edit_cursor, 
                    key);
            DisplayMBString((unsigned char*)group->edit_buf, 
                    group->edit_start, 
                    group->edit_cursor, 
                    1, 8);
        }
    } else {
        if(key == KEY_CTRL_EXIT) {
            *key_ptr = KEY_PRGM_NONE;
            group->editing = false;
            Cursor_SetFlashOff();
        }
        else if(key == KEY_CTRL_EXE) {
            *key_ptr = KEY_PRGM_NONE;
            group->editing = false;
            Cursor_SetFlashOff();
            *(group->fields[group->cursor].data) = atoi_int(group->edit_buf);
        }
        else if(key && key < 30000) {
            if(!numeric_input(key)) {
                return;
            }

            group->edit_cursor = EditMBStringChar(
                    (unsigned char*)group->edit_buf, 
                    INPUT_FIELD_EDIT_BUF_LEN, 
                    group->edit_cursor, 
                    key);
            DisplayMBString((unsigned char*)group->edit_buf, 
                    group->edit_start, 
                    group->edit_cursor, 
                    1, 8);
        } else {
            EditMBStringCtrl(
                    (unsigned char*)group->edit_buf, 
                    INPUT_FIELD_EDIT_BUF_LEN, 
                    &group->edit_start, 
                    &group->edit_cursor, 
                    key_ptr, 
                    1, 8);
            DisplayMBString((unsigned char*)group->edit_buf, 
                    group->edit_start, 
                    group->edit_cursor, 
                    1, 8);
        }
    }
}

void scroll_input_group(input_group_t *field_group, int offset)
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
