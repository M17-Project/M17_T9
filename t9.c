//--------------------------------------------------------------------
// T9 text entry - t9.c
//
// Wojciech Kaczmarski, SP5WWP
// M17 Project, 4 November 2024
//--------------------------------------------------------------------
#include "t9.h"

uint8_t getDigit(char c)
{
    return "22233344455566677778889999"[c-'a']-'0'; //char-key map
}

node_t* createNode(void)
{
    node_t *n = (node_t*)malloc(sizeof(node_t));

    for(uint8_t i=0; i<8; i++)
        n->branch[i]=NULL;

    n->list=(list_t*)malloc(sizeof(list_t));
    n->list->word=NULL;
    n->list->next=NULL;

    return n;
}

void addDict(node_t *root, char *word)
{
    node_t *curr = root;
    list_t *list;
    uint8_t len = strlen(word);

    for(uint8_t i=0; i<len; i++)
    {
        uint8_t loc = getDigit(word[i])-2;
        if(curr->branch[loc]==NULL)
        {
            curr->branch[loc]=createNode();
        }
        curr=curr->branch[loc];
    }

    list = curr->list;
    while(list->next!=NULL)
    {
        list=list->next;
    }

    list->word=(char*)malloc(strlen(word));
    strcpy(list->word, word);
    list->next=(list_t*)malloc(sizeof(list_t));
    list->next->word=NULL;
    list->next->next=NULL;
}

char* getWord(node_t *root, char *code)
{
    node_t *curr = root;
    list_t *list;
    uint8_t len=strlen(code);

    for(uint8_t i=0; i<len && code[i]!='*'; i++)
    {
        curr = curr->branch[(uint8_t)code[i]-'0'-2];
    }

    list=curr->list;

    //use the asterisk key to access remaining entries
    for(uint8_t i=0; i<len; i++)
    {
        if(code[i]=='*' && list->next->word!=NULL) //scan for asterisks, but stop at the last entry
            list=list->next;
    }

    return list->word;
}
