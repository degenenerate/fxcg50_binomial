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
    input_field_t *input_fields;
    int count;
    int top;
    int height;
    int cursor;
    int cursor_top;
    bool editing;
    char edit_buf[INPUT_FIELD_EDIT_BUF_LEN];
    int edit_start;
    int edit_cursor;
} input_field_group_t;

void draw_input_field(input_field_group_t *field_group);
void handle_input_field_input(input_field_group_t *field_group, int *key_ptr);
void scroll_input_field(input_field_group_t *field_group, int offset);

#endif
