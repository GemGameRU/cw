#include "error.h"

#include <stdio.h>
#include <stdlib.h>

#define ERROR_STD stderr

void ERROR(char* message) {
    fprintf(ERROR_STD, "Error: %s\n", message);
    exit(1);
}
