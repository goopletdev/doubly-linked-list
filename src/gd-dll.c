#include "gd-dll.h"

gd_dll* gd_dll_init(void) {
    gd_dll* list = (gd_dll*)malloc(sizeof(gd_dll));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void gd_dll_cleanup(gd_dll* list, void (*callback)(void* value)) {
    if (callback) {
        while (list->tail) {
            callback(gd_dll_pop(list));
        }
    } else {
        while (list->tail) {
            gd_dll_pop(list);
        }
    }
    free(list);
}

gd_dll_node* gd_dll_push(gd_dll* list, void* value) {
    gd_dll_node* node = (gd_dll_node*)malloc(sizeof(gd_dll_node));
    node->value = value;
    node->prev = list->tail;
    node->next = NULL;
    if (list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
    list->length++;
    return node;
}

gd_dll_node* gd_dll_unshift(gd_dll* list, void* value) {
    gd_dll_node* node = (gd_dll_node*)malloc(sizeof(gd_dll_node));
    node->value = value;
    node->prev = NULL;
    node->next = list->head;
    if (list->head) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }
    list->head = node;
    list->length++;
    return node;
}

void* gd_dll_pop(gd_dll* list) {
    gd_dll_node* node = list->tail;
    if (!node) {
        return NULL;
    }
    list->tail = node->prev;
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    void* value = node->value;
    free(node);
    list->length--;
    return value;
}

void* gd_dll_shift(gd_dll* list) {
    gd_dll_node* node = list->head;
    if (!node) {
        return NULL;
    }
    list->head = node->next;
    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    void* value = node->value;
    free(node);
    list->length--;
    return value;
}

void gd_dll_forEach(gd_dll* list, void (*callback)(void* value)) {
    gd_dll_node* node = list->head;
    while (node) {
        callback(node->value);
        node = node->next;
    }
}

void gd_dll_reverse(gd_dll* list) {
    if (list->length < 1) {
        return;
    }
    gd_dll_node* front = list->head;
    gd_dll_node* back = list->tail;
    void* temp_value = NULL;
    while (front != back) {
        temp_value = front->value;
        front->value = back->value;
        back->value = temp_value;
        if (front->next == back) {
            break;
        }
        front = front->next;
        back = back->prev;
    }
}

