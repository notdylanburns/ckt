#ifndef _LINEMAP_H_GUARD_
#define _LINEMAP_H_GUARD_

#include "common.h"

struct CktLineMap {
    int start;
    int end;
    struct CktLineMap *next;
    int *conv; // a list of ints specifying the difference in position between the preprocessed source and the original source 
    int convLen;
};

typedef struct CktLineMap CktLineMap;

/**
 * @brief Create a new CktLineMap from the specified source string. Returns NULL on failure.
 * 
 * @param source The source string from which to create the CktLineMap
 * @return CktLineMap * 
 */
extern CktLineMap *newCktLineMap(const char *source);

/**
 * @brief Deallocates the memory for the specified CktLineMap.
 * 
 * @param lm A pointer to the CktLineMap to destroy
 */
extern void destroyCktLineMap(CktLineMap *lm);

/**
 * @brief Gets the line and column for a given position in the source. Returns 1 on error.
 * 
 * @param lm A pointer to the CktLineMap to use
 * @param pos The byte position in the source string
 * @param line A pointer to an integer to be populated with the current line
 * @param col A pointer to an integer to be populated with the current column
 * @return CktError 
 */
extern CktError getCktLineMapInfo(CktLineMap *lm, int pos, int *line, int *col);

/**
 * @brief Adds a conversion to the CktLineMap. Returns 1 on failure.
 * 
 * @param lm A pointer to the CktLineMap to modify
 * @param delta 
 * @return CktError 
 */
extern CktError addCktLineMapConv(CktLineMap *lm, int delta);

#endif