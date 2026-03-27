#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Collection.h"
#include "TypeInfo.h"
#include "operations.h"

/* ---------- печать коллекции ---------- */
static void print_collection(const Collection *col, const char *name) {
    if (!col) {
        printf("  %s = (не создана)\n", name);
        return;
    }
    printf("  %s (size %zu, cap %zu): [", name, size(col), capacity(col));
    for (size_t i = 0; i < size(col); ++i) {
        if (i > 0) printf(", ");
        void *elem = get(col, i);
        col->type->print(elem);
    }
    printf("]\n");
}


int main(void) {
    Collection *cat_coll = create_collection(get_string_type());
    const char *cat_str = "cat";
    append(cat_coll, &cat_str);
    print_collection(cat_coll, "Cat's");
    free_collection(cat_coll);
}
