//--------------------------------------------------------------------
// T9 text entry - test.c
//
// Wojciech Kaczmarski, SP5WWP
// M17 Project, 4 October 2024
//--------------------------------------------------------------------
#include <stdio.h>
#include "t9.h"

int main(void)
{
    //initialize a tree for the English dictionary
    node_t *dict_en = createNode();

    //load the word list
    char word[32]="";
    FILE *fp = fopen("wordlist.txt", "r");
    while(fgets(word, sizeof(word), fp)!=NULL)
    {
        word[strlen(word)-1]=0; //remove trailing newline char
        addDict(dict_en, word);
    }
    fclose(fp);

    //decode some words
    printf("getWord: %s\n", getWord(dict_en, "6736789"));
    printf("getWord: %s\n", getWord(dict_en, "47**"));
    printf("         %s\n", "T9");
    printf("getWord: %s\n", getWord(dict_en, "73239"));

    return 0;
}
