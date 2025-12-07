#!/usr/bin/env python3

INPUT_WORDS   = "../dict/wordlist.txt"
INPUT_OFFSETS = "../dict/wordlist_sorted_offsets.txt"
OUTPUT        = "../dict/dict_en_offsets.h"

header_guard = "DICT_EN_OFFSETS_H"

with open(INPUT_WORDS, "r", encoding="utf-8") as f:
    words = [w.strip() for w in f if w.strip()]

word_count = len(words)   # DICT_EN_WC

with open(INPUT_OFFSETS, "r", encoding="utf-8") as f:
    offsets = [int(x.strip()) for x in f if x.strip()]

assert len(offsets) == word_count - 1

with open(OUTPUT, "w", encoding="utf-8") as out:

    out.write(f"#ifndef {header_guard}\n")
    out.write(f"#define {header_guard}\n\n")

    out.write("#include <stdint.h>\n")
    out.write(f"#define DICT_EN_WC {word_count}\n\n")

    out.write(f"const uint16_t dict_offsets[DICT_EN_WC-1] =\n{{\n")

    for off in offsets:
        out.write(f"\t{off},\n")

    out.write("};\n\n")
    out.write("#endif\n")