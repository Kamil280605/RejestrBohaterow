#ifndef LIST_H
#define LIST_H

#include "hero.h"

typedef struct Node {
    Hero data;
    struct Node* next;
} Node;

Node* createNode(Hero h);
void printHeroes(Node* head);
void freeList(Node* head);

#endif
