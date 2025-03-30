#pragma once
#include "linked_list.unity.h"

typedef struct {
    const char *id;
    int32_t value;
} TestData;

bool compare_test_data(void *a, void *b) {
    return strcmp(((TestData *)a)->id, ((TestData *)b)->id) == 0 && ((TestData *)a)->value == ((TestData *)b)->value;
}

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

    assert(LinkedList_head(NULL) == NULL);

    LinkedListNode *node = LinkedListNode_alloc(&d1);

    assert(LinkedList_head(node) == node);

    LinkedList_append(node, &d2);
    LinkedList_append(node, &d3);
    LinkedList_append(node, &d4);

    assert(LinkedList_head(node) == node);

    LinkedList_clear(node);

    node = LinkedListNode_alloc(&d1);

    assert(LinkedList_head(node) == node);

    LinkedList_prepend(node, &d2);
    LinkedList_append(node, &d3);

    LinkedListNode *new_head = LinkedList_prepend(node, &d4);

    assert(LinkedList_head(node) == new_head);

    LinkedList_clear(node);
}

void test_LinkedList_tail(void) {
    TestData d1 = {.id = "entry-1", .value = -12};
    TestData d2 = {.id = "entry-2", .value = 5};
    TestData d3 = {.id = "entry-3", .value = 16};
    TestData d4 = {.id = "entry-3", .value = 65};

    assert(LinkedList_tail(NULL) == NULL);

    LinkedListNode *node = LinkedListNode_alloc(&d1);
    LinkedListNode *tail = NULL;

    assert(LinkedList_tail(node) == node);

    LinkedList_append(node, &d2);
    LinkedList_append(node, &d3);
    tail = LinkedList_append(node, &d4);

    assert(LinkedList_tail(node) == tail);

    LinkedList_clear(node);

    node = LinkedListNode_alloc(&d1);

    assert(LinkedList_tail(node) == node);

    LinkedList_prepend(node, &d2);
    tail = LinkedList_append(node, &d3);

    assert(LinkedList_tail(node) == tail);

    LinkedList_clear(node);
}

void test_LinkedList_prepend(void) {
    TestData d1 = {.id = "entry-1", .value = -12};
    TestData d2 = {.id = "entry-2", .value = 5};
    TestData d3 = {.id = "entry-3", .value = 16};
    TestData d4 = {.id = "entry-3", .value = 65};

    LinkedListNode *node = LinkedListNode_alloc(&d1);

    LinkedList_prepend(node, &d2);
    LinkedList_prepend(node, &d3);

    assert(LinkedList_tail(node) == node);

    LinkedListNode *tail = LinkedList_append(node, &d4);

    assert(LinkedList_tail(node) == tail);

    LinkedList_clear(node);
}

void test_LinkedList_append(void) {
    TestData d1 = {.id = "entry-1", .value = -12};
    TestData d2 = {.id = "entry-2", .value = 5};
    TestData d3 = {.id = "entry-3", .value = 16};
    TestData d4 = {.id = "entry-3", .value = 65};

    LinkedListNode *node = LinkedListNode_alloc(&d1);

    LinkedList_append(node, &d2);
    LinkedList_append(node, &d3);

    assert(LinkedList_head(node) == node);

    LinkedListNode *head = LinkedList_prepend(node, &d4);

    assert(LinkedList_head(node) == head);

    LinkedList_clear(node);
}

void test_LinkedList_remove(void) {
    TestData d1 = {.id = "entry-1", .value = -12};
    TestData d2 = {.id = "entry-2", .value = 5};
    TestData d3 = {.id = "entry-3", .value = 16};
    TestData d4 = {.id = "entry-3", .value = 65};

    LinkedListNode *node = LinkedListNode_alloc(&d1);

    LinkedList_append(node, &d2);
    LinkedList_append(node, &d3);
    LinkedList_prepend(node, &d4);

    assert(LinkedList_contains(node, &d2, compare_test_data));
    assert(LinkedList_contains(node, &d3, compare_test_data));
    assert(LinkedList_contains(node, &d4, compare_test_data));

    LinkedList_remove(node, &d4);

    assert(!LinkedList_contains(node, &d4, compare_test_data));

    LinkedList_remove(node, &d2);

    assert(!LinkedList_contains(node, &d2, compare_test_data));

    LinkedList_remove(node, &d3);

    assert(!LinkedList_contains(node, &d3, compare_test_data));

    LinkedList_clear(node);
}

void test_LinkedList_reverse(void) {
    TestData d1 = {.id = "entry-1", .value = -12};
    TestData d2 = {.id = "entry-2", .value = 5};
    TestData d3 = {.id = "entry-3", .value = 16};
    TestData d4 = {.id = "entry-3", .value = 65};

    LinkedListNode *n1 = LinkedListNode_alloc(&d1);

    LinkedListNode *n2 = LinkedList_append(n1, &d2);
    LinkedListNode *n3 = LinkedList_append(n1, &d3);
    LinkedListNode *n4 = LinkedList_append(n1, &d4);

    assert(LinkedList_head(n3) == n1);

    assert(n1->next == n2);
    assert(n1->prev == NULL);
    assert(n2->next == n3);
    assert(n2->prev == n1);
    assert(n3->next == n4);
    assert(n3->prev == n2);
    assert(n4->next == NULL);
    assert(n4->prev == n3);

    LinkedListNode *new_head = LinkedList_reverse(n1);

    assert(new_head == n4);

    assert(n4->next == n3);
    assert(n4->prev == NULL);
    assert(n3->next == n2);
    assert(n3->prev == n4);
    assert(n2->next == n1);
    assert(n2->prev == n3);
    assert(n1->next == NULL);
    assert(n1->prev == n2);

    LinkedList_clear(n1);
}
