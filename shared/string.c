#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *chars;
    size_t length;
} String;

String *String_new(char *chars) {
    String *string = (String *)malloc(sizeof(String));

    if (!string || !chars) {
        return NULL;
    }

    size_t length = 0;
    const char *c_ptr = chars;

    while (*(c_ptr++)) {
        length++;
    }

    string->chars = chars;
    string->length = length;

    return string;
}
