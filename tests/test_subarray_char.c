#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"
#include "operations.h"

void test_subarray_char() {
    printf("Test 9: subarray of chars... ");
    fflush(stdout);
    Collection *col = create_collection(get_char_type());
    char str[] = "Hello";
    for (size_t i = 0; i < strlen(str); ++i) append(col, &str[i]);

    Collection *sub = subarray(col, 1, 3);
    assert(sub != NULL);
    assert(size(sub) == 3);
    assert(*(char*)get(sub, 0) == 'e');
    assert(*(char*)get(sub, 1) == 'l');
    assert(*(char*)get(sub, 2) == 'l');

    // неверные индексы
    assert(subarray(col, 2, 1) == NULL);
    assert(subarray(col, 5, 6) == NULL);

    free_collection(col);
    free_collection(sub);
    printf("OK\n");
}
