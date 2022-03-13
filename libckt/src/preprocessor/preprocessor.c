#include "preprocessor/preprocessor.h"

#include <stdlib.h>

CktPreprocessor *newCktPreprocessor(const char *source, CktLineMap *lm) {
    CktPreprocessor *pp = malloc(sizeof(CktPreprocessor));
    if (pp == NULL)
        return NULL;

    pp->lm = lm;

    pp->old = pp->srcPtr = source;

    pp->new = NULL;
    pp->newLen = 0;

    pp->skipped = 0;

    pp->symbols = newCktHashMap(NULL, NULL);
    if (pp->symbols == NULL) {
        free(pp);
        return NULL;
    }

    // ifStack is stack of bools representing whether or not to include bytes in preprocessed output
    pp->ifStack = newCktStack(NULL);
    if (pp->ifStack == NULL) {
        destroyCktHashMap(pp->symbols);
        free(pp);
        return NULL;
    }

    return pp;
}

void destroyCktPreprocessor(CktPreprocessor *pp) {
    if (pp == NULL)
        return;

    destroyCktHashMap(pp->symbols);
    destroyCktStack(pp->ifStack);

    free(pp->new);

    free(pp);
}

CktError appendCktPreprocessorBuffer(CktPreprocessor *pp, char c) {
    char *tmp = realloc(pp->new, pp->newLen + 2);
    if (tmp == NULL) {
        return 1;
    }

    tmp[pp->newLen++] = c;
    tmp[pp->newLen] = '\0';

    pp->new = tmp;

    if (addCktLineMapConv(pp->lm, pp->skipped))
        return 1;

    return 0;
}