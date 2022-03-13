#include "preprocessor/macro.h"

#include <stdlib.h>

#include "stack.h"

struct __macro_table_ent {
    const char *m;                                      // the macro name
    CktError (*f)(CktPreprocessor *, int, char **);     // the macro function
    int i;                                              // whether or not to ignore this macro in a if block
};

static const struct __macro_table_ent MACROS[] = {
#define MACRO(n) &__MACRO_##n
    { "use",    MACRO(use),     1 },
    { "import", MACRO(import),  1 },
    { "ifdef",  MACRO(ifdef),   0 },
    { "ifndef", MACRO(ifndef),  0 },
    { "else",   MACRO(else),    0 },
    { "endif",  MACRO(endif),   0 },
    { "define", MACRO(define),  1 },
#undef MACRO
};

#define MACRO(n) static CktError __MACRO_##n##(CktPreprocessor *pp, int argc, char **argv)

MACRO(use) {

}

MACRO(import) {

}

MACRO(ifdef) {
    if (argc < 1)
        // too few arguments
        ;
    else if (argc > 1)
        // too many arguments
        ;
    
    //if (!isSymbol(argv[0]))
        // expected symbol
        //;

    if (getCktHashMapItem(pp->symbols, argv[0], NULL)) {
        // symbol undefined, so we skip
        if (pushCktStack(pp->ifStack, (void *)1))
            return 1;
    } else {
        // symbol defined, so we don't skip
        if (pushCktStack(pp->ifStack, (void *)0))
            return 1;
    }

    return 0;
}

MACRO(ifndef) {
    if (argc < 1)
        // too few arguments
        return 1;
    else if (argc > 1)
        // too many arguments
        return 1;
    
    //if (!isSymbol(argv[0]))
        // expected symbol
        //;

    if (getCktHashMapItem(pp->symbols, argv[0], NULL)) {
        // symbol undefined, so we don't skip
        if (pushCktStack(pp->ifStack, (void *)0))
            return 1;
    } else {
        // symbol defined, so we skip
        if (pushCktStack(pp->ifStack, (void *)1))
            return 1;
    }

    return 0;
}

MACRO(else) {
    if (argc > 0)
        // too many arguments
        return 1;

    if (isCktStackEmpty(pp->ifStack))
        // else missing if(n)def
        return 1;

    int skip = (int)popCktStack(pp->ifStack);
    if (pushCktStack(pp->ifStack, (void *)!skip))
        return 1;

    return 0;
}

MACRO(endif) {
    if (argc > 0)
        // too many arguments
        return 1;

    if (isCktStackEmpty(pp->ifStack))
        // endif missing if(n)def
        return 1;

    popCktStack(pp->ifStack);

    return 0;
}

MACRO(define) {
    if (argc < 1)
        // too few arguments
        return 1;
    else if (argc > 1)
        // too many arguments
        return 1;
    
    //if (!isSymbol(argv[0]))
        // expected symbol
        //;

    if (addCktHashMapItem(pp->symbols, argv[0], NULL))
        // internal error
        return 1;

    return 0;
}

MACRO(undef) {
    if (argc < 1)
        // too few arguments
        return 1;
    else if (argc > 1)
        // too many arguments
        return 1;
    
    //if (!isSymbol(argv[0]))
        // expected symbol
        //;

    // undef-ing an undefined symbol is a no-op, 
    // so we don't care about the return value here
    removeCktHashMapItem(pp->symbols, argv[0]);

    return 0;
}

#undef MACRO