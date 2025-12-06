#!/usr/bin/env python3

INPUT  = "../dict/wordlist.txt"
OUTPUT = "../dict/dict_en.h"

header_guard = "DICT_EN_H"

with open(INPUT, "r", encoding="utf-8") as f:
    words = [w.strip() for w in f if w.strip()]

with open(OUTPUT, "w", encoding="utf-8") as out:
    out.write(f"#ifndef {header_guard}\n")
    out.write(f"#define {header_guard}\n\n")

    out.write("char dict[] = \"\\\n")

    for w in words:
        out.write(f"{w}\\0\\\n")

    out.write("\\0\\\n\";\n\n")

    out.write("#endif\n")