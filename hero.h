#ifndef HERO_H
#define HERO_H

#define MAX_NAME 100

typedef enum {
    AKTYWNY,
    NA_MISJI,
    RANNY,
    ZAGINIONY,
    ZAWIESZONY
} Status;

typedef struct {
    char imie[MAX_NAME];
    char rasa[MAX_NAME];
    char klasa[MAX_NAME];
    int poziom;
    int reputacja;
    Status status;
} Hero;

const char* statusToString(Status status);

#endif
