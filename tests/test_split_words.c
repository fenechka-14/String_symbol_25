#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"
#include "operations.h"

void test_split_words() {
    printf("Test 10: split words... ");
    fflush(stdout);
    Collection *str = create_collection(get_char_type());
    char text[] = "  Hello   world!  ";
    for (size_t i = 0; i < strlen(text); ++i) append(str, &text[i]);

    Collection *words = split_words(str);
    assert(words != NULL);
    assert(size(words) == 2);

    const char *w1 = *(const char**)get(words, 0);
    const char *w2 = *(const char**)get(words, 1);
    assert(strcmp(w1, "Hello") == 0);
    assert(strcmp(w2, "world!") == 0);

    free_collection(str);
    free_collection(words);
    printf("OK\n");
}
