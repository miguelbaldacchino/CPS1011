#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "GenSet1.h"

bool ElementInSet(const void *element, GenSet_t *set) { // determines if element in set
    for (int i = 0; i < set->length; i++) {
        if (set->elementSize == sizeof(int) && memcmp(set->elements[i], element, set->elementSize) == 0) {
            return true;
        } else if (set->elementSize == sizeof(char[64]) && strcmp((const char *)set->elements[i], (const char *)element) == 0) {
            return true;
        }
    }
    return false;
}

GenSet_t *initSet(size_t elementSize) { // returns -> NULL: Allocation failure (structure or elements), newSet
    if (elementSize != sizeof(int) && elementSize != sizeof(char[64])) { // check for type, only int and char[64]
        return NULL; // Invalid element size
    }

    GenSet_t *newSet = malloc(sizeof(GenSet_t));  // Dynamic memory ie. heap used

    if (newSet == NULL) {
        return NULL;
    }

    newSet->length = 0; // Initially an empty set
    newSet->elements = malloc(sizeof(void *) * 1); // Space allocated for a single value
    newSet->elementSize = elementSize; // data type assign

    if (newSet->elements == NULL) {
        // allocation failure for elements
        deinitSet(newSet);
        return NULL;
    }

    newSet->deallocation = false; // flag for deininSet(), used as validation/check in other functions
    if (newSet->elementSize == sizeof(int)) { // flag to see if set is of type int/char[64]
        newSet->isInt = true; // type int
    }
    else if (newSet->elementSize == sizeof(char[64])) {
        newSet->isInt = false; // type char[64]
    }
    return newSet;
}

int deinitSet(GenSet_t *set) { // Follows Error Codes
    if (set == NULL) {
        return NULL_POINTER_ERROR; // Avoid dereferencing a null pointer
    }

    for (int i = 0; i < set->length; i++) {
        free(set->elements[i]);
    }
// free every dynamically stored memory
    free(set->elements);
    set->deallocation = true;
    free(set);
    return SUCCESS;
}

bool isEmptySet(GenSet_t *set) { // true: dealloc/empty, false: not empty
    if (set->length == 0 || set->deallocation) {
        // set empty/has been deallocated
        return true;
    } else {
        //set not empty
        return false;
    }
}

bool isSubsetSet(GenSet_t *set1, GenSet_t *set2) { // NULL: dealloc/NULL sets, diff set types, true/false
    if (set1->deallocation || set2->deallocation) {
        // dealloc check
        return false;
    }
    if (set1 == NULL || set2 == NULL) {
        // NULL check
        return false;
    }

    if (set1->isInt != set2->isInt) {
        // type check
        return false;
    }

    for (int i = 0; i < set1->length; i++) {
        if (!ElementInSet(set1->elements[i], set2)) {
            return false;
        }
    }

    return true;
}

int addToSet(GenSet_t *set, const void *element) { // Follows Error Codes
    if (set->deallocation) { // dealloc
        return DEALLOCATED_ERROR;
    }
    if (set == NULL) { // null
        return NULL_POINTER_ERROR;
    }


    if (set->isInt && !ElementInSet(element, set)) { // adds if int
        set->elements = realloc(set->elements, sizeof(void *) * (set->length + 1));
        set->elements[set->length] = malloc(set->elementSize);

        if (set->elements[set->length] == NULL) {
            deinitSet(set);
            return NULL_POINTER_ERROR;
        }

        memcpy(set->elements[set->length], element, set->elementSize); // add element to set
        set->length += 1;
        return SUCCESS;
    } else if (set->elementSize == sizeof(char[64]) && !ElementInSet(element, set)) { // adds if 64-char string
        set->elements = realloc(set->elements, sizeof(void *) * (set->length + 1));
        set->elements[set->length] = malloc(set->elementSize);

        if (set->elements[set->length] == NULL) {
            deinitSet(set);
            return NULL_POINTER_ERROR;
        }

        strcpy((char *)set->elements[set->length], (const char *)element); // add element to set
        set->length += 1; // increment length
        return SUCCESS;
    }

    return ELEMENT_EXISTS_ERROR;
}

int displaySet(GenSet_t *set) {  // Follows Error Codes
    if (set->deallocation) {
        return DEALLOCATED_ERROR;
    }
    if (set == NULL) {
        return NULL_POINTER_ERROR;
    }

    printf("{");

    for (int i = 0; i < set->length; i++) {
        // prints all elements of set, only if set is of type int/char[64]
        if (set->elementSize == sizeof(int)) {
            printf("%d", *((const int *)set->elements[i]));
        } else if (set->elementSize == sizeof(char[64])) {
            printf("%s", (const char *)set->elements[i]);
        }

        if (i < set->length - 1) {
            printf(", ");
        }
    }

    printf("}\n");

    return SUCCESS;
}

int countSet(GenSet_t *set) {  // Follows Error Codes
    if (set->deallocation) {
        return DEALLOCATED_ERROR;
    }
    if (set == NULL) {
        return NULL_POINTER_ERROR;
    }
    // returns the length of the set ie. no of elements in set
    return set->length;
}

GenSet_t *unionSet(GenSet_t *set1, GenSet_t *set2) {  // NULL: dealloc/NULL sets, diff set types
    if (set1->deallocation || set2->deallocation) {
        return NULL;
    }
    if (set1 == NULL || set2 == NULL) {
        return NULL;
    }

    if (set1->isInt != set2->isInt) {
        return NULL;
    } // dealloc, mismatch type and null checks
    // creates new set to store union
    GenSet_t *newSet = initSet(set1->elementSize);
    // add elements of set1
    for (int i = 0; i < set1->length; i++) {
        addToSet(newSet, set1->elements[i]);
    }
    // add elements of set3
    for (int i = 0; i < set2->length; i++) {
        addToSet(newSet, set2->elements[i]);
    } // adds all elem of set 1 and 2

    return newSet;
}

GenSet_t *intersectSet(GenSet_t *set1, GenSet_t *set2) {  // NULL: dealloc/NULL sets, diff set types
    if (set1->deallocation || set2->deallocation) {
        return NULL;
    }
    if (set1 == NULL || set2 == NULL) {
        return NULL;
    }

    if (set1->elementSize != set2->elementSize) {
        return NULL;
    } // dealloc, mismatch type and null checks

    // creates new set to store intersection
    GenSet_t *newSet = initSet(set1->elementSize);

    for (int i = 0; i < set1->length; i++) {
        if (ElementInSet(set1->elements[i], set2)) {
            addToSet(newSet, set1->elements[i]);
        }
    } // adds elem of set1 to set if in set2

    return newSet;
}

GenSet_t *diffSet(GenSet_t *set1, GenSet_t *set2) {  // NULL: dealloc/NULL sets, diff set types
    if (set1->deallocation || set2->deallocation) {
        return NULL;
    }
    if (set1 == NULL || set2 == NULL) {
        return NULL;
    }

    if (set1->elementSize != set2->elementSize) {
        return NULL;
    } // dealloc, mismatch type and null checks

    // creates new set to store diff
    GenSet_t *newSet = initSet(set1->elementSize);

    for (int i = 0; i < set1->length; i++) {
        if (!ElementInSet(set1->elements[i], set2)) {
            addToSet(newSet, set1->elements[i]);
        }
    } // adds elem of set1 to set if not in set 2

    return newSet;
}
