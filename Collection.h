#ifndef COLLECTION_H
#define COLLECTION_H
#include "TypeInfo.h"
#include <stddef.h>

typedef struct Collection
{
    void *data; //массив элементов
    size_t size; //сколько элементов сейчас
    size_t capacity; //сколько слотов сейчас
    const TypeInfo *type; //инф о типе
}
Collection;

Collection* create_collection(const TypeInfo *type); //создаем массив
void free_collection(Collection *col); //чистим память и массив
int append(Collection *col, const void *elem); //добалвеям new el и проверка памяти
void* get(const Collection *col, size_t index); //get * на el по index
void set(Collection *col, size_t index, const void *elem); //замена el по index новым значением 
size_t size(const Collection *col); //сколько el в массиве
size_t capacity(const Collection *col); //сколько слотов в массиве

#endif
