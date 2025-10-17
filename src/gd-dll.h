/******************************************************************************
 * Doubly-linked list data structure and methods
 *****************************************************************************/

#ifndef GD_DLL_H
#define GD_DLL_H

typedef struct gd__dll_nodeT gd_dll_node;
struct gd__dll_nodeT {
    void* value;
    gd_dll_node* next;
    gd_dll_node* prev;
};

typedef struct gd__dllT gd_dll;
struct gd__dllT {
    int length;
    gd_dll_node* head;
    gd_dll_node* tail;
};

/**
 * Initialize a doubly linked list
 */
gd_dll* gd_dll_init(void);

/**
 * Free entire list, using a callback function to free malloc'd values
 */
void gd_dll_cleanup(gd_dll* list, void (*callback)(void* value));

gd_dll_node* gd_dll_push(gd_dll* list, void* value);
gd_dll_node* gd_dll_unshift(gd_dll* list, void* value);
void* gd_dll_pop(gd_dll* list);
void* gd_dll_shift(gd_dll* list);

void gd_dll_forEach(gd_dll* list, void (*callback)(void* value));
void gd_dll_reverse(gd_dll* list);

#endif // GD_DLL_H
