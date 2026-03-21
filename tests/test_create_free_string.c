#include <stdio.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"

void test_create_free_string() {
    printf("Test 4: create/free string collection... ");
    fflush(stdout);
    Collection *col = create_collection(get_string_type());
    assert(col != NULL);
    assert(size(col) == 0);
    free_collection(col);
    printf("OK\n");
}
