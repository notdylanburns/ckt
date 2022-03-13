#ifndef _COMMON_H_GUARD_
#define _COMMON_H_GUARD_

typedef enum {
    LO,
    HI,
    Z,
} CktState;

typedef enum {
    INT,
    BOOL,
    IFACE,
} CktType;

typedef int CktError;

typedef struct {
    char *source;
} CktInterpreter;

typedef void (*Deallocator)(void *);

extern void setCktInterpreterError(CktInterpreter *i, CktError e);

inline void CktNoDeallocate(void *data) {
    return;
}

#endif