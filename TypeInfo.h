#ifndef TYPEINFO_H
#define TYPEINFO_H 

#include <stddef.h>

typedef struct TypeInfo
{
    size_t elem_size; //размер эл в байтах
    void (*init)(void *dst); //подготовка пустой ячейки к безопасном использованию
    void (*copy)(void *dst, const void *src); //copy from src to dst
    void (*free)(void *elem); //free память
    void (*print)(const void *elem); //просто чтоб вывел элемент
    void (*scan)(void *elem); //для тестов + чтение элемента из stdin
    int (*compare)(const void *a, const void *b); //сравнение для усложнения(31) и тестов
} 
TypeInfo;

const TypeInfo *get_char_type(void);//прототип, не примает аргументов, возвращает указатель
const TypeInfo *get_string_type(void);//same для строки

#endif
