//--------------------------------------------------------------------
// T9 text entry - t9.c
//
// Wojciech Kaczmarski, SP5WWP
// M17 Project, 4 December 2025
//--------------------------------------------------------------------
#include "t9.h"

uint8_t getDigit(const char c)
{
    return "22233344455566677778889999"[c - 'a'];
}

char *getWord(char *dict, char *code)
{
    char *word = dict;

    uint8_t code_len = strlen(code);

    // count asterisks
    uint8_t depth = 0;
    for (uint8_t i = 0; i < code_len; i++)
    {
        if (code[i] == '*')
            depth++;
    }

    // subtract the amount of asterisks from the code length
    code_len -= depth;

    // word length
    uint8_t wlen = 0;

    do
    {
        wlen = strlen(word);

        if (wlen == code_len)
        {
            // speed up the search a bit. TODO: there's room for improvement here
            if (getDigit(word[0]) > code[0])
            {
                break;
            }

            uint8_t match = 1;

            for (uint8_t i = 0; i < code_len; i++)
            {
                if (getDigit(word[i]) != code[i])
                {
                    match = 0;
                    break;
                }
            }

            if (match)
            {
                if (depth == 0)
                    return word;
                depth--;
            }
        }

        word += wlen + 1;
    } while (wlen != 0);

    return "";
}
