#include "tokeniser/token.h"

#include <stdlib.h>
#include <string.h>

#include "value.h"

CktTokenType getCktTokenType(const char *s) {
#define TK(a, t) if (!strcmp(s, a)) { return CKT_TK_##t; }
    TK(".", PERIOD);
    TK(",", COMMA);
    TK(":", COLON);
    TK(";", SEMICOLON);
    TK("(", LPAREN);
    TK(")", RPAREN);
    TK("[", LSQUARE);
    TK("]", RSQUARE);
    TK("{", LCURLY);
    TK("}", RCURLY);
    TK("<", LANGLE);
    TK(">", RANGLE);
    TK("+", PLUS);
    TK("-", MINUS);
    TK("*", MULTIPLY);
    TK("/", DIVIDE);
    TK("^", EXPONENT);
    TK("circuit", KW_CIRCUIT);
    TK("interface", KW_INTERFACE);
    TK("declare", KW_DECLARE);
    TK("connect", KW_CONNECT);
    TK("to", KW_TO);
    TK("input", KW_INPUT);
    TK("output", KW_OUTPUT);
    TK("transput", KW_TRANSPUT);
    TK("hi", KW_HI);
    TK("lo", KW_LO);
#undef TK

    if (isCktNumber(s))
        return CKT_TK_NUMBER;
    else if (isCktIdentifier(s))
        return CKT_TK_IDENT;
    else
        return CKT_TK_UNKNOWN;

}

CktToken *newCktToken(const char *value, int line, int column) {
    CktToken *tk = malloc(sizeof(CktToken));
    if (tk == NULL)
        return NULL;

    tk->value = strdup(value);
    if (tk->value == NULL) {
        free(tk);
        return NULL;
    }

    tk->type = getCktTokenType(value);
    tk->len = strlen(value);
    tk->line = line;
    tk->column = column;
    
    tk->next = tk->prev = NULL;

    return tk;
}

void destroyCktToken(CktToken *t) {
    if (t == NULL)
        return;

    free(t->value);
    free(t);
}

void destroyCktTokens(CktToken *t) {
    while (t->next != NULL) {
        t = t->next;
        destroyCktToken(t->prev);
    }

    destroyCktToken(t);
}

CktTokenStream *newCktTokenStream() {
    CktTokenStream *ts = malloc(sizeof(CktTokenStream));
    if (ts == NULL)
        return NULL;

    ts->cur = 0;
    ts->len = 0;
    ts->tk = NULL;
    ts->head = NULL;

    return ts;
}

void destroyCktTokenStream(CktTokenStream *ts) {
    destroyCktTokens(ts->head);
    free(ts);
}

CktError addCktTokenStreamToken(CktTokenStream *ts, const char *value, int line, int column) {
    CktToken *tk = newCktToken(value, line, column);
    if (tk == NULL)
        return 1;
    
    if (ts->head == NULL) {
        ts->len = 1;
        ts->head = tk;
        return 0;
    }

    ts->len += 1;

    CktToken *prev = ts->head;
    while (prev->next != NULL)
        prev = prev->next;

    prev->next = tk;
    tk->prev = prev;

    return 0;
}

CktToken *nextCktTokenStreamToken(CktTokenStream *ts) {
    if (ts->tk == NULL) {
        ts->tk = ts->head;
        ts->cur = 0;
        return ts->head;
    }

    if (ts->tk == NULL)
        return NULL;

    ts->cur += 1;
    ts->tk = ts->tk->next;
    return ts->tk;
}

CktToken *peekCktTokenStreamToken(CktTokenStream *ts) {
    if (ts->tk == NULL) {
        return ts->head;
    }

    if (ts->tk == NULL)
        return NULL;

    return ts->tk->next;
}