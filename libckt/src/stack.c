#include "stack.h"

#include <stdlib.h>

CktStackItem *newCktStackItem(void *value) {
    CktStackItem *si = malloc(sizeof(CktStackItem));
    if (si == NULL)
        return NULL;

    si->value = value;
    si->next = NULL;

    return si;
}

void destroyCktStackItem(CktStackItem *si, Deallocator free_data) {
    if (si == NULL)
        return;
    
    if (free_data != NULL)
        free_data(si->value);

    free(si);
}

void destroyCktStackItems(CktStackItem *si, Deallocator free_data) {
    if (si == NULL)
        return;

    CktStackItem *next;
    while (si != NULL) {
        next = si->next;
        destroyCktStackItem(si, free_data);
        si = next;
    }
}

CktStack *newCktStack(Deallocator free_data) {
    CktStack *s = malloc(sizeof(CktStack));
    if (s == NULL)
        return NULL;

    s->free_data = free_data == NULL ? &CktNoDeallocate : free_data;
    s->len = 0;
    s->top = NULL;

    return s;
}

void destroyCktStack(CktStack *s) {
    if (s == NULL)
        return;

    destroyCktStackItems(s->top, s->free_data);
    free(s);
}

CktError pushCktStack(CktStack *s, void *value) {
    CktStackItem *new = newCktStackItem(value);
    if (new == NULL)
        return 1;
    
    new->next = s->top;
    s->top = new;
    s->len++;

    return 0;
}

void *popCktStack(CktStack *s) {
    if (isCktStackEmpty(s))
        return NULL;
        
    void *data = s->top->value;
    s->top = s->top->next;

    s->len--;

    return data;
}

void *getCktStackValue(CktStack *s) {
    if (isCktStackEmpty(s))
        return NULL;

    return s->top->value;
}

int isCktStackEmpty(CktStack *s) {
    if (s->len == 0 || s->top == NULL)
        return 1;

    return 0;
}