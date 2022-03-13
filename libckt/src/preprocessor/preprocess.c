#include "preprocessor/preprocess.h"

#include <stdlib.h>

#include "preprocessor/macro.h"
#include "preprocessor/preprocessor.h"

static inline char isFirstCharOnLine(const char *c, const char *source) {
    if (c == source)
        return 1;

    for (c--; c > source; c--) {
        switch (*c) {
            case ' ':
            case '\t':
            case '\r':
                continue;

            case '\n':
                return 1;

            default:
                return 0;
        }
    }

    return 0;
}

char *CktPreprocess(const char *source, CktLineMap *lm) {

    CktPreprocessor *pp = newCktPreprocessor(source, lm);
    if (pp == NULL)
        return NULL;

    for (; *(pp->srcPtr); pp->srcPtr++) {
        switch (*(pp->srcPtr)) {
            case '@':
                pp->skipped++;
                // line is macro
                if (isFirstCharOnLine(pp->srcPtr, source)) {
                    if (CktParseMacro(pp))
                        // error while parsing macro
                        ;
                } else {
                    // error, @ must appear as first character on line
                }
                continue;

            case '/':
                if (*(pp->srcPtr + 1) == '/') {
                    pp->skipped += 2;
                    pp->srcPtr++;
                    // Single line comment
                    if (*(++pp->srcPtr))
                        for (; *(pp->srcPtr) && *(pp->srcPtr) != '\n'; pp->srcPtr++)
                            pp->skipped++;
                    pp->srcPtr--;
                } else if (*(pp->srcPtr + 1) == '*') {
                    pp->skipped += 2;
                    pp->srcPtr++;
                    // Multi line comment
                    for (; *(pp->srcPtr); pp->srcPtr++) {
                        pp->skipped++;
                        if (*(pp->srcPtr) == '*' && *(pp->srcPtr + 1) == '/') {
                            pp->skipped++;
                            pp->srcPtr++;
                            break;
                        }
                    }
                }

                continue;

            default:
                if (appendCktPreprocessorBuffer(pp, *(pp->srcPtr))) {
                    destroyCktPreprocessor(pp);
                    return NULL;
                }
                continue;
        }
    }

    char *retVal = strdup(pp->new);
    destroyCktPreprocessor(pp);

    return retVal;
}