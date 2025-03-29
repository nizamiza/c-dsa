#pragma once
#include "linked_list.unity.h"

typedef struct LinkedListNode LinkedListNode;

struct LinkedListNode {
    struct LinkedListNode *prev;
    struct LinkedListNode *next;
    void *data;
};

LinkedListNode *LinkedListNode_alloc(void *data) {
    LinkedListNode *node = (LinkedListNode *)malloc(sizeof(LinkedListNode));

    if (!node) {
        return NULL;
    }

    node->prev = NULL;
    node->next = NULL;
    node->data = data;

    return node;
}

LinkedListNode *LinkedList_head(LinkedListNode *node) {
    if (!node) {
        return NULL;
    }

    while (node->prev) {
        node = node->prev;
    }

    return node;
}

LinkedListNode *LinkedList_tail(LinkedListNode *node) {
    if (!node) {
        return NULL;
    }

    while (node->next) {
        node = node->next;
    }

    return node;
}

LinkedListNode *LinkedList_prepend(LinkedListNode *node, void *data) {
    if (!node) {
        return LinkedListNode_alloc(data);
    }

    LinkedListNode *head = LinkedList_head(node);
    LinkedListNode *new_node = LinkedListNode_alloc(data);

    if (!new_node) {
        return NULL;
    }

    new_node->next = head;
    head->prev = new_node;

    return new_node;
}

LinkedListNode *LinkedList_append(LinkedListNode *node, void *data) {
    if (!node) {
        return LinkedListNode_alloc(data);
    }

    LinkedListNode *tail = LinkedList_tail(node);
    LinkedListNode *new_node = LinkedListNode_alloc(data);

    if (!new_node) {
        return NULL;
    }

    new_node->prev = tail;
    tail->next = new_node;

    return new_node;
}

LinkedListNode *LinkedList_remove(LinkedListNode *node, void *data) {
    if (!node) {
        return NULL;
    }

    LinkedListNode *current = LinkedList_head(node);

    while (current && current->data != data) {
        current = current->next;
    }

    if (!current) {
        return node;
    }

    if (!current->prev && !current->next) {
        goto free_and_return;
    }

    if (!current->next) {
        current->prev->next = NULL;
    } else if (!current->prev) {
        current->next->prev = NULL;
        node = current->next;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

free_and_return:
    free(current);
    return node;
}

void LinkedList_clear(LinkedListNode *node) {
    if (!node) {
        return;
    }

    LinkedListNode *current = LinkedList_head(node);
    LinkedListNode *next = NULL;

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }

    node = NULL;
    return;
}

bool LinkedList_contains(LinkedListNode *node, void *data, bool (*compare)(void *, void *)) {
    if (!node) {
        return false;
    }

    LinkedListNode *current = LinkedList_head(node);

    while (current) {
        if (compare(current->data, data)) {
            return true;
        }

        current = current->next;
    }

    return false;
}

LinkedListNode *LinkedList_reverse(LinkedListNode *node) {
    if (!node) {
        return NULL;
    }

    LinkedListNode *current = LinkedList_tail(node);
    LinkedListNode *new_prev = NULL;
    LinkedListNode *new_next = NULL;

    while (current) {
        new_prev = current->next;
        new_next = current->prev;

        current->next = current->prev;
        current->prev = new_prev;

        current = new_next;
    }

    return LinkedList_head(node);
}
