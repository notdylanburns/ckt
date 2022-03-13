#include "circuit/circuit.h"

#include <stdlib.h>
#include <string.h>

CktCircuit *newCktCircuit(const char *name, ) {
    CktCircuit *c = malloc(sizeof(CktCircuit));
    if (c == NULL)
        return NULL;

    c->name = strdup(name);
    if (c->name == NULL) {
        free(c);
        return NULL;
    }

    c->declaration = NULL;
    c->interface = NULL;

    c->is_template = true;
    c->do_update = false;

    return c;
}

void destroyCktCircuit(CktCircuit *c) {
    if (c == NULL)
        return;
    
    //destroyCktDeclaration(c->declaration);
    destroyCktInterface(c->interface);

    free(c->name);
    free(c);
}

int addCktCircuitPin(CktCircuit *c, const char *pin_name, CktPinDirection dir, int width) {
    if (c->interface == NULL) {
        c->interface = newCktInterface();
        if (c->interface == NULL)
            return 1;
    }

    return addCktInterfacePin(c->interface, pin_name, dir, width);
}

int addCktCircuitInterface(CktCircuit *c, CktInterface *i, CktHashMap *params) {
    CktPin *p = i->pins;
    while (p != NULL) {
        if (addCktCircuitPin(c, p->name, p->direction, p->width))
            return 1;
        p = p->next;
    }

    return 0;
}

CktCircuit *createCktCircuitInstance(CktCircuit *c) {
    if (!c->is_template)
        return NULL;
    
    CktCircuit *i = newCktCircuit(c->name);
    if (i == NULL)
        return NULL;

    i->is_template = false;
    i->interface = newCktInterfaceInstance(c->interface);
    if (i->interface == NULL)
        goto cleanup;

    i->declaration = newCktDeclarationInstance(c->declaration);
    if (i->declaration == NULL)
        goto cleanup;

    return i;

cleanup:
    destroyCktCircuit(i);
    return NULL;
    
}