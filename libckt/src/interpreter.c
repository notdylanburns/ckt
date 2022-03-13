#include "interpreter.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linemap.h"
#include "tokeniser/token.h"
#include "tokeniser/tokenise.h"
#include "preprocessor/preprocessor.h"

CktInterpreter *newCktInterpreter() {
    CktInterpreter *i = malloc(sizeof(CktInterpreter));
    if (i == NULL)
        return NULL;

    return i;
}

void destroyCktInterpreter(CktInterpreter *i) {
    if (i == NULL)
        return;

    free(i->source);

    free(i);
}

CktError loadCktInterpreterSource(CktInterpreter *i, const char *bytes) {
    i->source = strdup(bytes);
    if (i->source == NULL)
        return 1;

    return 0;
}

CktError startCktInterpreter(CktInterpreter *i) {
    CktLineMap *lm = newCktLineMap(i->source);
    if (lm == NULL)
        return 1;

    char *preprocessed = CktPreprocess(i->source, lm);
    
    CktTokenStream *ts;
    CktToken *tk;
    if (CktTokenise(preprocessed, lm, &ts))
        // error occurred during tokenisation
        ;
    while ((tk = nextCktTokenStreamToken(ts)) != NULL) {
        printf("%d:%d %d %s (len=%d)\n", tk->line, tk->column, tk->type, tk->value, tk->len);
    }

    //CktAST *ast = CktParse(ts);
    //CktBuildEnv(i, ast);
    
    destroyCktLineMap(lm);
    destroyCktTokenStream(ts);
    //destroyCktAST(ast);
    //destroyCktEnv(env);
    return 0;

cleanup:
    destroyCktLineMap(lm);
    destroyCktTokenStream(ts);
    //destroyCktAST(ast);
    //destroyCktEnv(env);
    return 1;
}