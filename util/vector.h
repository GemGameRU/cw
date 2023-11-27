#pragma once
#include <stddef.h>

#define MIN_VECTOR_SIZE 16

typedef struct Sentence {
    size_t len;
    size_t words;
    size_t allocated;
    wchar_t body[];
} String;

typedef struct Text {
    size_t len;
    size_t allocated;
    String* body[];
} Text;

String** new_string(size_t _size);
String** extend_string(String** _str);
void append_wchar(Text** _text, wchar_t _ch);
void clear(String** _str);

Text** new_text(size_t _size);
Text** extend_text(Text** _text);
void append_new_string(Text** _text);
String** last_string(Text** _text);
void swap_strings(Text** _text);

void free_text(Text* _text);
