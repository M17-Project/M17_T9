//--------------------------------------------------------------------
// T9 text entry - t9.h
//
// Wojciech Kaczmarski, SP5WWP
// M17 Project, 6 December 2025
//--------------------------------------------------------------------
#ifndef M17_T9_LIB
#define M17_T9_LIB

#include <stdint.h>
#include <string.h>

#define T9_MAX_CODE_LEN 32

uint8_t getDigit(char c);
uint8_t countAsterisks(const char *code, uint8_t len);

// linear search
char* getWord(const char *dict, const char *code);

// log search
int8_t cmp_t9(const char *word, const char *code);
uint16_t getFirstIndex(const char *dict, uint16_t dict_size, const uint16_t *offsets, const char *code);
uint8_t countBlock(const char *dict, uint16_t dict_size, const uint16_t *offsets, int first_index, const char *code);
char *getWordCycling(const char *dict, uint16_t dict_size, const uint16_t *offsets, const char *code, uint8_t code_len, uint8_t depth);
char *getWordLog(const char *dict, uint16_t dict_size, const uint16_t *offsets, const char *code);

#endif
