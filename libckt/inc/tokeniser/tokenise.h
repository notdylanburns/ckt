#ifndef _TOKENISE_H_GUARD_
#define _TOKENISE_H_GUARD_

#include "common.h"
#include "linemap.h"
#include "token.h"

/**
 * @brief Transforms a string into a stream of CktTokens. Returns 1 on failure.
 * 
 * @param source The source string
 * @param lm A pointer to a CktLineMap 
 * @param ts A pointer to be populated with the CktTokenStream result
 * @return CktTokenStream * 
 */
extern CktError CktTokenise(const char *source, CktLineMap *lm, CktTokenStream **ts);

#endif