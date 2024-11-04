//--------------------------------------------------------------------
// T9 text entry - t9.h
//
// Wojciech Kaczmarski, SP5WWP
// M17 Project, 4 November 2024
//--------------------------------------------------------------------
#pragma once
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct list
{
    char *word;
    struct list *next;
} list_t;

typedef struct node
{
    struct node *branch[8]; //8 buttons: [2]..[9]
    struct list *list;
} node_t;

uint8_t getDigit(char c);
node_t* createNode(void);

void addDict(node_t *root, char *word);
char* getWord(node_t *root, char *code);
