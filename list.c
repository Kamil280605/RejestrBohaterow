#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node* createNode(Hero h) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) {
        printf("Blad alokacji pamieci!\n");
        return NULL;
    }

    n->data = h;
    n->next = NULL;
    return n;
}

void printHeroes(Node* head) {
    if (!head) {
        printf("Lista bohaterow jest pusta.\n");
        return;
    }

    Node* temp = head;
    while (temp) {
        printf("Imie: %s | Rasa: %s | Klasa: %s | Poziom: %d | Reputacja: %d | Status: %s\n",
            temp->data.imie,
            temp->data.rasa,
            temp->data.klasa,
            temp->data.poziom,
            temp->data.reputacja,
            statusToString(temp->data.status)
        );
        temp = temp->next;
    }
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
