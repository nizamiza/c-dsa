#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct LinkedListNode LinkedListNode;

LinkedListNode *LinkedListNode_alloc(void *data);
LinkedListNode *LinkedList_head(LinkedListNode *node);
LinkedListNode *LinkedList_tail(LinkedListNode *node);
LinkedListNode *LinkedList_prepend(LinkedListNode *node, void *data);
LinkedListNode *LinkedList_append(LinkedListNode *node, void *data);
LinkedListNode *LinkedList_remove(LinkedListNode *node, void *data);
void LinkedList_clear(LinkedListNode *node);
bool LinkedList_contains(LinkedListNode *node, void *data, bool (*compare)(void *, void *));
LinkedListNode *LinkedList_reverse(LinkedListNode *node);

void test_LinkedList_alloc(void);
void test_LinkedList_head(void);

#include "linked_list.c"
#include "linked_list.test.c"
