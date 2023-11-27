#include "regex_task.h"

#include <ctype.h>
#include <iconv.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#include "util/error.h"
int check_word(wchar_t* word, wchar_t* expression);

void regex_task(Text** _text, wchar_t* expression) {
    const wchar_t* seps = L" ,.";
    wchar_t* context = NULL;
    setlocale(LC_ALL, "ru_RU.UTF-8");  // set the locale to the user's default locale

    for (size_t i = 0; i < (*_text)->len; ++i) {
        char all_match = 1;
        wchar_t* str = wcsdup((*_text)->body[i]->body);
        wchar_t* word = wcstok(str, seps, &context);
        while (word != NULL) {
            if (!check_word(word, expression)) {
                all_match = 0;
                break;
            }
            word = wcstok(NULL, seps, &context);
        }
        free(str);
        if (!all_match)
            clear(&(*_text)->body[i]);
    }
}

int check_word(wchar_t* word, wchar_t* expression) {
    int _e = 0;
    int _w = 0;
    int match = 0;
    while (expression[_e] != L'\0' && word[_w] != L'\0') {
        if (expression[_e] == L'*') {
            for (size_t i = 0; word[i] != L'\0'; i++) {
                match += check_word(&word[_w + i], &expression[_e + 1]);
                if (match)
                    return 1;
            }
            return 0;
            break;
        } else if (expression[_e] == L'?' || expression[_e] == word[_w]) {
            _e++;
            _w++;
        } else {
            return 0;
            break;
        }
    }
    return 1;
}
