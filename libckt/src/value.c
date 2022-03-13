#include "value.h"

#include <string.h>

bool isCktNumber(const char *s) {
#define ISBIN(d) (d == '0' || d == '1')
#define ISOCT(d) (d >= '0' && d <= '7')
#define ISDEC(d) (d >= '0' && d <= '9')
#define ISHEX(d) (ISDEC(d) || (d >= 'a' && d <= 'f') || (d >= 'A' && d <= 'F'))

    if (strlen(s) == 0)
        return false;
    else if (strlen(s) > 2 && s[0] == '0') {
        switch (s[1]) {
            case 'b':
                for (const char *c = s + 2; *c; c++)
                    if (!ISBIN(*c))
                        return false;
                break;
            
            case 'o':
                for (const char *c = s + 2; *c; c++)
                    if (!ISOCT(*c))
                        return false;
                break;

            case 'd':
                for (const char *c = s + 2; *c; c++)
                    if (!ISDEC(*c))
                        return false;
                break;

            case 'x':
                for (const char *c = s + 2; *c; c++)
                    if (!ISHEX(*c))
                        return false;
                break;

            default:
                if (!ISDEC(s[1]))
                    return false;
                
                for (const char *c = s + 2; *c; c++)
                    if (!ISDEC(*c))
                        return false;
        }
    } else {
        for (const char *c = s; *c; c++)
            if (!ISDEC(*c))
                return false;
    }

    return true;

#undef ISBIN
#undef ISOCT
#undef ISDEC
#undef ISHEX
}

bool isCktIdentifier(const char *s) {
#define ISIDENT1ST(c)  ((c >= 'a' && c <= 'z') || \
                        (c >= 'A' && c <= 'Z') || \
                        c == '_')
#define ISIDENT(c) (ISIDENT1ST(c) || (c >= '0' && c <= '9') || c == '\'')

    if (strlen(s) == 0)
        return false;
    else if (!ISIDENT1ST(s[0]))
        return false;
    else
        for (const char *c = s; *c; c++)
            if (!ISIDENT(*c))
                return false;
    
    return true;

#undef ISIDENT1ST
#undef ISIDENT
}