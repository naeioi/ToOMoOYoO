#ifndef __TEST_H
#define __TEST_H
#include <stdio.h>

void testbegin(const char *s) {
    printf("------Test Begin-------\n");
    puts(s);
    printf("-----------------------\n\n");
}

void testend() {
    printf("\n\n-------Test End--------\n\n");
}

#endif