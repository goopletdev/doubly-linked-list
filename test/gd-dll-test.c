#include "gd-dll.h"
#include "unity.h"

gd_dll* list;

void setUp(void) {
    list = gd_dll_init();
}

void tearDown(void) {
    gd_dll_cleanup(list, free);
}

void gdDllTest_push_shouldAppendValue(void) {
    char* string1 = (char*)malloc(sizeof(char) * 6);
    char* string2 = (char*)malloc(sizeof(char) * 6);
    char* string3 = (char*)malloc(sizeof(char) * 5);
    strcpy(string1, "Hello");
    strcpy(string2, "world");
    strcpy(string3, "test");

    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
    TEST_ASSERT_EQUAL(0, list->length);

    gd_dll_node* node1 = gd_dll_push(list, string1);
    // test list members
    TEST_ASSERT_EQUAL(1, list->length);
    TEST_ASSERT_EQUAL(node1, list->head);
    TEST_ASSERT_EQUAL(node1, list->tail);
    // test node1 members
    TEST_ASSERT_NULL(node1->next);
    TEST_ASSERT_NULL(node1->prev);
    TEST_ASSERT_EQUAL_STRING("Hello", node1->value);

    gd_dll_node* node2 = gd_dll_push(list, string2);
    // test list members
    TEST_ASSERT_EQUAL(2, list->length);
    TEST_ASSERT_EQUAL(node1, list->head);
    TEST_ASSERT_EQUAL(node2, list->tail);
    // test node1 members
    TEST_ASSERT_NULL(node1->prev);
    TEST_ASSERT_EQUAL(node2, node1->next);
    TEST_ASSERT_EQUAL_STRING("Hello", node1->value);
    // test node2 members
    TEST_ASSERT_EQUAL(node1, node2->prev);
    TEST_ASSERT_NULL(node2->next);
    TEST_ASSERT_EQUAL_STRING("world", node2->value);

    gd_dll_node* node3 = gd_dll_push(list, string3);
    // test list members
    TEST_ASSERT_EQUAL(3, list->length);
    TEST_ASSERT_EQUAL(node1, list->head);
    TEST_ASSERT_EQUAL(node3, list->tail);
    // test node1 members
    TEST_ASSERT_NULL(node1->prev);
    TEST_ASSERT_EQUAL(node2, node1->next);
    TEST_ASSERT_EQUAL_STRING("Hello", node1->value);
    // test node2 members
    TEST_ASSERT_EQUAL(node1, node2->prev);
    TEST_ASSERT_EQUAL(node3, node2->next);
    TEST_ASSERT_EQUAL_STRING("world", node2->value);
    // test node3 members
    TEST_ASSERT_EQUAL(node2, node3->prev);
    TEST_ASSERT_NULL(node3->next);
    TEST_ASSERT_EQUAL_STRING("test", node3->value);
}

void gdDllTest_unshift_shouldPrependValue(void) {
    char* string1 = (char*)malloc(sizeof(char) * 6);
    char* string2 = (char*)malloc(sizeof(char) * 6);
    char* string3 = (char*)malloc(sizeof(char) * 5);
    strcpy(string1, "Hello");
    strcpy(string2, "world");
    strcpy(string3, "test");

    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
    TEST_ASSERT_EQUAL(0, list->length);

    gd_dll_node* node1 = gd_dll_unshift(list, string1);
    // test list members
    TEST_ASSERT_EQUAL(1, list->length);
    TEST_ASSERT_EQUAL(node1, list->head);
    TEST_ASSERT_EQUAL(node1, list->tail);
    // test node1 members
    TEST_ASSERT_NULL(node1->next);
    TEST_ASSERT_NULL(node1->prev);
    TEST_ASSERT_EQUAL_STRING("Hello", node1->value);

    gd_dll_node* node2 = gd_dll_unshift(list, string2);
    // test list members
    TEST_ASSERT_EQUAL(2, list->length);
    TEST_ASSERT_EQUAL(node2, list->head);
    TEST_ASSERT_EQUAL(node1, list->tail);
    // test node1 members
    TEST_ASSERT_NULL(node1->next);
    TEST_ASSERT_EQUAL(node2, node1->next);
    TEST_ASSERT_EQUAL_STRING("Hello", node1->value);
    // test node2 members
    TEST_ASSERT_EQUAL(node1, node2->next);
    TEST_ASSERT_NULL(node2->prev);
    TEST_ASSERT_EQUAL_STRING("world", node2->value);

    gd_dll_node* node3 = gd_dll_unshift(list, string3);
    // test list members
    TEST_ASSERT_EQUAL(3, list->length);
    TEST_ASSERT_EQUAL(node3, list->head);
    TEST_ASSERT_EQUAL(node1, list->tail);
    // test node1 members
    TEST_ASSERT_NULL(node1->next);
    TEST_ASSERT_EQUAL(node2, node1->prev);
    TEST_ASSERT_EQUAL_STRING("Hello", node1->value);
    // test node2 members
    TEST_ASSERT_EQUAL(node1, node2->next);
    TEST_ASSERT_EQUAL(node3, node2->prev);
    TEST_ASSERT_EQUAL_STRING("world", node2->value);
    // test node3 members
    TEST_ASSERT_EQUAL(node2, node3->next);
    TEST_ASSERT_NULL(node3->prev);
    TEST_ASSERT_EQUAL_STRING("test", node3->value);
}

void gdDllTest_pop_shouldRemoveAndReturnLastValue(void) {
    char* string1 = (char*)malloc(sizeof(char) * 6);
    char* string2 = (char*)malloc(sizeof(char) * 6);
    char* string3 = (char*)malloc(sizeof(char) * 5);
    strcpy(string1, "Hello");
    strcpy(string2, "world");
    strcpy(string3, "test");
    gd_dll_node* node1 = gd_dll_push(list, string1);
    gd_dll_node* node2 = gd_dll_push(list, string2);
    gd_dll_node* node3 = gd_dll_push(list, string3);

    TEST_ASSERT_EQUAL_STRING("test", gd_dll_pop(list));
    TEST_ASSERT_NULL(node2->next);
    TEST_ASSERT_EQUAL(node2, list->tail);
    TEST_ASSERT_EQUAL(2, list->length);

    TEST_ASSERT_EQUAL_STRING("world", gd_dll_pop(list));
    TEST_ASSERT_NULL(node1->next);
    TEST_ASSERT_EQUAL(node1, list->tail);
    TEST_ASSERT_EQUAL(1, list->length);

    TEST_ASSERT_EQUAL_STRING("Hello", gd_dll_pop(list));
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
    TEST_ASSERT_EQUAL(0, list->length);

    free(string1);
    free(string2);
    free(string3);
}

void gdDllTest_shift_shouldRemoveAndReturnFirstValue(void) {
    char* string1 = (char*)malloc(sizeof(char) * 6);
    char* string2 = (char*)malloc(sizeof(char) * 6);
    char* string3 = (char*)malloc(sizeof(char) * 5);
    strcpy(string1, "Hello");
    strcpy(string2, "world");
    strcpy(string3, "test");
    gd_dll_node* node1 = gd_dll_push(list, string1);
    gd_dll_node* node2 = gd_dll_push(list, string2);
    gd_dll_node* node3 = gd_dll_push(list, string3);

    TEST_ASSERT_EQUAL_STRING("Hello", gd_dll_unshift(list));
    TEST_ASSERT_NULL(node2->prev);
    TEST_ASSERT_EQUAL(node2, list->head);
    TEST_ASSERT_EQUAL(2, list->length);

    TEST_ASSERT_EQUAL_STRING("world", gd_dll_unshift(list));
    TEST_ASSERT_NULL(node3->prev);
    TEST_ASSERT_EQUAL(node3, list->head);
    TEST_ASSERT_EQUAL(1, list->length);

    TEST_ASSERT_EQUAL_STRING("test", gd_dll_unshift(list));
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
    TEST_ASSERT_EQUAL(0, list->length);

    free(string1);
    free(string2);
    free(string3);
}

int count = 0;
char buffer[1024];

void forEach_test_callback(void* value) {
    char* string = (char*)value;
    strcat(buffer, string[0]);
    count++;
}

void gdDllTest_forEach_shouldIterateFromHeadToTail(void) {
    memset(buffer, '\0', 1024);
    char* string1 = (char*)malloc(sizeof(char) * 6);
    char* string2 = (char*)malloc(sizeof(char) * 6);
    char* string3 = (char*)malloc(sizeof(char) * 5);
    strcpy(string1, "Hello");
    strcpy(string2, "world");
    strcpy(string3, "test");
    gd_dll_node* node1 = gd_dll_push(list, string1);
    gd_dll_node* node2 = gd_dll_push(list, string2);
    gd_dll_node* node3 = gd_dll_push(list, string3);

    gd_dll_forEach(list, forEach_test_callback);
    TEST_ASSERT_EQUAL(3, count);
    TEST_ASSERT_EQUAL_STRING("Hwt", buffer);
}

void gdDllText_reverse_shouldReverseNodeValueOrder(void) {
    char* string1 = (char*)malloc(sizeof(char) * 6);
    char* string2 = (char*)malloc(sizeof(char) * 6);
    char* string3 = (char*)malloc(sizeof(char) * 5);
    strcpy(string1, "Hello");
    strcpy(string2, "world");
    strcpy(string3, "test");
    gd_dll_node* node1 = gd_dll_push(list, string1);
    gd_dll_node* node2 = gd_dll_push(list, string2);
    gd_dll_node* node3 = gd_dll_push(list, string3);

    gd_dll_reverse(list);
    TEST_ASSERT_EQUAL_STRING("test", node1->value);
    TEST_ASSERT_EQUAL_STRING("world", node2->value);
    TEST_ASSERT_EQUAL_STRING("Hello", node3->value);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(gdDllTest_push_shouldAppendValue);
    RUN_TEST(gdDllTest_unshift_shouldPrependValue);
    RUN_TEST(gdDllTest_pop_shouldRemoveAndReturnLastValue);
    RUN_TEST(gdDllTest_shift_shouldRemoveAndReturnFirstValue);
    RUN_TEST(gdDllTest_forEach_shouldIterateFromHeadToTail);
    RUN_TEST(gdDllTest_reverse_shouldReverseNodeValueOrder);

    return UNITY_END();
}
