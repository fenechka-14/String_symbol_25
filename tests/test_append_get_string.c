#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"

void test_append_get_string() {
    printf("Test 5: append and get strings...\n");
    fflush(stdout);
    Collection *col = create_collection(get_string_type());
    printf("  collection created\n");
    fflush(stdout);

    char *s1 = strdup("Hello");
    char *s2 = strdup("World");
    char *s3 = strdup("!");
    printf("  strings allocated\n");
    fflush(stdout);

    int res1 = append(col, &s1);
    printf("  append s1 returned %d\n", res1);
    fflush(stdout);
    int res2 = append(col, &s2);
    printf("  append s2 returned %d\n", res2);
    fflush(stdout);
    int res3 = append(col, &s3);
    printf("  append s3 returned %d\n", res3);
    fflush(stdout);

    assert(res1 == 1 && res2 == 1 && res3 == 1);
    printf("  size = %zu\n", size(col));
    fflush(stdout);

    const char *got1 = *(const char**)get(col, 0);
    const char *got2 = *(const char**)get(col, 1);
    const char *got3 = *(const char**)get(col, 2);
    printf("  retrieved pointers: %p, %p, %p\n", got1, got2, got3);
    fflush(stdout);

    if (got1) printf("  got1 = %s\n", got1);
    if (got2) printf("  got2 = %s\n", got2);
    if (got3) printf("  got3 = %s\n", got3);
    fflush(stdout);

    assert(strcmp(got1, "Hello") == 0);
    assert(strcmp(got2, "World") == 0);
    assert(strcmp(got3, "!") == 0);
    printf("  string comparisons passed\n");
    fflush(stdout);

    free_collection(col);
    printf("  collection freed\n");
    printf("OK\n");
}
