#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Collection.h"
#include "TypeInfo.h"

void test_set_string() {
    printf("Test 6: set element in string collection...\n");
    fflush(stdout);
    Collection *col = create_collection(get_string_type());
    char *s1 = strdup("Old");
    char *s2 = strdup("New");
    char *s3 = strdup("Old");
    printf("  s1 = %p (%s)\n", s1, s1);
    printf("  s2 = %p (%s)\n", s2, s2);
    printf("  s3 = %p (%s)\n", s3, s3);
    fflush(stdout);

    append(col, &s1);
    append(col, &s3);
    printf("  after append, size = %zu\n", size(col));
    fflush(stdout);

    const char *got0_before = *(const char**)get(col, 0);
    const char *got1_before = *(const char**)get(col, 1);
    printf("  before set: slot0 = %p (%s), slot1 = %p (%s)\n",
           got0_before, got0_before, got1_before, got1_before);
    fflush(stdout);

    set(col, 1, &s2);
    printf("  after set, size = %zu\n", size(col));
    fflush(stdout);

    const char *got0 = *(const char**)get(col, 0);
    const char *got1 = *(const char**)get(col, 1);
    printf("  after set: slot0 = %p (%s), slot1 = %p (%s)\n",
           got0, got0, got1, got1);
    fflush(stdout);

    printf("  s1 still = %s\n", s1);
    printf("  s2 still = %s\n", s2);
    fflush(stdout);

    int cmp0 = strcmp(got0, "Old");
    int cmp1 = strcmp(got1, "New");
    printf("  strcmp(got0, \"Old\") = %d\n", cmp0);
    printf("  strcmp(got1, \"New\") = %d\n", cmp1);
    fflush(stdout);

    assert(cmp0 == 0);
    assert(cmp1 == 0);

    free_collection(col);
    printf("OK\n");
}
