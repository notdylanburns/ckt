#ifndef _VALUE_H_GUARD_
#define _VALUE_H_GUARD_

#include <stdbool.h>

/**
 * @brief Tests if a string is a number.
 * 
 * @param s The string to test
 * @return bool
 */
extern bool isCktNumber(const char *s);

/**
 * @brief Tests if a string is a valid identifier.
 * 
 * @param s The string to test
 * @return bool
 */
extern bool isCktIdentifier(const char *s);

#endif