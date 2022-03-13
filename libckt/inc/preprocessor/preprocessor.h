#ifndef _PREPROCESSOR_H_GUARD_
#define _PREPROCESSOR_H_GUARD_

#include "common.h"
#include "hashmap.h"
#include "linemap.h"
#include "stack.h"

typedef struct {
    CktLineMap *lm;
    CktHashMap *symbols;
    CktStack *ifStack;
    const char *old;
    const char *srcPtr;
    char *new;
    int newLen;
    int skipped;
} CktPreprocessor;

/**
 * @brief Creates a new CktPreprocessor. Returns NULL on failure.
 * 
 * @param source The source to preprocess
 * @param lm The CktLineMap for this source
 * @return CktPreprocessor * 
 */
extern CktPreprocessor *newCktPreprocessor(const char *source, CktLineMap *lm);

/**
 * @brief Deallocates the memory for a CktPreprocessor.
 * 
 * @param p A pointer to the CktPreprocessor to destroy
 */
extern void destroyCktPreprocessor(CktPreprocessor *pp);

/**
 * @brief 
 * 
 * @param pp 
 * @param c 
 * @return CktError 
 */
extern CktError appendCktPreprocessorBuffer(CktPreprocessor *pp, char c);

#endif