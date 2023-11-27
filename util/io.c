#include "io.h"

#include <locale.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>

#include "vector.h"

#define PARSE_ELLIPSIS 0

void read_text(Text** _text) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    append_new_string(_text);
    int newline = 0;
    int ended = 0;
    int dots = 0;
    int space = 0;
    int word = 1;

    for (wchar_t ch = getwchar(); !(newline == 1 && ch == L'\n'); ch = getwchar()) {
        switch (ch) {
            case L'.':
                dots++;
                word = 0;
                space = 0;
                append_wchar(_text, ch);
                if (dots)
                    ended = 1;
#if PARSE_ELLIPSIS
                if (dots == 3)
                    ended = 0;
#endif
                break;
            case L'\n':
                newline++;
                if (!space) {
                    append_wchar(_text, L' ');
                    space = 1;
                }

                break;
            case L'\t':
            case L' ':
#if PARSE_ELLIPSIS
                if (dots == 1)
#else
                if (dots)
#endif
                    ended = 1;
                else
                    dots = 0;
                if (ended)
                    break;
                space = 1;
                word = 0;
                append_wchar(_text, ch);
                break;
            case L',':
                word = 0;
            default:
                if (ended)
                    append_new_string(_text);
                if (!word) {
                    (*last_string(_text))->words++;
                    word = 1;
                }
                ended = 0;
                newline = 0;
                dots = 0;
                space = 0;
                append_wchar(_text, ch);
                break;
        }
    }
}

void output_text(Text** _text) {
    setlocale(LC_ALL, "ru_RU.utf8");
    for (size_t i = 0; i < (*_text)->len; i++)
        if ((*_text)->body[i]->len != 0)
            printf("%ls\n", (*_text)->body[i]->body);
}
