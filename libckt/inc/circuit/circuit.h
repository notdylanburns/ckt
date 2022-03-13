#ifndef _CIRCUIT_H_GUARD_
#define _CIRCUIT_H_GUARD_

#include <stdbool.h>

#include "hashmap.h"

#include "declaration.h"
#include "interface.h"
#include "pin.h"

/*
 * Struct representing a Ckt circuit
 */
typedef struct {
    char *name;
    CktInterface *interface;
    CktDeclaration *declaration;
    CktHashMap *parameters;
    bool is_template;  

    bool do_update;
} CktCircuit;

/**
 * @brief Creates a new CktCircuit. Returns NULL on failure.
 * 
 * @param name The name of the CktCircuit
 * @param params The parameters of this circuit
 * @return CktCircuit * 
 */
extern CktCircuit *newCktCircuit(const char *name, CktHashMap *params);

/**
 * @brief Deallocates the memory for the specified CktCircuit
 * 
 * @param c A pointer to the CktCircuit to destroy
 */
extern void destroyCktCircuit(CktCircuit *c);

/**
 * @brief Adds a pin to the specified CktCircuit. Returns 1 on error.
 * 
 * @param c A pointer to the CktCircuit
 * @param pin_name The name of the pin to add
 * @param dir The pin direction
 * @param width The width of this pin
 * @return int 
 */
extern int addCktCircuitPin(CktCircuit *c, const char *pin_name, CktPinDirection dir, int width);

/**
 * @brief Appends a CktInterface to the CktCircuit's interface. Returns 1 on error. 
 * 
 * @param c A pointer to the CktCircuit
 * @param i A pointer to the CktInterface
 * @param params A hashmap specifying the parameters of this interface 
 * @return int 
 */
extern int addCktCircuitInterface(CktCircuit *c, CktInterface *i, CktHashMap *params);

/**
 * @brief Create an instance of a CktCircuit template. Returns NULL on failure.
 * 
 * @param c The CktCircuit template to use
 * @return CktCircuit * 
 */
extern CktCircuit *createCktCircuitInstance(CktCircuit *c);

#endif