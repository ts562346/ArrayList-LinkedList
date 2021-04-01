//
// Created by Tasneem on 2021-02-26.
//

#include "linked_list.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

LinkedList* llist_initialize(int dataTypeSize, char* dataType){
    LinkedList *linkedList = malloc(sizeof (LinkedList));

    if(linkedList == NULL || dataType == NULL)
        return NULL;

    linkedList->first = NULL;
    linkedList->last = NULL;
    linkedList->size = 0;
    linkedList->itemSize = dataTypeSize;
    linkedList->type = malloc(strlen(dataType) + 1);
    strcpy(linkedList->type, dataType);

    return linkedList;
}

bool llist_add_at(LinkedList *list, int index, void *element)
{
    if(element != NULL && list != NULL){
        Node *node = malloc(sizeof(Node));

        if(node == NULL)
            return false;

        node->data = malloc(list->itemSize);

        if(node->data == NULL)
            return false;

        if(index > 0 && index < ((list->size))){
            Node *currentNode = list->first;

            if(currentNode == NULL)
                return false;

            for(int i = 0; i < index; i++)
                currentNode = currentNode->next;

            if(currentNode == NULL)
                return false;

            memcpy(node->data, element, list->itemSize);

            (currentNode->prev)->next = node;
            node->next = currentNode;
            node->prev = currentNode->prev;
            currentNode->prev = node;

            list->size++;
            return true;
        }

        else if(list->size == 0){
            memcpy(node->data, element, list->itemSize);

            list->first = node;
            list->last = node;
            node->next = NULL;
            node->prev = NULL;
            list->size++;

            return true;
        }

        else if(index == 0){
            memcpy(node->data, element, list->itemSize);
            Node *currentNode = list->first;

            if(currentNode == NULL)
                return false;

            currentNode->prev = node;
            node->prev = NULL;
            node->next = currentNode;
            list->first = node;

            list->size++;
            return true;
        }

        else if(index == (list->size)){
            memcpy(node->data, element, list->itemSize);
            Node *currentNode = list->last;

            if(currentNode == NULL)
                return false;

            node->next = NULL;
            node->prev = currentNode;
            currentNode->next = node;
            list->last = node;

            list->size++;
            return true;
        }

        else
            return false;
    }

    return false;

}

bool llist_add_first(LinkedList* list, void* element){
    if (element == NULL || list == NULL)
        return false;

    llist_add_at(list, 0, element);
}

bool llist_add_last(LinkedList* list, void* element){
    if (element == NULL || list == NULL)
        return false;

    llist_add_at(list, list->size, element);
}

void* llist_get(LinkedList *list, int index){

    if(list != NULL){

        if(index >= 0 && index < (list->size)){

            void *element = malloc(list->itemSize);
            Node *currentNode = list->first;

            if(currentNode == NULL)
                return NULL;

            for(int i = 0; i < index; i++)
                currentNode = currentNode->next;

            if(currentNode == NULL)
                return NULL;

            memcpy(element, currentNode->data, list->itemSize);

            if(element != NULL)
                return element;
        }
        return NULL;
    }
    return NULL;
}

int llist_index_of(LinkedList* list, void* element){
    if (list == NULL || element == NULL)
        return -1;

    Node *node = list->first;

    if (node == NULL)
        return -1;

    for (int i = 0; i < list->size; i++){

        if (node == NULL || node->data == NULL)
            return -1;

        if (memcmp(element, node->data, list->itemSize) == 0)
            return i;
    }
}

void* llist_remove(LinkedList* list, int index){
    if (list == NULL)
        return NULL;

    if (index > 0 && index < (list->size)-1) {
        void *element = malloc(list->itemSize);

        if(element == NULL)
            return NULL;

        Node *node = list->first;

        if(node == NULL)
            return NULL;

        for(int i = 0; i < index; i++)
            node = node->next;

        if(node == NULL || node->data == NULL)
            return NULL;

        node->data = malloc(list->itemSize);
        memcpy(node->data, element, list->itemSize);

        (node->prev)->next = node->next;
        (node->next)->prev = node->prev;

        if((node->prev)->next == NULL || (node->next)->prev == NULL)
            return NULL;

        free(node->data);
        free(node);
        list->size--;

        if(element != NULL)
            return element;
        else
            return NULL;

    } else if (index == 0) {

        if(list->size == 1) {
            Node *node = list->first;

            if(node == NULL)
                return NULL;

            void *element = malloc(list->itemSize);

            if(element == NULL)
                return NULL;

            node->data = malloc(list->itemSize);
            memcpy(node->data, element, list->itemSize);

            list->first = NULL;
            node->next = NULL;
            node->prev = NULL;

            free(node->data);
            free(node);
            list->size--;

            if(element != NULL)
                return element;
            else
                return NULL;
        }

        Node *currentNode = list->first;

        if(currentNode == NULL)
            return NULL;

        void *element = malloc(list->itemSize);

        if(element == NULL)
            return NULL;

        currentNode->data = malloc(list->itemSize);
        memcpy(currentNode->data, element, list->itemSize);

        list->first = currentNode->next;

        if(list->first == NULL)
            return NULL;

        (currentNode->next)->prev = NULL;

        currentNode->next = NULL;
        free(currentNode->data);
        free(currentNode);
        list->size--;

        if(element != NULL)
            return element;
        else
            return NULL;

    } else if(index == (list->size)-1) {
        Node *currentNode = list->last;

        if(currentNode == NULL)
            return NULL;

        void *element = malloc(list->itemSize);

        if(element == NULL)
            return NULL;

        currentNode->data = malloc(list->itemSize);
        memcpy(currentNode->data, element, list->itemSize);

        list->last = currentNode->prev;

        if(list->last == NULL)
            return NULL;

        (currentNode->prev)->next = NULL;

        currentNode->prev = NULL;

        free(currentNode->data);
        free(currentNode);
        list->size--;

        if(element != NULL)
            return element;
        else
            return NULL;
    } else {
        return NULL;
    }
}

void* llist_remove_first(LinkedList* list){
    if (list == NULL)
        return false;
    else
        llist_remove(list, 0);
}

void* llist_remove_last(LinkedList* list){
    if (list == NULL)
        return false;
    else
        llist_remove(list, (list->size)-1);
}

bool llist_destroy(LinkedList* list){
    if (list == NULL)
        return false;

    Node *currentNode = list->first;

    for(int i=0; i < (list->size); i++){
        Node *temp = currentNode->next;
        free(currentNode->data);

        free(currentNode);
        currentNode = temp;
    }

    free(list->type);
    free(list);

    return true;
}
