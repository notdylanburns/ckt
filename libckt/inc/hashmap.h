#ifndef _HASHMAP_H_GUARD_
#define _HASHMAP_H_GUARD_

#define MAX_BUCKETS (1 << 12) // 2 ^ 10
#define HASHMAP_SEED (unsigned int)1414158098

#include "common.h"

struct __ckt_hashmap_bucket {
    char *key;
    void *data;
    struct __ckt_hashmap_bucket *next;
};

typedef struct {
    struct __ckt_hashmap_bucket *buckets[MAX_BUCKETS];
    unsigned int (*hashf)(const char *, int);
    Deallocator free_data;
} CktHashMap;

/**
 * @brief Creates a new CktHashMap. Returns NULL on failure.
 * 
 * @param hashf The hashing function for this CktHashMap. If NULL, the default is used.
 * @param free_data A callback function specifying how to free the hashmap items. If NULL, deallocation doesn't occur.
 * @return CktHashMap * 
 */
extern CktHashMap *newCktHashMap(unsigned int (*hashf)(const char *, int), Deallocator free_data);

/**
 * @brief Deallocates the memory for the specified CktHashMap 
 * 
 * @param h A pointer to the CktHashMap to destroy
 */
extern void destroyCktHashMap(CktHashMap *h);

/**
 * @brief Adds an item to the specified CktHashMap. Returns 1 on error.
 * 
 * @param h A pointer to the CktHashMap
 * @param key The key for the item
 * @param value The value associated with the key
 * @return CktError
 */
extern CktError addCktHashMapItem(CktHashMap *h, char *key, void *value);

/**
 * @brief Get an item from a CktHashMap. Returns 1 on error.
 * 
 * @param h A pointer to the CktHashMap
 * @param key The key for the item
 * @param value A pointer to be populated with the data from the hashmap
 * @return CktError 
 */
extern CktError getCktHashMapItem(CktHashMap *h, char *key, void **value);

/**
 * @brief Removes an item from a CktHashMap. Returns 1 on error.
 * 
 * @param h A pointer to the CktHashMap
 * @param key The key for the item to be removed
 * @return CktError 
 */
extern CktError removeCktHashMapItem(CktHashMap *h, char *key);

#endif