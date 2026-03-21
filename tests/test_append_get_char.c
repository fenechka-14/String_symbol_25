#include <stdio.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"

void test_append_get_char() {
    printf("Test 2: append and get chars... ");
    fflush(stdout);
    Collection *col = create_collection(get_char_type());
    assert(col != NULL);

    char c1 = 'A', c2 = 'B', c3 = 'C';
    assert(append(col, &c1) == 1);
    assert(append(col, &c2) == 1);
    assert(append(col, &c3) == 1);
    assert(size(col) == 3);

    assert(*(char*)get(col, 0) == 'A');
    assert(*(char*)get(col, 1) == 'B');
    assert(*(char*)get(col, 2) == 'C');
    assert(get(col, 3) == NULL);

    free_collection(col);
    printf("OK\n");
}
