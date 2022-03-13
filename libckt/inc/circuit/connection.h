#ifndef _CONNECTION_H_GUARD_
#define _CONNECTION_H_GUARD_

#include <stdbool.h>

#include "common.h"

#include "declaration.h"
#include "interface.h"

enum CktConnectionEndpointTypes {
    CE_PIN,     // Pin
    CE_CONST,   // HI or LO
};

/**
 * @brief Struct representing a connection endpoint within a Ckt circuit
 * 
 */
typedef struct {
    enum CktConnectionEndpointTypes t;
    union {
        CktPin *pin;
        CktState constant;
    } value;
    bool resolved;
    
} CktConnectionEndpoint;

/**
 * @brief Struct representing a connection within a Ckt circuit
 * 
 */
typedef struct {
    CktConnectionEndpoint **to;
    bool do_update;
} CktConnection;

#endif