#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#include "GenSet2.h"

// generic set data structure, where user-defined data types can be used.
// displaying of elements func to be supplied by user, since data type is user-defined
// comparing of elements func to be supplied by user, since data type is user-defined

// use of function pointers needed for these two, for library flexibility

struct GenSet{
    void** elements; // a pointer to array of void pointers, stores addresses of elements in set.
    // elements is a pointer to a pointer void, hence the 'void**', (pointer to a pointer)
    // the ** is used for flexibility w handling diff data types
    size_t length; // size_t -> bytes
    size_t elementSize;
    bool deallocation; // flag for deinitSet()

    int (*compare)(const void*, const void*);
    void (*display)(const void*);
    void (*filewrite)(const void*, FILE*);

};
void* getMemoryLocation(const GenSet* set, size_t index) {
    return (char*)set->elements + index * set->elementSize;
    // pointer to memory of i-th element, better explained in personal notes
    // char* is used to turn set->elements into bytes
    // char* for better pointer arithmetic
    // (char*)set->elements -> casted pointer   set->elementSize * set->length -> offset eg. sizeof(int) * set->length

}

GenSet* initSet(size_t elementSize, int (*compare)(const void*, const void*), void (*display)(const void*),
                void (*filewrite)(const void*, FILE*)) {
    GenSet* newSet = (GenSet*)malloc(sizeof(GenSet));

    if (newSet == NULL) {
        // memory allocation failure
        return NULL;
    }

    newSet->elements = NULL;
    newSet->length = 0;
    newSet->elementSize = elementSize;
    newSet->deallocation = false;
    newSet->compare = compare;
    newSet->display = display;
    newSet->filewrite = filewrite;

    return newSet;
}

void deinitSet(GenSet* set) {
    if (set == NULL) {
        return;
    }
    set->deallocation = true;

    free(set->elements);
    free(set);
}


bool isEmptySet(GenSet* set) {
    if (set == NULL || set->deallocation) {
        return true;
    }
    return (set->length == 0);
}

bool isElementInSet(const GenSet* set, const void* element) {
    for (size_t i = 0; i < set->length; i++) {
        if (set->compare(element, getMemoryLocation(set, i)) == 0) {
            // checks to see if a-b = 0 essentially

            return true; // element found
        }
    }
    return false;
}

void addToSet(GenSet* set, const void* element) {
    // error handling to be added later

    if (isElementInSet(set, element)) {
        return;
    }

    // calculating new elements memory location ie. adding offset to caster pointer
    void* elementMemoryLocation = malloc(set->elementSize);
    if (!elementMemoryLocation) {
        // handle memory allocation failure
        return;
    }

    void* newElements = realloc(set->elements, set->elementSize * (set->length + 1)); // as in 2a
    if (newElements == NULL) {
        // memory allocation failure
        free(elementMemoryLocation);
        return;
    }
    set->elements = newElements;
    memcpy(elementMemoryLocation, element, set->elementSize);

    void* setElementMemoryLocation = getMemoryLocation(set, set->length);
    memcpy(setElementMemoryLocation, elementMemoryLocation, set->elementSize);

    set->length = set->length + 1;

    // qsort(set->elements, set->length, set->elementSize, set->compare);
    free(elementMemoryLocation);
}

void displaySet(const GenSet* set) {
    if (set == NULL || set->deallocation) {
        return;
    }

    printf("Set elements: { ");

    for (size_t i = 0; i < set->length; i++) {
        // using function pointer
        set->display(getMemoryLocation(set, i));
        if (i < set->length - 1) {
            printf(", ");
        }
    }
    printf(" }\n");
}

size_t countSet(const GenSet* set) {
    if (set == NULL || set->deallocation) {
        return 0;
    }
    return set->length;
}

bool isSubsetSet(const GenSet* setA, const GenSet* setB) {
    if (setA == NULL || setB == NULL || setA->deallocation || setB->deallocation) {
        return false;
    }
    for (size_t i = 0; i < setA->length; i++) {
        if (!isElementInSet(setB, getMemoryLocation(setA, i))) {
            return false;
        }
    }
    // all elements of a in b, hence a subset b
    return true;
}

GenSet* unionSet(const GenSet* setA, const GenSet* setB) {
    if (setA == NULL || setB == NULL || setA->deallocation || setB->deallocation) {
        return false;
    }
    if (setA->elementSize != setB->elementSize || setA->compare != setB->compare || setA->display != setB->display) {
        // sets not of same type
        return NULL;
    }

    GenSet* unionSet = initSet(setA->elementSize, setA->compare, setA->display, setA->filewrite);

    // add of setA
    for (size_t i = 0; i < setA->length; i++) {
        addToSet(unionSet, getMemoryLocation(setA, i));
    }

    // add of setB
    for (size_t i = 0; i < setB->length; i++) {
        addToSet(unionSet, getMemoryLocation(setB, i));
    }
    return unionSet;
}

GenSet* intersectSet(const GenSet* setA, const GenSet* setB) {
    if (setA == NULL || setB == NULL || setA->deallocation || setB->deallocation) {
        return false;
    }
    if (setA->elementSize != setB->elementSize || setA->compare != setB->compare || setA->display != setB->display) {
        // sets not of same type
        return NULL;
    }

    GenSet* intersectionSet = initSet(setA->elementSize, setA->compare, setA->display, setA->filewrite);

    for (size_t i = 0; i < setA->length; i++) {
        if (isElementInSet(setB, getMemoryLocation(setA, i))){
            addToSet(intersectionSet, getMemoryLocation(setA, i));
        }
    }
    return intersectionSet;
}

GenSet* diffSet(const GenSet* setA, const GenSet* setB) {
    if (setA == NULL || setB == NULL || setA->deallocation || setB->deallocation) {
        return false;
    }
    if (setA->elementSize != setB->elementSize || setA->compare != setB->compare || setA->display != setB->display) {
        // sets not of same type
        return NULL;
    }

    GenSet* diffSet = initSet(setA->elementSize, setA->compare, setA->display, setA->filewrite);

    for (size_t i = 0; i < setA->length; i++) {
        if (!isElementInSet(setB, getMemoryLocation(setA, i))) {
            addToSet(diffSet, getMemoryLocation(setA, i));
        }
    }
    return diffSet;
}

void export(const GenSet* set, const char* filename) {
    if (set == NULL || set->deallocation) {
        return;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    for (size_t i = 0; i < set->length; i++) {
        set->filewrite(getMemoryLocation(set, i), filename);
    }
    fclose(file);
}


