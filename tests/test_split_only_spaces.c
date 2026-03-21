#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"
#include "operations.h"

void test_split_only_spaces() {
    printf("Test 12: split string with only spaces... ");
    fflush(stdout);
    Collection *str = create_collection(get_char_type());
    char text[] = "   \t  \n  ";
    for (size_t i = 0; i < strlen(text); ++i) append(str, &text[i]);

    Collection *words = split_words(str);
    assert(words != NULL);
    assert(size(words) == 0);
    free_collection(str);
    free_collection(words);
    printf("OK\n");
}
