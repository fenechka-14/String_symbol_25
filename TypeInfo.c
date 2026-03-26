#include "TypeInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//вспомогательные функции для symbol (char)
static void char_init(void *dst){
    *(char*)dst = 0; //безопасное состояние для слота с символом
}

static void char_copy(void *dst, const void *src){
    *(char*)dst = *(const char*)src; //копируем символ
}

static void char_free(void *elem){
    (void)elem; //ничего не делаем, просто игнорируем параметр
}

static void char_print(const void *elem){
    printf("%c", *(char*)elem);
}

static void char_scan( void *elem){
    scanf( " %c", (char*)elem); //сразу в массив эл
}

static int char_compare(const void *a, const void *b){
    const char ca = *(const char*)a;
    const char cb = *(const char*)b;
    if (ca < cb) return -1;
    if (ca > cb) return 1;
    return 0;
}


//вспомогательные функции для string (char*)
static void string_init(void *dst){
   char **slot = (char**)dst; // указатель на слот
   *slot = NULL;
}

static void string_copy(void *dst, const void *src){
    char **d = (char**)dst; //указывает на слот приемник
    const char **s = (const char**)src;
    *d = (char*)*s;
}

static void string_free(void *elem){
    char **slot = (char**)elem;
    if (*slot) {
        free(*slot);
        *slot = NULL;
    }
}

static void string_print(const void *elem){
    const char **slot = (const char**)elem;
    const char *str = *slot;
    if (str) printf("%s",str);
    else printf("(null)");
}

static void string_scan(void *elem){
    string_free(elem);
    char **slot = (char**)elem;
    char buffer[256];
    if (scanf("%255s", buffer)==1){
        *slot=malloc(strlen(buffer)+1); //выделяем память под копию
        if (*slot){
            strcpy(*slot, buffer);
        } else {
            *slot = NULL;
        }
    } else {
        *slot = NULL;
    }
}

static int string_compare(const void *a, const void *b){
    const char **sa = (const char**)a; //адрес 1го слота
    const char **sb = (const char**)b; //адрес 2го слота
    const char *stra = *sa; //указатель на 1ю строку
    const char *strb = *sb; //указатель на 2ю строку
    if (!stra && !strb) return 0; //если оба Null
    if (!stra) return -1; //если первая Null
    if (!strb) return 1;
    return strcmp(stra, strb);
    
}

//Типы
const TypeInfo* get_char_type(void) {
    static const TypeInfo info = {
        .elem_size = sizeof(char),
        .init = char_init,
        .copy = char_copy,
        .free = char_free,
        .print = char_print,
        .scan = char_scan,
        .compare = char_compare
    };
    return &info;
}

const TypeInfo* get_string_type(void) {
    static const TypeInfo info = {
        .elem_size = sizeof(char*),
        .init = string_init,
        .copy = string_copy,
        .free = string_free,
        .print = string_print,
        .scan = string_scan,
        .compare = string_compare
    };
    return &info;
}