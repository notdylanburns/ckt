#include "circuit/interface.h"

#include <stdlib.h>

CktInterface *newCktInterface() {
    CktInterface *i = malloc(sizeof(CktInterface));
    if (i == NULL)
        return NULL;

    i->interface = NULL;
    i->pins = NULL;

    return i;
}

void destroyCktInterface(CktInterface *i) {
    if (i == NULL)
        return;

    destroyCktPins(i->pins);

    destroyCktHashMap(i->interface);

    free(i);
}

int addCktInterfacePin(CktInterface *i, const char *name, CktPinDirection dir, int width) {
    CktPin *p = newCktPin(name, dir, width);
    if (p == NULL)
        return 1;

    CktPin *b = NULL, *n = i->pins;
    while (n != NULL) {
        b = n;
        n = b->next;
    }

    if (b == NULL)
        i->pins = p;
    else
        b->next = p;

    return 0;
}

CktInterface *createCktInterfaceInstance(CktInterface *i) {
    CktInterface *n = newCktInterface();
    if (n == NULL)
        return NULL;

    n->interface = newCktHashMap(NULL, &destroyCktPin);
    if (n->interface == NULL)
        goto cleanup;

    CktPin *p = i->pins;
    while (p != NULL) {
        if (addCktHashMapItem(n->interface, p->name, (void *)p))
            goto cleanup;
        p = p->next;
    }

    return n;

cleanup:
    destroyCktInterface(n);
    return NULL;
}