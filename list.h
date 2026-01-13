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

Node* addHeroInteractive(Node* head);
int isNameUnique(Node* head, const char* name);

Node* findHeroByName(Node* head, const char* name);
void editHero(Node* head);

Node* removeHero(Node* head);

void saveToFile(Node* head, const char* filename);
Node* loadFromFile(const char* filename);
