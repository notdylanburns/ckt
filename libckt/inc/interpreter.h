#ifndef _INTERPRETER_H_GUARD_
#define _INTERPRETER_H_GUARD_

#include "common.h"

/**
 * @brief Creates a new CktInterpreter. Returns NULL on failure.
 * 
 * @return CktInterpreter * 
 */
extern CktInterpreter *newCktInterpreter();

/**
 * @brief Deallocates the memory for a CktInterpreter.
 * 
 * @param i A pointer to the CktInterpreter to destroy
 */
extern void destroyCktInterpreter(CktInterpreter *i); 

/**
 * @brief Load the bytes to interpret into the CktInterpreter. Returns 1 on failure.
 * 
 * @param i A pointer to the interpreter
 * @param bytes The bytes to load
 * @return CktError 
 */
extern CktError loadCktInterpreterSource(CktInterpreter *i, const char *bytes);

/**
 * @brief Begins execution of the interpreter. Returns the exit code of the interpreter.
 * 
 * @param i A pointer to the CktInterpreter to start
 * @return CktError 
 */
extern CktError startCktInterpreter(CktInterpreter *i);

#endif