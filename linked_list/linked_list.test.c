#pragma once
#include "linked_list.unity.h"

typedef struct {
    const char *id;
    int32_t value;
} TestData;

void test_LinkedList_alloc(void) {
    TestData sample = {.id = "alloc-test", .value = 32};

    LinkedListNode *node = LinkedListNode_alloc(&sample);

    assert(node != NULL);
    assert(node->data == &sample);
    assert(node->prev == NULL);
    assert(node->next == NULL);

    LinkedList_clear(node);
}

void test_LinkedList_head(void) {
    TestData d1 = {.id = "entry-1", .value = -12};
    TestData d2 = {.id = "entry-2", .value = 5};
    TestData d3 = {.id = "entry-3", .value = 16};
    TestData d4 = {.id = "entry-3", .value = 65};

    LinkedListNode *node = LinkedListNode_alloc(&d1);

    LinkedList_append(node, &d2);
    LinkedList_append(node, &d3);
    LinkedList_append(node, &d4);

    assert(LinkedList_head(node) == node);
}
