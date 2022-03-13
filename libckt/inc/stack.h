#ifndef _STACK_H_GUARD_
#define _STACK_H_GUARD_

#include "common.h"

struct CktStackItem {
    struct CktStackItem *next;
    void *value;
};

typedef struct CktStackItem CktStackItem;

/**
 * @brief Creates a CktStackItem. Returns NULL on failure.
 * 
 * @param value The value for this CktStackItem
 * @return CktStackItem * 
 */
extern CktStackItem *newCktStackItem(void *value);

/**
 * @brief Deallocates the memory for a CktStackItem.
 * 
 * @param si A pointer to the CktStackItem to destroy
 * @param free_data A callback function specifying how to free the stack item data. If NULL, deallocation doesn't occur.
 */
extern void destroyCktStackItem(CktStackItem *si, Deallocator free_data);

/**
 * @brief Deallocates the memory for a linked list of CktStackItems.
 * 
 * @param si A pointer to the first CktStackItem in the linked list to destroy
 * @param free_data A callback function specifying how to free the stack items. If NULL, deallocation doesn't occur.
 */
extern void destroyCktStackItems(CktStackItem *si, Deallocator free_data);

typedef struct {
    CktStackItem *top;
    int len;
    Deallocator free_data;
} CktStack;

/**
 * @brief Creates a new CktStack. Returns NULL on failure.
 * 
 * @param free_data A callback function specifying how to free the stack items. If NULL, deallocation doesn't occur.
 * @return CktStack * 
 */
extern CktStack *newCktStack(Deallocator free_data);

/**
 * @brief Deallocates the memory for a CktStack.
 * 
 * @param s A pointer to the stack to destroy
 */
extern void destroyCktStack(CktStack *s);

/**
 * @brief Pushes a value onto a CktStack. Returns 1 on failure.
 * 
 * @param s A pointer to the CktStack to push
 * @param value The value to push
 * @return CktError 
 */
extern CktError pushCktStack(CktStack *s, void *value);

/**
 * @brief Pops a value from a CktStack. Returns NULL if the CktStack is empty.
 * 
 * @param s A pointer to the CktStack to pop
 * @return void * 
 */
extern void *popCktStack(CktStack *s);

/**
 * @brief Returns the value at the top of the CktStack without popping it, or NULL if the CktStack is empty.
 * 
 * @param s A pointer to the CktStack
 * @return void * 
 */
extern void *getCktStackValue(CktStack *s);

/**
 * @brief Returns 0 if not empty, else 1.
 * 
 * @param s A pointer to the CktStack
 * @return int 
 */
extern int isCktStackEmpty(CktStack *s);

#endif