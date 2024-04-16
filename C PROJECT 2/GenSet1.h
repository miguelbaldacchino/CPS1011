#ifndef GENSET_H
#define GENSET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SUCCESS 0
#define NULL_POINTER_ERROR 1
#define ELEMENT_EXISTS_ERROR 2
#define DEALLOCATED_ERROR 3

typedef struct {
    size_t elementSize;
    size_t length;
    void **elements;
    bool deallocation;  // flag for deinitSetInt(), shows if been deallocated
    bool isInt; // flag for type, is integer or isnt
} GenSet_t;

GenSet_t *initSet(size_t elementSize); // return NULL if allocation failure (set/elements)
int deinitSet(GenSet_t *set); // Follows Error Codes
bool isEmptySet(GenSet_t *set); // true: dealloc/empty, false: not empty
bool isSubsetSet(GenSet_t *set1, GenSet_t *set2); // NULL: dealloc/NULL sets, diff set types, true/false
int addToSet(GenSet_t *set, const void *element); // Follows Error Codes
int displaySet(GenSet_t *set); // Follows Error Codes
int countSet(GenSet_t *set); // Follows Error Codes
GenSet_t *unionSet(GenSet_t *set1, GenSet_t *set2); // NULL: dealloc/NULL sets, diff set types
GenSet_t *intersectSet(GenSet_t *set1, GenSet_t *set2); // NULL: dealloc/NULL sets, diff set types
GenSet_t *diffSet(GenSet_t *set1, GenSet_t *set2); // NULL: dealloc/NULL sets, diff set types

#endif // GENSET_H
