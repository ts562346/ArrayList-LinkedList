//
// Created by Tasneem on 2021-02-20.
//

#include "array_list.h"
#include "stdlib.h"
#include <string.h>
#include "stdbool.h"

ArrayList* alist_initialize (int maxSize, int dataSize, char* type){
    ArrayList *list = malloc(sizeof (ArrayList));
    list->arr = malloc(sizeof (void*) * maxSize);
    list->size = 0;
    list->maxSize = maxSize;
    list->itemSize = dataSize;
    list->type = type;

    return list;
}

bool alist_add (ArrayList* list, void* element) {
    if (element == NULL || list == NULL)
        return false;

    if (list-> size == list-> maxSize)
        _alist_resize(list);

    list->arr[list->size] = malloc(list->itemSize);
    memcpy(list->arr[list->size], element, list->itemSize);

    list->size++;

    if (list->arr[(list->size) - 1] == NULL)
        return false;

    return true;
}

bool alist_add_at (ArrayList* list, int index, void* element){

    if(list == NULL || element == NULL)
        return false;

    if (index < 0 && index > list->size)
        return false;

    if  (list->size == list->maxSize)
        _alist_resize(list);

    list->arr[list->size] = malloc(list->itemSize);

    // not sure
    for (int i = list->size; i > index; i--){
        list->arr[i] = list->arr[i-1];
    }

    list->arr[index] = malloc(list->itemSize);

    memcpy(list->arr[index], element, list->itemSize);
    list->size++;

    return true;
}

void alist_clear (ArrayList* list){
    if (list == NULL)
        return;

    for (int i = 0; i < list->size; ++i) {
        free(list->arr[i]);
    }

    free(list);
}

void* alist_get (ArrayList* list, int index){
    if (list == NULL)
        return NULL;

    if(index < 0 || index > list->size)
        return NULL;

    return (list->arr[index]);

}

int alist_index_of (ArrayList* list, void* element){
    if (list == NULL || element == NULL)
        return -1;

    for (int i = 0; i < list->size; ++i) {
        if(memcmp(element, list->arr[i], list->itemSize) == 0)
            return 1;
    }
}

void* alist_remove (ArrayList* list, int index){
    if(list == NULL)
        return NULL;

    if(index < 0 || index > list->size)
        return NULL;

    void *remove; // not sure
    void *removedElement = memcpy(remove, list->arr[index], list->itemSize);
    free(list->arr[index]);

    for (int i = index; i < (list->size)-1; ++i)
        list->arr[i] = list->arr[i+1];

    list->size--;
    return removedElement;

}

bool alist_destroy (ArrayList* list){
    if (list == NULL)
        return false;

    for (int i = 0; i < (list->size); ++i) {
        free(list->arr[i]);
    }

    free(list->arr);
    return true;
}

bool _alist_resize (ArrayList* list){
    if (list == NULL)
        return false;

    list->maxSize *= 2;
    list->arr = realloc(list->arr, sizeof(void*) *list->maxSize);

    if(list->arr[(list->maxSize)-1] == 0)
        return false;

    return true;
}
