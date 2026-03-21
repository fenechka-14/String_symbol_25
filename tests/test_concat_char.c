#include <stdio.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"
#include "operations.h"

void test_concat_char() {
    printf("Test 7: concatenation of char collections... ");
    fflush(stdout);
    Collection *a = create_collection(get_char_type());
    Collection *b = create_collection(get_char_type());
    char ca[] = {'A', 'B'};
    char cb[] = {'C', 'D'};
    append(a, &ca[0]); append(a, &ca[1]);
    append(b, &cb[0]); append(b, &cb[1]);

    Collection *c = concat(a, b);
    assert(c != NULL);
    assert(size(c) == 4);
    assert(*(char*)get(c, 0) == 'A');
    assert(*(char*)get(c, 3) == 'D');

    free_collection(a);
    free_collection(b);
    free_collection(c);
    printf("OK\n");
}
