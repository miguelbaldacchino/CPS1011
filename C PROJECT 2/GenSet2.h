#ifndef GENSET_H
#define GENSET_H

#include <stdbool.h>
#include <stddef.h>

typedef struct GenSet GenSet;

GenSet* initSet(size_t elementSize, int (*compare)(const void*, const void*), void (*display)(const void*),
                void (*filewrite)(const void*, FILE*));

void deinitSet(GenSet* set);
bool isEmptySet(GenSet* set);

void addToSet(GenSet* set, const void* element);
void displaySet(const GenSet* set);
size_t countSet(const GenSet* set);
bool isSubsetSet(const GenSet* setA, const GenSet* setB);
GenSet* unionSet(const GenSet* setA, const GenSet* setB);
GenSet* intersectSet(const GenSet* setA, const GenSet* setB);
GenSet* diffSet(const GenSet* setA, const GenSet* setB);
void export(const GenSet* set, const char* filename);


#endif // GENSET_H
