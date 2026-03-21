#include <stdio.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"

void test_create_free_char() {
    printf("Test 1: create/free char collection... ");
    fflush(stdout);
    Collection *col = create_collection(get_char_type());
    assert(col != NULL);
    assert(size(col) == 0);
    assert(capacity(col) >= 4);
    free_collection(col);
    printf("OK\n");
}