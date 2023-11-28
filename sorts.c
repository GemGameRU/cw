#include "sorts.h"

#include <stdlib.h>

#include "util/error.h"
#include "util/vector.h"
#include "words.h"

inline static void _swap_f(float** _arr, size_t _pos1, size_t _pos2) {
    float temp = (*_arr)[_pos1];
    (*_arr)[_pos1] = (*_arr)[_pos2];
    (*_arr)[_pos2] = temp;
}

void sort_avgwordlen(Text** _text) {
    float* avg_lens;
    avg_lens = calloc((*_text)->len, sizeof(float));
    if (avg_lens == NULL) {
        ERROR("failed to allocate");
        exit(1);  // fix linter warning
    }

    for (size_t i = 0; i < (*_text)->len; i++) {
        Words* _tmp = *from_string_with_sep(&(*_text)->body[i]);
        avg_lens[i] = _tmp->avglen;
        free_words(_tmp);
    }

    for (size_t i = 0; i < (*_text)->len - 1; i++) {
        for (size_t j = 0; j < (*_text)->len - i - 1; j++)
            if (avg_lens[i] < avg_lens[i + 1]) {
                swap_strings(_text, i, i + 1);
                _swap_f(&avg_lens, i, i + 1);
            }
    }
    free(avg_lens);
}
void sort_text_all(Text** _text) {
    for (size_t i = 0; i < (*_text)->len; i++)
        sort_words(&(*_text)->body[i]);
}
void sort_words(String** _str) {
    Words* _words = *from_string_with_sep(_str);
    for (size_t i = 0; i < _words->words->len - 1; i++) {
        for (size_t j = 0; j < _words->words->len - i - 1; j++)
            if (_words->words->body[i]->len < _words->words->body[i + 1]->len)
                swap_strings(&_words->words, i, i + 1);
        }
    *_str = *to_string(&_words);
    free_words(_words);
}
