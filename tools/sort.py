#!/usr/bin/env python3

# T9 mapping
t9 = {
    **dict.fromkeys(list("abc"),  '2'),
    **dict.fromkeys(list("def"),  '3'),
    **dict.fromkeys(list("ghi"),  '4'),
    **dict.fromkeys(list("jkl"),  '5'),
    **dict.fromkeys(list("mno"),  '6'),
    **dict.fromkeys(list("pqrs"), '7'),
    **dict.fromkeys(list("tuv"),  '8'),
    **dict.fromkeys(list("wxyz"), '9'),
}

def t9code(w):
    return ''.join(t9[c] for c in w.lower())

# read words
with open("../dict/wordlist.txt") as f:
    words = [w.strip() for w in f if w.strip()]

# sort by T9, then alphabetically
words.sort(key=lambda w: (t9code(w), w.lower()))

# write sorted list
with open("../dict/wordlist_sorted.txt", "w") as f:
    f.write("\n".join(words))

# write cumulative lengths (+1 per word)
cum = 0
with open("../dict/wordlist_sorted_offsets.txt", "w") as f:
    for w in words[:-1]:        # last word needs no offset after it
        cum += len(w) + 1
        f.write(f"{cum}\n")