#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "hero.h"
#include "list.h"

int main(void) {
    Node* head = NULL;
    int choice;

    do {
        printf("\n--- Rejestr Bohaterow ---\n");
        printf("1. Dodaj bohatera\n");
        printf("2. Wyswietl bohaterow\n");
        printf("3. Edytuj bohatera\n");
        printf("0. Wyjscie\n");
        printf("Wybor: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            head = addHeroInteractive(head);
            break;
        case 2:
            printHeroes(head);
            break;
        case 3:
            editHero(head);
            break;
        case 0:
            printf("Koniec programu.\n");
            break;
        default:
            printf("Niepoprawny wybor.\n");
        }
    } while (choice != 0);

    freeList(head);
    return 0;
}
