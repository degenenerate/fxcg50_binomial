#ifndef UI_INPUT_FIELD_H
#define UI_INPUT_FIELD_H

#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "typedef.h"

typedef struct {
    const char* text;
    int *data;
} input_field_t;

#define INPUT_FIELD_EDIT_BUF_LEN 16

typedef struct {
    input_field_t *fields;
    int count;
    int top;
    int height;
    int cursor;
    int cursor_top;
    bool editing;
    char edit_buf[INPUT_FIELD_EDIT_BUF_LEN];
    int edit_start;
    int edit_cursor;
} input_group_t;

void draw_input_group(input_group_t *field_group);
void handle_input_group_input(input_group_t *field_group, int *key_ptr);
void scroll_input_group(input_group_t *field_group, int offset);

#endif
