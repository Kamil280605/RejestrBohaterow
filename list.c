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

Node* findHeroByName(Node* head, const char* name) {
    while (head) {
        if (strcmp(head->data.imie, name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void editHero(Node* head) {
    char name[100];
    printf("Podaj imie bohatera do edycji: ");
    scanf("%99s", name);

    Node* node = findHeroByName(head, name);
    if (!node) {
        printf("Nie znaleziono bohatera.\n");
        return;
    }

    printf("Edycja bohatera %s\n", node->data.imie);

    printf("Nowa rasa: ");
    scanf("%99s", node->data.rasa);

    printf("Nowa klasa: ");
    scanf("%99s", node->data.klasa);

    printf("Nowy poziom: ");
    scanf("%d", &node->data.poziom);

    printf("Nowa reputacja: ");
    scanf("%d", &node->data.reputacja);

    printf("Nowy status (0-aktywny, 1-na misji, 2-ranny, 3-zaginiony, 4-zawieszony): ");
    scanf("%d", (int*)&node->data.status);

    printf("Dane bohatera zaktualizowane.\n");
}

Node* removeHero(Node* head) {
    char name[100];
    printf("Podaj imie bohatera do usuniecia: ");
    scanf("%99s", name);

    Node* current = head;
    Node* prev = NULL;

    while (current) {
        if (strcmp(current->data.imie, name) == 0) {

            if (current->data.status == NA_MISJI) {
                printf("Nie mozna usunac bohatera bedacego na misji!\n");
                return head;
            }

            if (prev == NULL) {
                head = current->next;
            }
            else {
                prev->next = current->next;
            }

            free(current);
            printf("Bohater zostal usuniety.\n");
            return head;
        }

        prev = current;
        current = current->next;
    }

    printf("Nie znaleziono bohatera o podanym imieniu.\n");
    return head;
}

void saveToFile(Node* head, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Nie mozna otworzyc pliku do zapisu.\n");
        return;
    }

    while (head) {
        fprintf(f, "%s;%s;%s;%d;%d;%d\n",
            head->data.imie,
            head->data.rasa,
            head->data.klasa,
            head->data.poziom,
            head->data.reputacja,
            head->data.status
        );
        head = head->next;
    }

    fclose(f);
    printf("Zapisano dane do pliku.\n");
}

Node* loadFromFile(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Plik nie istnieje. Start z pusta lista.\n");
        return NULL;
    }

    Node* head = NULL;
    Hero h;

    while (fscanf(f, "%99[^;];%99[^;];%99[^;];%d;%d;%d\n",
        h.imie,
        h.rasa,
        h.klasa,
        &h.poziom,
        &h.reputacja,
        (int*)&h.status) == 6) {

        Node* n = createNode(h);
        if (!n) break;

        n->next = head;
        head = n;
    }

    fclose(f);
    printf("Wczytano dane z pliku.\n");
    return head;
}

void searchByName(Node* head) {
    char query[100];
    int found = 0;

    printf("Podaj imie lub prefiks: ");
    scanf("%99s", query);

    while (head) {
        if (strncmp(head->data.imie, query, strlen(query)) == 0) {
            printf("Imie: %s | Rasa: %s | Klasa: %s | Poziom: %d | Reputacja: %d | Status: %s\n",
                head->data.imie,
                head->data.rasa,
                head->data.klasa,
                head->data.poziom,
                head->data.reputacja,
                statusToString(head->data.status)
            );
            found = 1;
        }
        head = head->next;
    }

    if (!found) {
        printf("Brak pasujacych bohaterow.\n");
    }
}

void searchByLevel(Node* head) {
    int level;
    int found = 0;

    printf("Podaj minimalny poziom: ");
    scanf("%d", &level);

    while (head) {
        if (head->data.poziom >= level) {
            printf("Imie: %s | Rasa: %s | Klasa: %s | Poziom: %d | Reputacja: %d | Status: %s\n",
                head->data.imie,
                head->data.rasa,
                head->data.klasa,
                head->data.poziom,
                head->data.reputacja,
                statusToString(head->data.status)
            );
            found = 1;
        }
        head = head->next;
    }

    if (!found) {
        printf("Brak bohaterow spelniajacych kryterium.\n");
    }
}

Node* sortByName(Node* head) {
    if (!head) return NULL;

    int swapped;
    Node* ptr;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != lptr) {
            if (strcmp(ptr->data.imie, ptr->next->data.imie) > 0) {
                Hero tmp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = tmp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);

    printf("Posortowano alfabetycznie po imieniu.\n");
    return head;
}

Node* sortByLevel(Node* head) {
    if (!head) return NULL;

    int swapped;
    Node* ptr;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != lptr) {
            if (ptr->data.poziom > ptr->next->data.poziom) {
                Hero tmp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = tmp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);

    printf("Posortowano po poziomie.\n");
    return head;
}



