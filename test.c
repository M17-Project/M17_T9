//--------------------------------------------------------------------
// T9 text entry - test.c
//
// Wojciech Kaczmarski, SP5WWP
// M17 Project, 4 December 2025
//--------------------------------------------------------------------
#include <stdio.h>

#ifdef __has_include
#if __has_include(<sys/time.h>)
#include <sys/time.h>
#else
#include <time.h>
#endif
#else
#if defined(__unix__) || defined(__APPLE__) || defined(__linux__)
#include <sys/time.h>
#else
#include <time.h>
#endif
#endif

#include "t9.h"
#include "dict_en.h"

char *w;

int main(void)
{
    // show the dictionary size
    printf("Dict size: %llu bytes\n", sizeof(dict_en));

    // benchmark - 1mil operations
    struct timeval tv[2];
    #if defined(__MINGW32__) || defined(__MINGW64__)
    mingw_gettimeofday(&tv[0], NULL);
    #else
    gettimeofday(&tv[0], NULL);
    #endif

    for (uint32_t i = 0; i < 1000; i++)
    {
        w = getWord(dict_en, "43556"); // "hello"
    }

    #if defined(__MINGW32__) || defined(__MINGW64__)
    mingw_gettimeofday(&tv[1], NULL);
    #else
    gettimeofday(&tv[1], NULL);
    #endif

    uint64_t t = (uint64_t)(tv[1].tv_sec - tv[0].tv_sec) * 1000000ULL + (uint64_t)(tv[1].tv_usec - tv[0].tv_usec);

    printf("Time: %llu.%06llu seconds\n", t / 1000000ULL, t % 1000000ULL);

    // print some text
    printf("Test: ");
    printf("%s ", getWord(dict_en, "43556"));    // hello
    printf("%s ", getWord(dict_en, "8447"));     // this
    printf("%s ", getWord(dict_en, "47"));       // is
    printf("%s\n", getWord(dict_en, "6736789")); // openrtx

    return 0;
}

