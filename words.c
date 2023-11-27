#include "words.h"

#include <stdlib.h>
#include <wchar.h>

#include "util/error.h"
#include "util/vector.h"

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
    _new_words->strlen = (*_str)->len;
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
    _new_words->avglen = avg_len(_new_words);
    free(str_dup);
    return &_new_words;
}

String** to_string(Words** _words) {
    static String* _new_string;
    _new_string = *new_string((*_words)->strlen + 1);
    _new_string->len = (*_words)->strlen;
    for (size_t i = 0; i < (*_words)->words->len; i++) {
        wcscpy(_new_string->body, (*_words)->words->body[i]->body);
        wcscpy(_new_string->body, (*_words)->separators->body[i]->body);
    }
    return &_new_string;
}

inline float avg_len(Words* _words) {
    size_t sum = 0;

    if (_words->words->len == 0)
        return 0;

    for (size_t i = 0; i < _words->words->len; i++)
        sum += _words->words->body[i]->len;

    return sum / _words->words->len;
}
