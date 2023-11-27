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

void regex_task(Text** _text, wchar_t* expression) {
    wchar_t* context = NULL;
    wchar_t seps[] = L" ,.";
    setlocale(LC_ALL, "ru_RU.UTF-8");  // set the locale to the user's default locale

    for (size_t i = 0; i < (*_text)->len; ++i) {
        char all_match = 1;
        wchar_t* str = wcsdup((*_text)->body[i]->body);
        wchar_t* word = wcstok(str, seps, &context);
        while (word != NULL) {
            int j = 0;
            int k = 0;
            int match = 0;
            while (expression[j] != L'\0' && word[k] != L'\0') {
                if (expression[j] == L'*') {
                    while (expression[j + 1] == L'*')
                        j++;
                    while (word[k] != L'\0' && expression[j + 1] != word[k])
                        k++;
                    if (word[k] == L'\0') {
                        match = 0;
                        break;
                    }
                } else if (expression[j] == L'?' || expression[j] == word[k]) {
                    j++;
                    k++;
                } else {
                    match = 0;
                    break;
                }
                match = 1;
            }
            if (!match) {
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
