#include "tokeniser/tokenise.h"

#include <string.h>

static const char *DELIMETERS = " \n\r\t.,:;()[]{}<>-+/*";

CktError CktTokenise(const char *source, CktLineMap *lm, CktTokenStream **ts) {
    CktTokenStream *t = newCktTokenStream();
    if (t == NULL)
        return 1;

    const char *c = source;
    int len = strlen(source);

    int pos, line, col;

    while ((pos = c - source) < len) {
        int dist = strcspn(c, DELIMETERS);
        if (dist == 0) {
            if (*c != ' ' && *c != '\n' && *c != '\r' && *c != '\t') {
                char buf[] = {*c, '\0'};
                if (getCktLineMapInfo(lm, pos, &line, &col)) {
                    // error - shouldn't ever occur
                    goto cleanup;
                } else if (addCktTokenStreamToken(t, buf, line, col)) {
                    //error
                    goto cleanup;
                }
            }
            c++;
        } else {
            char buf[dist + 1];
            buf[dist] = '\0';

            strncpy(buf, c, dist);
            if (getCktLineMapInfo(lm, pos, &line, &col)) {
                // error - shouldn't ever occur
                goto cleanup;
            } else if (addCktTokenStreamToken(t, buf, line, col)) {
                //error
                goto cleanup;
            }

            c += dist;
        }
    }

    *ts = t;
    return 0;

cleanup:
    destroyCktTokenStream(t);
    *ts = NULL;
    return 1;
}