#include "GenSet1.h"
#include <stdio.h>

int main() {
    //INT
    printf("INTEGER:\n");
    GenSet_t *integerSet1 = initSet(sizeof(int)); // initializing sets
    GenSet_t *integerSet2 = initSet(sizeof(int)); // w type int

    int elem1 = 1;
    int elem2 = 2; int elem3 = 3;
    int elem4 = 4; int elem5 = 5; // declaring int variables

    addToSet(integerSet1, &elem1);
    addToSet(integerSet1, &elem2);
    addToSet(integerSet1, &elem3);
    // adding vars to set
    addToSet(integerSet2, &elem3);
    addToSet(integerSet2, &elem4);
    addToSet(integerSet2, &elem5);

    printf("Set 1: ");
    displaySet(integerSet1);
    //display sets
    printf("Set 2: ");
    displaySet(integerSet2);

    //set operations
    GenSet_t *unionintegerSet = unionSet(integerSet1, integerSet2);
    printf("Union Set: ");
    displaySet(unionintegerSet);

    GenSet_t *intersectintegerSet = intersectSet(integerSet1, integerSet2);
    printf("Intersection Set: ");
    displaySet(intersectintegerSet);

    GenSet_t *diffintegerSet = diffSet(integerSet1, integerSet2);
    printf("Difference Set: ");
    displaySet(diffintegerSet);

    // CHAR
    printf("\nCHARACTER:\n");
    GenSet_t *characterSet1 = initSet(sizeof(char[64])); // initializing sets
    GenSet_t *characterSet2 = initSet(sizeof(char[64])); // w type 64-char string


    addToSet(characterSet1, "test1");
    addToSet(characterSet1, "test2");
    addToSet(characterSet1, "test3");
    // adding str to set
    addToSet(characterSet2, "test3");
    addToSet(characterSet2, "test4");
    addToSet(characterSet2, "test5");

    printf("Set 1: ");
    displaySet(characterSet1);
    // displaying sets
    printf("Set 2: ");
    displaySet(characterSet2);

    // sset operations
    GenSet_t *unioncharacterSet = unionSet(characterSet1, characterSet2);
    printf("Union Set: ");
    displaySet(unioncharacterSet);

    GenSet_t *intersectcharacterSet = intersectSet(characterSet1, characterSet2);
    printf("Intersection Set: ");
    displaySet(intersectcharacterSet);

    GenSet_t *diffcharacterSet = diffSet(characterSet1, characterSet2);
    printf("Difference Set: ");
    displaySet(diffcharacterSet);

    // CHECKS AND TESTING
    if (!(isSubsetSet(integerSet2, characterSet1))) { printf("Mismatches sets\n"); } // VALIDATION CHECK FOR MISMATCHED SETS
    if (unionSet(integerSet1, characterSet2) == NULL) { printf("MISMATCH SETS FOR UNION\n"); } // VALIDATION CHECK FOR MISMATCHES SETS FOR UNION
    if (intersectSet(integerSet1, characterSet2) == NULL) { printf("MISMATCH SETS FOR INTERSECT\n"); } // VALIDAATION CHECK FOR MISMATCHING SETS IN INTERSECTION
    if (diffSet(integerSet1, characterSet2) == NULL) { printf("MISMATCH SETS FOR DIFF\n"); } // VALIDATION CHECK FOR MISMATCHING SETS IN DIFFERENCE

    GenSet_t *invalidSet = initSet(sizeof(double));
    if (invalidSet == NULL) {printf("INVALID SET RETURNED NULL\n");} // VALID CHECK FOR INVALID SETS RETURNING NULL

    deinitSet(characterSet1);
    deinitSet(characterSet2);
    deinitSet(unioncharacterSet);
    deinitSet(intersectcharacterSet);
    deinitSet(diffcharacterSet);
    //deinitialize all
    deinitSet(integerSet1);
    deinitSet(integerSet2);
    deinitSet(unionintegerSet);
    deinitSet(intersectintegerSet);
    deinitSet(diffintegerSet);

    return 0;
}
