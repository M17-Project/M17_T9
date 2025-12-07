//--------------------------------------------------------------------
// T9 text entry - test.c
//
// Wojciech Kaczmarski, SP5WWP
// M17 Project, 5 December 2025
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

#include "../t9.h"
#include "../dict/dict_en.h"
#include "../dict/dict_en_sorted.h"
#include "../dict/dict_en_offsets.h"

const char *w;
struct timeval tv[2];
uint64_t t;

int main(void)
{
    // show the dictionary size
    printf("Dict size\n");
    printf(" normal:  %llu bytes\n", sizeof(dict));
    printf(" sorted:  %llu bytes\n", sizeof(dict_sorted));
    printf(" offsets: %llu bytes\n", sizeof(dict_offsets));
    printf("----------------------\n");

    // benchmark - 1000 operations
    // normal search
    printf("Normal search");
#if defined(__MINGW32__) || defined(__MINGW64__)
    mingw_gettimeofday(&tv[0], NULL);
#else
    gettimeofday(&tv[0], NULL);
#endif

    for (uint32_t i = 0; i < 1000; i++)
    {
        w = getWord(dict, "43556"); // "hello"
    }

#if defined(__MINGW32__) || defined(__MINGW64__)
    mingw_gettimeofday(&tv[1], NULL);
#else
    gettimeofday(&tv[1], NULL);
#endif

    t = (uint64_t)(tv[1].tv_sec - tv[0].tv_sec) * 1000000ULL + (uint64_t)(tv[1].tv_usec - tv[0].tv_usec);
    printf(" time: %llu.%03llu milliseconds\n", t / 1000ULL, t % 1000ULL);

    // log search
    printf("Log search");
#if defined(__MINGW32__) || defined(__MINGW64__)
    mingw_gettimeofday(&tv[0], NULL);
#else
    gettimeofday(&tv[0], NULL);
#endif

    for (uint32_t i = 0; i < 1000; i++)
    {
        w = getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "43556"); // "hello"
    }

#if defined(__MINGW32__) || defined(__MINGW64__)
    mingw_gettimeofday(&tv[1], NULL);
#else
    gettimeofday(&tv[1], NULL);
#endif

    t = (uint64_t)(tv[1].tv_sec - tv[0].tv_sec) * 1000000ULL + (uint64_t)(tv[1].tv_usec - tv[0].tv_usec);
    printf(" time:    %llu.%03llu milliseconds\n", t / 1000ULL, t % 1000ULL);

    // print some text
    printf("Standard search:    ");
    printf("%s ", getWord(dict, "43556"));    // hello
    printf("%s ", getWord(dict, "8447"));     // this
    printf("%s ", getWord(dict, "47"));       // is
    printf("%s\n", getWord(dict, "6736789")); // openrtx

    printf("Log search:         ");
    printf("%s ", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "43556"));    // hello
    printf("%s ", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "8447"));     // this
    printf("%s ", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "47"));       // is
    printf("%s\n", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "6736789")); // openrtx

    printf("Word clusters (linear search):\n");
    printf(" %s\n", getWord(dict, "2273"));      // base
    printf(" %s\n", getWord(dict, "2273*"));     // card
    printf(" %s\n", getWord(dict, "2273**"));    // care
    printf(" %s\n", getWord(dict, "2273***"));   // case
    printf(" %s\n", getWord(dict, "2273****"));  // case
    printf(" %s\n", getWord(dict, "2273*****")); // case

    printf("Word clusters (log search):\n");
    printf(" %s\n", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "2273"));      // base
    printf(" %s\n", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "2273*"));     // card
    printf(" %s\n", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "2273**"));    // care
    printf(" %s\n", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "2273***"));   // case
    printf(" %s\n", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "2273****"));  // base
    printf(" %s\n", getWordLog(dict_sorted, DICT_EN_WC, dict_offsets, "2273*****")); // card

    return 0;
}
