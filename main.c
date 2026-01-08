#include <stdio.h>
#include "hero.h"
#include "list.h"

int main(void) {
    Node* head = NULL;

    Hero h1 = { "Arthas", "Czlowiek", "Wojownik", 10, 80, AKTYWNY };
    Hero h2 = { "Elwyn", "Elf", "Mag", 7, 90, AKTYWNY };

    head = createNode(h1);
    head->next = createNode(h2);

    printf("Lista bohaterow:\n");
    printHeroes(head);

    freeList(head);
    return 0;
}
