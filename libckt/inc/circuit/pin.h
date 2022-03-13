#ifndef _PIN_H_GUARD_
#define _PIN_H_GUARD_

#include "common.h"

typedef enum {
    INPUT,
    OUTPUT,
    TRANSPUT,
} CktPinDirection;

/**
 * @brief Struct representing a Ckt circuit pin
 * 
 */
struct CktPin {
    char *name;
    CktState state;
    CktPinDirection direction;
    struct CktPin *next;
    int width;
};

typedef struct CktPin CktPin;

/**
 * @brief Creates a new CktPin. Returns NULL on failure.
 * 
 * @param name The name of the pin
 * @param dir The pin direction
 * @param width The width of this pin
 * @return CktPin * 
 */
extern CktPin *newCktPin(const char *name, CktPinDirection dir, int width);

/**
 * @brief Deallocates the memory for a CktPin.
 * 
 * @param p A pointer to the CktPin to deallocate
 */
extern void destroyCktPin(CktPin *p);

/**
 * @brief Deallocates the memory for a linked list of CktPins.
 * 
 * @param p A pointer to the first CktPin in the linked list
 */
extern void destroyCktPins(CktPin *p);

/**
 * @brief Set the state of a CktPin and notify all connections.
 * 
 * @param p The pin to set
 * @param s The new state of the pin
 */
extern void setCktPinState(CktPin *p, CktState s);

#endif