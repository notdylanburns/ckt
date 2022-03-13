#include "circuit/pin.h"

#include <stdlib.h>
#include <string.h>

CktPin *newCktPin(const char *name, CktPinDirection dir, int width) {
    CktPin *p = malloc(sizeof(CktPin));
    if (p == NULL)
        return NULL;

    p->name = strdup(name);
    if (p->name == NULL) {
        free(p);
        return NULL;
    }

    p->direction = dir;
    p->next = NULL;
    p->state = Z;
    p->width = width;

    return p;
}

void destroyCktPin(CktPin *p) {
    if (p == NULL)
        return;

    free(p->name);
    free(p);
}

void destroyCktPins(CktPin *p) {
    CktPin *n;
    while (p != NULL) {
        n = p->next;
        destroyCktPin(p);
        p = n;
    }
}