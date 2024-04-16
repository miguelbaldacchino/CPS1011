#include <stdio.h>
#include "GenSet2.h"

int intComparison(const void* a, const void* b) {
    return (*(int*)a - *(int*)b); // via type-casting
}

void intDisplaying(const void* element) {
    printf("%d ", *(int*)element);
}

void IntFileWrite(const void* element, FILE* name) {
    FILE* file = fopen(name, "a");
    if (file == NULL) {
        return;
    }

    fprintf(file, "%d\n", *(int*)element);

    fclose(file);
}

int charComparison(const void* a, const void* b) {
    return (*(char*)a - *(char*)b); // via type-casting
}

void charDisplaying(const void* element) {
    printf("%c", *(char*)element);
}

void charFileWrite(const void* element, const char* name) {
    FILE* file = fopen(name, "a");
    if (file == NULL) {
        return;
    }

    fprintf(file, "%c\n", *(char*)element);

    fclose(file);
}

int main () {/*
    GenSet *setA = initSet(sizeof(int), intComparison, intDisplaying, IntFileWrite);
    GenSet *setB = initSet(sizeof(int), intComparison, intDisplaying, IntFileWrite);


    if (isEmptySet(setA)) { printf("Set A is empty/deallocated"); }
    else { printf("Set A is not empty"); }
    printf(" after initialization\n");
    if (isEmptySet(setB)) { printf("Set B is empty/deallocated"); }
    else { printf("Set is B not empty"); }
    printf(" after initialization\n");

    int element1 = 1; int element4 = 4;
    int element2 = 2;
    int element3 = 3;

    addToSet(setA, &element1); addToSet(setB, &element4);
    addToSet(setA, &element2); addToSet(setB, &element2);
    addToSet(setA, &element3); addToSet(setB, &element3);

    if (isEmptySet(setA)) { printf("Set A is empty/deallocated\n"); }
    else { printf("Set A is not empty\n"); }
    if (isEmptySet(setB)) { printf("Set B is empty/deallocated\n"); }
    else { printf("Set B is not empty\n"); }

    displaySet(setA);
    displaySet(setB);

    size_t numberOfElements = countSet(setA);
    printf("Number of elements in Set A: %zu\n", numberOfElements);

    if (isSubsetSet(setA, setB)) {printf("A subset B\n"); }
    else { printf("A not subset B\n"); }

    GenSet* setC = unionSet(setA, setB); // all elements of a and b
    displaySet(setC);

    GenSet* setD = intersectSet(setA, setB); // all elements of a and b
    displaySet(setD);

    GenSet* setE = diffSet(setA, setB); // all elements of a and b
    displaySet(setE);

    export(setB, "setB.txt");

    deinitSet(setA);
    displaySet(setA);

    if (isEmptySet(setA)) { printf("Set is empty/deallocated"); }
    else { printf("Set is not empty"); }
    printf(" after deinitialization\n"); */


     GenSet *setA = initSet(sizeof(char), charComparison, charDisplaying, charFileWrite);
    GenSet *setB = initSet(sizeof(char), charComparison, charDisplaying, charFileWrite);


    if (isEmptySet(setA)) { printf("Set A is empty/deallocated"); }
    else { printf("Set A is not empty"); }
    printf(" after initialization\n");
    if (isEmptySet(setB)) { printf("Set B is empty/deallocated"); }
    else { printf("Set is B not empty"); }
    printf(" after initialization\n");

    char element1 = 'a'; char element4 = 'd';
    char element2 = 'b';
    char element3 = 'c';

    addToSet(setA, &element1); addToSet(setB, &element4);
    addToSet(setA, &element2); addToSet(setB, &element2);
    addToSet(setA, &element3); addToSet(setB, &element3);

    if (isEmptySet(setA)) { printf("Set A is empty/deallocated\n"); }
    else { printf("Set A is not empty\n"); }
    if (isEmptySet(setB)) { printf("Set B is empty/deallocated\n"); }
    else { printf("Set B is not empty\n"); }

    displaySet(setA);
    displaySet(setB);

    size_t numberOfElements = countSet(setA);
    printf("Number of elements in Set A: %zu\n", numberOfElements);

    if (isSubsetSet(setA, setB)) {printf("A subset B\n"); }
    else { printf("A not subset B\n"); }

    GenSet* setC = unionSet(setA, setB); // all elements of a and b
    displaySet(setC);

    GenSet* setD = intersectSet(setA, setB); // all elements of a and b
    displaySet(setD);

    GenSet* setE = diffSet(setA, setB); // all elements of a and b
    displaySet(setE);

    export(setB, "setB.txt");

    deinitSet(setA);
    displaySet(setA);

    if (isEmptySet(setA)) { printf("Set is empty/deallocated"); }
    else { printf("Set is not empty"); }
    printf(" after deinitialization\n");



}