#include <locale.h>
#include <stdio.h>

#include "start.h"
#include "util/error.h"

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    puts("Course work for option 5.2, created by Vadim Grebenyuk.");
    start();
    return 0;
}
