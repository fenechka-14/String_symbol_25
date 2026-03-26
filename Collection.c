#include "Collection.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4 //небольшая емкость коллекции для начала

Collection* create_collection(const TypeInfo *type){
    Collection *col = malloc(sizeof(Collection)); //выделяем память под массив
    if (!col) return NULL; //если не выделилась память
    col->type = type; //сохр указатель на тип
    col->size = 0; //сначала элементов нет
    col->capacity = INITIAL_CAPACITY; //устанавливаем начальную емкость
    col->data = malloc(type->elem_size * col->capacity); // el на capacity
    if (!col->data){
        free(col);
        return NULL;
    } // if память не выделилась под массив, то чистим ранее выделенную структуру
    return col; //готовая col
}

void free_collection(Collection *col){
    if (!col) return; //if null ничего не делаем
    for (size_t i=0; i<col->size; ++i){
        void *elem = (char*)col->data + i * col->type->elem_size; //уточнить
        col->type->free(elem);
    }
    free(col->data); //освобождаем слоты
    free(col); //освобождаем память структуры
}

static int ensure_capacity(Collection *col,size_t new_size){
    if (new_size <= col->capacity) return 1;
    size_t new_cap = col->capacity * 2; //удвоим текущуюю емкость
    if (new_cap < new_size) new_cap = new_size; //если все равно мало
    void *new_data = realloc(col->data, col->type->elem_size * new_cap); //выделение память под new_cap элементов
    if (!new_data) return 0; //ошибка если не удалось выделить память
    col->data = new_data; //сохраняем новый указатель на начало адреса памяти массива
    col->capacity = new_cap; //новая емкость
    return 1;
}

int append(Collection *col, const void *elem){
    if (!col || !elem) return 0; //если что-то из Null, то ничего
    if (!ensure_capacity(col, col->size + 1)) return 0; //проверка есть ли место для нового el
    void *slot = (char*)col->data + col->size * col->type->elem_size; //адрес новго слота (начало массива + кол-во эл на размер)
    col->type->init(slot); //делаем слот безопасным
    col->type->copy(slot, elem); //copy from el to slot
    col->size++; //увеличиваем счетчик el
    return 1;
}

void* get(const Collection *col, size_t index){
    if (!col || index >= col->size) return NULL; //проверка есть ли массив и индекс
    return (char*)col->data + index * col->type->elem_size; //переходим к нужному индексу (начало + el на size)
}

void set(Collection *col, size_t index, const void *elem){
    if (!col || index >= col->size || !elem) return; // проверка существования массива, индекса и передан ли новый el
    void *slot = (char*)col->data + index * col->type->elem_size; //адрес нужной ячейки
    col->type->free(slot); //удаляем данные по индексу
    col->type->init(slot); //приводим ячейку в безопасное состояние
    col->type->copy(slot, elem); //copy new_el
}

size_t size(const Collection *col){
    return col ? col->size : 0; //if col !=0 то возвращается size, иначе 0
}

size_t capacity(const Collection *col){
    return col ? col->capacity : 0; //аналогично возвращает либо текущую емкость либо 0
}
