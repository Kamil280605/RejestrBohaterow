#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "hero.h"
#include "list.h"

int main(void) {
    Node* head = loadFromFile("heroes.txt");
    int choice;

    do {
        printf("\n--- Rejestr Bohaterow ---\n");
        printf("1. Dodaj bohatera\n");
        printf("2. Wyswietl bohaterow\n");
        printf("3. Edytuj bohatera\n");
        printf("4. Usun bohatera\n");
        printf("5. Zapisz do pliku\n");
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
        case 4:
            head = removeHero(head);
            break;
        case 5:
            saveToFile(head, "heroes.txt");
            break;
        case 0:
            printf("Koniec programu.\n");
            break;
        default:
            printf("Niepoprawny wybor.\n");
        }
    } while (choice != 0);

    saveToFile(head, "heroes.txt");
    freeList(head);
    return 0;
}
