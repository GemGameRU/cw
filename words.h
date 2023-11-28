#pragma once

#include "util/vector.h"

typedef struct Words {
    Text* words;
    Text* separators;
    float avglen;
    size_t strlen;
} Words;

Words** from_string_with_sep(String** _str);
String** to_string(Words** _words);
void free_words(Words* _words);
