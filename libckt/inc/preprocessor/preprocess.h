#ifndef _PREPROCESS_H_GUARD_
#define _PREPROCESS_H_GUARD_

#include "../linemap.h"

/**
 * @brief Preprocesses a source string: removing comments and processing macros. Returns NULL on failure.
 * 
 * @param source The source string to operate on
 * @param lm A pointer to the CktLineMap 
 * @return char * 
 */
extern char *CktPreprocess(const char *source, CktLineMap *lm);

#endif