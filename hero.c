#include "hero.h"

const char* statusToString(Status status) {
    switch (status) {
    case AKTYWNY: return "aktywny";
    case NA_MISJI: return "na misji";
    case RANNY: return "ranny";
    case ZAGINIONY: return "zaginiony";
    case ZAWIESZONY: return "zawieszony";
    default: return "nieznany";
    }
}
