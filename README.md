# M17_T9

A small C library implementing T9 text entry with a sample English dictionary
(around 3,000 common words).

## Features
- T9 character to digit encoding (`2`–`9`)
- Exact-length T9 search
- Support for cycling through words within a collision cluster using trailing `*`
- Two lookup modes:
  - Linear search on an alphabetically sorted dictionary
  - Binary search on a T9 lexicographically sorted dictionary with offsets
- Compact dictionary stored as a flat, zero-terminated string list

## Dictionary
`/dict/wordlist.txt` contains a sample word list.  
It is used to generate:
- `dict_en.h` — alphabetically sorted list  
- `dict_en_sorted.h` — T9-sorted list  
- `dict_en_offsets.h` — 16-bit offsets for the T9-sorted list (excluding the first word)

Python scripts available in the `/tools/` directory can be used to generate those header files based on any input wordlist text file.

>[!NOTE]
>The dictionary may only contain lowercase ASCII words.

## API

### getDigit()
Returns the T9 digit (`2`–`9`) for a given lowercase letter.

### cmp_t9()
Lexicographical comparison between a word (string) and a T9 code.

### \*getWord()
Linear search on an alphabetically sorted dictionary.  
Returns the first word matching the T9 code.  
Trailing `*` selects the *n*-th match, too many `*` returns the last match.

### \*getWordLog()
Binary search on a T9-sorted dictionary.  
Handles cycling through collisions using modulo arithmetic.

## Building
Run `make` in the main directory. For tests, run `make test` followed by optional `make testrun` to execute them. To install the library, use `make install`.

`libt9.so` is the shared library.  
A test program is built from `/tests/test.c`.

## Usage example
```C
#include <t9.h>

// returns the second word matching T9 code "227"...
// ...using linear search
char *str1 = getWord(dict, "227*");

// ...using log (binary) search
char *str2 = getWordLog(dict_sorted, DICT_EN_WC, dict_offset, "227*");
```
Compile with `gcc ... -lt9`.

## License
GPL-2.0 license (see the LICENSE file).
