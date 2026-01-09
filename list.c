#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

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

int isNameUnique(Node* head, const char* name) {
    while (head) {
        if (strcmp(head->data.imie, name) == 0) {
            return 0;
        }
        head = head->next;
    }
    return 1;
}

Node* addHeroInteractive(Node* head) {
    Hero h;

    printf("Imie: ");
    scanf("%99s", h.imie);

    if (!isNameUnique(head, h.imie)) {
        printf("Bohater o takim imieniu juz istnieje!\n");
        return head;
    }

    printf("Rasa: ");
    scanf("%99s", h.rasa);

    printf("Klasa: ");
    scanf("%99s", h.klasa);

    printf("Poziom: ");
    scanf("%d", &h.poziom);

    printf("Reputacja (0-100): ");
    scanf("%d", &h.reputacja);

    printf("Status (0-aktywny, 1-na misji, 2-ranny, 3-zaginiony, 4-zawieszony): ");
    scanf("%d", (int*)&h.status);

    Node* n = createNode(h);
    if (!n) return head;

    n->next = head;
    return n;
}

