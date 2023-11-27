#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#include "error.h"

String** last_string(Text** _text) {
    return &(*_text)->body[(*_text)->len - 1];
}

String** extend_string(String** _str) {
    static String* _new_str;
    _new_str = *new_string((*_str)->allocated * 2);
    wmemcpy(_new_str->body, (*_str)->body, (*_str)->len);
    _new_str->len = (*_str)->len;
    _new_str->words = (*_str)->words;
    free(*_str);
    return &_new_str;
}
void clear(String** _str) {
    free(*_str);
    *_str = *new_string(MIN_VECTOR_SIZE);
}

Text** extend_text(Text** _text) {
    static Text* _new_text;
    _new_text = *new_text((*_text)->allocated * 2);
    memcpy(_new_text->body, (*_text)->body, (*_text)->len * sizeof(String*));
    _new_text->len = (*_text)->len;
    free(*_text);
    return &_new_text;
}

String** new_string(size_t _size) {
    static String* _new_str;
    _new_str = calloc(sizeof(String) + _size * sizeof(wchar_t), 1);
    if (_new_str == NULL) {
        ERROR("Failed to allocate new string");
        exit(1);  // fix warning
    }
    _new_str->allocated = _size;
    _new_str->len = 0;
    return &_new_str;
}

Text** new_text(size_t _size) {
    static Text* _new_text;
    _new_text = calloc(sizeof(Text) + _size * sizeof(String*), 1);
    if (_new_text == NULL) {
        ERROR("Failed to allocate new text");
        exit(1);  // fix warning
    }
    _new_text->allocated = _size;
    return &_new_text;
}

void append_wchar(Text** _text, wchar_t _ch) {
    String** _last = last_string(_text);
    if ((*_last)->allocated == (*_last)->len)
        *_last = *extend_string(_last);
    (*_last)->body[(*_last)->len++] = _ch;
};

void append_new_string(Text** _text) {
    if ((*_text)->allocated == (*_text)->len)
        *_text = *extend_text(_text);
    (*_text)->len++;
    *last_string(_text) = *new_string(MIN_VECTOR_SIZE);
};

void free_text(Text* _text) {
    for (size_t i = 0; i < _text->len; i++)
        free(_text->body[i]);
    free(_text);
}

Words** from_string_with_sep(String** _str) {
    static Words* _new_words;
    _new_words = calloc(1, sizeof(Words));
    if (!_new_words) {
        ERROR("Failed to allocate new words");
        exit(1);  // fix warning
    }
    wchar_t* context;
    _new_words->words = *new_text((*_str)->len + 1);
    _new_words->separators = *new_text((*_str)->len + 1);
    wchar_t* str_dup = wcsdup((*_str)->body);
    wcstok(str_dup, L" ,.", &context);

    int last = 0;
    for (size_t i = 0; i < (*_str)->len; i++) {
        if (str_dup[i] == (*_str)->body[i]) {
            if (last != 0)
                append_new_string(&_new_words->words);
            append_wchar(&_new_words->words, str_dup[i]);
        } else {
            if (last != 0)
                append_new_string(&_new_words->separators);
            append_wchar(&_new_words->separators, (*_str)->body[i]);
        }
    }
    free(str_dup);
    return &_new_words;
}

void swap_strings(Text** _text, size_t _pos1, size_t _pos2) {
    void* temp;
    temp = (*_text)->body[_pos1];
    (*_text)->body[_pos1] = (*_text)->body[_pos2];
    (*_text)->body[_pos2] = temp;
}
