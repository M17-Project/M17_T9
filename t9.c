//--------------------------------------------------------------------
// T9 text entry - t9.c
//
// Wojciech Kaczmarski, SP5WWP
// M17 Project, 7 December 2025
//--------------------------------------------------------------------
#include "t9.h"

// get digit for a given character (lowercase a..z)
// we assume that the wordlist does not use any other characters
uint8_t getDigit(char c)
{
    return "22233344455566677778889999"[c - 'a'];
}

uint8_t countAsterisks(const char *code, uint8_t len)
{
    uint8_t depth = 0;

    for (int8_t i = len - 1; i >= 0; i--)
    {
        if (code[i] == '*')
            depth++;
        else
            break;
    }

    return depth;
}

// --- linear search ---
// search the dictionary for a word matching the input T9 code
// find the first match using linear search
// no asterisks at the end of the code -> return the first occurrence
// NOTE: use with alphabetically sorted dictionary *only*
// TODO: too many asterisks will make the function return the last matching entry
//       this happens when the size of T9 collision cluster is smaller than the number of asterisks
const char *getWord(const char *dict, const char *code)
{
    uint8_t code_len = strlen(code);

    // check code length
    if (code_len == 0)
        return "";

    // count trailing asterisks
    uint8_t depth = countAsterisks(code, code_len);

    // subtract the amount of asterisks from the code length
    code_len -= depth;

    // zero-length code - return
    if (code_len == 0)
        return "";

    const char *word = dict;
    const char *lastword = "";

    // word length
    uint8_t wlen = 0;

    do
    {
        wlen = strlen(word);

        if (wlen == code_len)
        {
            // speed up the search a bit
            // exit early when there is no chance of finding a matching code
            if (getDigit(word[0]) > code[0])
                break;

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
                else
                {
                    lastword = word;
                    depth--;
                }
            }
        }

        // look at the next word in the dictionary
        word += wlen + 1;
    } while (wlen != 0); // until we reach the end of it

    // return an empty string if no match has been found
    return lastword;
}

// --- log search ---
// compare T9 code with a word (for log search direction)
int8_t cmp_t9(const char *word, const char *code)
{
    uint8_t i = 0;

    // compare digit-by-digit
    while (word[i] && code[i])
    {
        uint8_t d = getDigit(word[i]);
        if (d < code[i])
            return -1;
        if (d > code[i])
            return 1;
        i++;
    }

    // if both ended - equal
    if (!word[i] && !code[i])
        return 0;

    // if only word ended - word is smaller
    if (!word[i])
        return -1;

    // if only code ended - code is smaller
    return 1;
}

// returns index of first matching word, or 0xFFFF if none
uint16_t getFirstIndex(const char *dict, uint16_t dict_size, const uint16_t *offsets, const char *code)
{
    uint16_t lo = 0, hi = dict_size - 1;
    uint16_t found = 0xFFFF; // out of bounds value for signalling failure

    // binary search for any (first) match
    while (lo <= hi)
    {
        uint16_t mid = (lo + hi) / 2;
        const char *word = &dict[mid == 0 ? 0 : offsets[mid - 1]];
        int8_t cmp = cmp_t9(word, code);

        if (cmp < 0)
            lo = mid + 1;
        else if (cmp > 0)
            hi = mid - 1;
        else
        {
            found = mid;
            break; // stop early - we now switch to linear scan
        }
    }

    // return 0xFFFF if failed
    if (found == 0xFFFF)
        return 0xFFFF;

    // linear scan backwards to first occurrence
    while (found)
    {
        const char *prev = &dict[found == 1 ? 0 : offsets[found - 2]]; // previous word
        if (cmp_t9(prev, code) != 0)
            break;
        found--;
    }

    return found;
}

// count how many consecutive words share the same T9 code (code collisions)
// we don't expect to have more than 10, so can use uint8_t here
uint8_t countBlock(const char *dict, uint16_t dict_size, const uint16_t *offsets, int first_index, const char *code)
{
    uint8_t count = 0;

    for (uint16_t i = first_index; i < dict_size; i++)
    {
        // implicit 0 for the first word entry is not contained within the 'offsets'
        const char *word = dict + (i == 0 ? 0 : offsets[i - 1]);

        if (cmp_t9(word, code) == 0)
            count++;
        else
            break;
    }

    return count;
}

// cycle through all words with matching T9 code
const char *getWordCycling(const char *dict, uint16_t dict_size, const uint16_t *offsets, const char *code, uint8_t code_len, uint8_t depth)
{
    // local copy of the code
    char c[T9_MAX_CODE_LEN] = "";
    memcpy(c, code, code_len);

    // find the first match
    uint16_t first = getFirstIndex(dict, dict_size, offsets, c);

    // no matches?
    if (first == 0xFFFF)
        return "";

    // count size of the T9 code collision block
    uint8_t block_len = countBlock(dict, dict_size, offsets, first, c);

    // choose index with wrap-around
    uint16_t idx = first + (depth % block_len);

    // return the word at this index
    return &dict[idx == 0 ? 0 : offsets[idx - 1]];
}

// find T9 code in the dictionary using log search
// NOTE: use with lexicographically sorted T9 dictionary *only*
const char *getWordLog(const char *dict, uint16_t dict_size, const uint16_t *offsets, const char *code)
{
    uint8_t code_len = strlen(code);

    // check code length
    if (code_len == 0)
        return "";

    // count trailing asterisks
    uint8_t depth = countAsterisks(code, code_len);

    // subtract the amount of asterisks from the code length
    code_len -= depth;

    // zero-length code - return
    if (code_len == 0)
        return "";

    // shorten the code - remove asterisks
    char c[T9_MAX_CODE_LEN] = "";
    strncpy(c, code, code_len);

    return getWordCycling(dict, dict_size, offsets, c, code_len, depth);
}
