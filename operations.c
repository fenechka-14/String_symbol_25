#include "operations.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Collection* concat(const Collection *a, const Collection *b){
    if (!a || !b) return NULL; //проверка на существование коллекций
    if (a->type != b->type) return NULL; //проверка на тип
    Collection *result = create_collection(a->type); //создаем new coll того же типа
    if (!result) return NULL; //если не удалось создать
    for (size_t i = 0; i< size(a); ++i){
        void *elem = get(a,i);
        if (!append(result, elem)){
            free_collection(result); //если не вышло
            return NULL;
        }
    }
    for (size_t i = 0; i < size(b); ++i){
        void *elem = get(b, i);
        if (!append(result, elem)) {
            free_collection(result);
            return NULL;
        }
    }
    return result;
}

Collection* subarray(const Collection *col, size_t i, size_t j){
    if (!col) return NULL;
    if (i > j || j >= size(col)) return NULL; //i<j & j не выходит за col
    Collection *result = create_collection(col->type); //создаем новую col
    if (!result) return NULL;
    for ( size_t k=i; k <= j; ++k){
        void *elem = get(col, k);
        if (!append(result, elem)){
            free_collection(result); //чистим если не вышло добавить
            return NULL;
        }
    }
    return result;
}

Collection* split_words(const Collection *str_col){
    if (!str_col) return NULL; //проверка на существование
    if (str_col->type != get_char_type()) return NULL; //проверка есть ли символы
    Collection *words = create_collection(get_string_type()); //новая col для хранения строк (слов)
    if (!words) return NULL;
    const char *chars = (const char*)str_col->data; //локальная переменная указывающая на нашу изначальную строку
    size_t len = size(str_col); //len string
    size_t start = 0;
    while (start < len){
        while (start < len && isspace((unsigned char)chars[start])) start++; //пропуск всех пробельных символов
        if (start >= len) break; //выход если дошли до конца
        size_t end = start;
        while (end < len && !isspace((unsigned char)chars[end])) end++; //тоже
        size_t word_len = end - start;
        char *word = malloc(word_len + 1);
        if (!word){
            free_collection(words);
            return NULL;
        }
        memcpy(word, chars + start, word_len); //копируем слово (с байта нужного + длина слова)
        word[word_len] = '\0'; //+ завершающий символ
        if (!append(words, &word)){ //если получилось - добавили, нет - почистили 
            free(word);
            free_collection(words);
            return NULL;
        }
        start = end; //продолжаем искать слова
    }
    return words;
}
