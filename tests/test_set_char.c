#include <stdio.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"

void test_set_char() {
    printf("Test 3: set element in char collection... ");
    fflush(stdout);
    Collection *col = create_collection(get_char_type());
    char c1 = 'X', c2 = 'Y';
    append(col, &c1);
    append(col, &c1);
    assert(size(col) == 2);

    set(col, 1, &c2);
    assert(*(char*)get(col, 0) == 'X');
    assert(*(char*)get(col, 1) == 'Y');

    // попытка с неверным индексом не должна ничего менять
    set(col, 5, &c2);
    assert(size(col) == 2);
    assert(*(char*)get(col, 1) == 'Y');

    free_collection(col);
    printf("OK\n");
}
