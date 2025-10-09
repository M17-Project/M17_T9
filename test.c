//--------------------------------------------------------------------
// T9 text entry - test.c
//
// Wojciech Kaczmarski, SP5WWP
// M17 Project, 6 November 2024
//--------------------------------------------------------------------
#include <stdio.h>

#include <t9.h>
#include "dict_en.h"

int main(void)
{
    //printf("dict size=%llu\n\n", sizeof(dict_en));

    printf("%s\n", getWord(dict_en, "43556")); //hello
    printf("%s\n", getWord(dict_en, "8447")); //this
    printf("%s\n", getWord(dict_en, "47")); //is
    printf("%s\n", getWord(dict_en, "6736789")); //openrtx

    return 0;
}
