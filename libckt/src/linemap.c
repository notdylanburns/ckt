#include "linemap.h"

#include <stdlib.h>

CktLineMap *newCktLineMap(const char *source) {
    CktLineMap *lm = malloc(sizeof(CktLineMap));
    if (lm == NULL)
        return NULL;

    CktLineMap *head = lm;

    lm->start = 0;
    int pos = 0;
    lm->convLen = 0;
    lm->conv = NULL;

    for (const char *c = source; *c; c++, pos++) {
        if (*c == '\n') {
            lm->end = pos;
            lm->next = malloc(sizeof(CktLineMap));
            if (lm->next == NULL) {
                destroyCktLineMap(lm);
                return NULL;
            }
            
            lm = lm->next;
            lm->start = pos + 1;
        }
    }

    lm->next = NULL;
    lm->end = pos;

    return head;
}

void destroyCktLineMap(CktLineMap *lm) {
    if (lm == NULL)
        return;

    CktLineMap *next;
    while (lm != NULL) {
        next = lm->next;
        free(lm);
        lm = next;
    }
}

CktError getCktLineMapInfo(CktLineMap *lm, int pos, int *line, int *col) {
    if (lm->convLen <= pos)
        // unmapped pos
        return 1;

    pos = lm->conv[pos];

    int c = 1;

    while (lm != NULL) {
        if (lm->end >= pos) {
            *line = c;
            *col = 1 + pos - lm->start;
            return 0;
        }

        lm = lm->next;
        c++;
    }

    return 1;
}

CktError addCktLineMapConv(CktLineMap *lm, int delta) {
    int *tmp = realloc(lm->conv, ++(lm->convLen) * sizeof(int));
    if (tmp == NULL)
        return 1;

    tmp[lm->convLen - 1] = delta;
    lm->conv = tmp;

    return 0;
}