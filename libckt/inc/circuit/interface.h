#ifndef _INTERFACE_H_GUARD_
#define _INTERFACE_H_GUARD_

#include "hashmap.h"
#include "pin.h"

/**
 * @brief Struct representing a Ckt circuit interface
 * 
 */
typedef struct {
    CktPin *pins;          // Linked list of pins for constructing instances
    CktHashMap *interface; // Hashmap of pins
} CktInterface;

/**
 * @brief Creates a new CktInterface. Returns NULL on failure.
 * 
 * @return CktInterface * 
 */
extern CktInterface *newCktInterface();

/**
 * @brief Deallocates the memory for the specified CktInterface.
 * 
 * @param i A pointer to the CktInterface to deallocate
 */
extern void destroyCktInterface(CktInterface *i);

/**
 * @brief Adds a CktPin to a CktInterface template. Returns 1 on error.
 * 
 * @param i A pointer to the CktInterface to add the CktPin to
 * @param name The name of the pin
 * @param dir The pin direction
 * @param width The width of this pin
 * @return int 
 */
extern int addCktInterfacePin(CktInterface *i, const char *name, CktPinDirection dir, int width);

/**
 * @brief Creates an instance of a CktInterface from the specified template. Returns NULL on failure. 
 * 
 * @param i The template CktInterface
 * @return CktInterface *
 */
extern CktInterface *createCktInterfaceInstance(CktInterface *i);

#endif