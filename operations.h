#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Collection.h"

Collection* concat(const Collection *a, const Collection *b); //конкатенация
Collection* subarray(const Collection *col, size_t i, size_t j); //подмассив с i el по j el
Collection* split_words(const Collection *str_col); //разбиение на слова

#endif