#include <stdio.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"
#include "operations.h"

void test_concat_mismatch() {
    printf("Test 8: concatenation with type mismatch (expect NULL)... ");
    fflush(stdout);
    Collection *a = create_collection(get_char_type());
    Collection *b = create_collection(get_string_type());
    Collection *c = concat(a, b);
    assert(c == NULL);
    free_collection(a);
    free_collection(b);
    printf("OK\n");
}
