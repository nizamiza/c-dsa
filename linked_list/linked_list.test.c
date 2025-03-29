#include "./linked_list.c"
#include "../shared/string.c"
#include <assert.h>

typedef struct {
    String *id;
    int32_t value;
} Data;

bool test_LinkedList_alloc(void) {
    Data sample = {.id = String_new("alloc-test"), .value = 32};

    LinkedListNode *node = LinkedListNode_alloc(&sample);

    assert(node != NULL);
    assert(node->data == &sample);
    assert(node->prev == NULL);
    assert(node->next == NULL);

    free(node);

    return true;
}
