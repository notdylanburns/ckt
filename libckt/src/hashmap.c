#include "hashmap.h"

#include <stdlib.h>
#include <string.h>

static unsigned int MurmurHash2(const char *key, int len) {
	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	unsigned int h = HASHMAP_SEED ^ len;

	const unsigned char *data = (const unsigned char *)key;

	while(len >= 4) {
		unsigned int k = *(unsigned int *)data;

		k *= m; 
		k ^= k >> r; 
		k *= m; 
		
		h *= m; 
		h ^= k;

		data += 4;
		len -= 4;
	}

	switch(len) {
        case 3: 
            h ^= data[2] << 16;
        case 2: 
            h ^= data[1] << 8;
        case 1: 
            h ^= data[0];
            h *= m;
	}

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h & (MAX_BUCKETS - 1);
}

CktHashMap *newCktHashMap(unsigned int (*hashf)(const char *, int), Deallocator free_data) {
    CktHashMap *h = malloc(sizeof(CktHashMap));
    if (h == NULL)
        return NULL;

    for (int i = 0; i < MAX_BUCKETS; i++)
        h->buckets[i] = NULL;

    h->hashf = (hashf == NULL) ? &MurmurHash2 : hashf;
    h->free_data = (free_data == NULL) ? &CktNoDeallocate : free_data;

    return h;
}

static struct __ckt_hashmap_bucket *new_bucket(char *key, void *data) {
    struct __ckt_hashmap_bucket *b = malloc(sizeof(struct __ckt_hashmap_bucket));
    if (b == NULL)
        return NULL;
    
    b->key = strdup(key);
    if (b->key == NULL) {
        free(b);
        return NULL;
    }

    b->data = data;
    b->next = NULL;

    return b;
}

static void destroy_bucket_ll(struct __ckt_hashmap_bucket *ll, void (*free_data)(void *)) {
    if (ll == NULL)
        return;

    destroy_bucket_ll(ll->next, free_data);

    free_data(ll->data);
    free(ll->key);
    free(ll);
}

void destroyCktHashMap(CktHashMap *h) {
    if (h == NULL)
        return;

    for (int i = 0; i < MAX_BUCKETS; i++)
        destroy_bucket_ll(h->buckets[i], h->free_data);

    free(h);
}

CktError addCktHashMapItem(CktHashMap *h, char *key, void *value) {
    unsigned int index = h->hashf(key, strlen(key)) & (MAX_BUCKETS - 1);
    struct __ckt_hashmap_bucket *n, *b = h->buckets[index];
    if (b == NULL) {
        n = new_bucket(key, value);
        if (n == NULL)
            return 1;
        
        h->buckets[index] = n;
        return 0;
    } else {
        while (b->next != NULL) {
            if (!strcmp(b->key, key)) {
                h->free_data(b->data);
                b->data = value;
            }
            b = b->next;
        }

        n = new_bucket(key, value);
        if (n == NULL)
            return 1;

        b->next = n;
        return 0;
    }
}

CktError getCktHashMapItem(CktHashMap *h, char *key, void **value) {
    unsigned int index = h->hashf(key, strlen(key)) & (MAX_BUCKETS - 1);
    struct __ckt_hashmap_bucket *b = h->buckets[index];
    while (b != NULL) {
        if (!strcmp(b->key, key)) {
            if (value != NULL)
                *value = b->data;
            return 0;
        }

        b = b->next;
    }

    return 1;
}

CktError removeCktHashMapItem(CktHashMap *h, char *key) {
    unsigned int index = h->hashf(key, strlen(key)) & (MAX_BUCKETS - 1);
    struct __ckt_hashmap_bucket *p = NULL, *b = h->buckets[index];
    while (b != NULL) {
        if (!strcmp(b->key, key)) {
            if (p == NULL)
                h->buckets[index] = b->next;
            else
                p->next = b->next;

            return 0;
        }

        p = b;
        b = b->next;
    }

    return 1;
}