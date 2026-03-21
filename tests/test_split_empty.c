#include <stdio.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"
#include "operations.h"

void test_split_empty() {
    printf("Test 11: split empty string... ");
    fflush(stdout);
    Collection *str = create_collection(get_char_type());
    Collection *words = split_words(str);
    assert(words != NULL);
    assert(size(words) == 0);
    free_collection(str);
    free_collection(words);
    printf("OK\n");
}
