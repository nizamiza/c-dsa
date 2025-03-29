#include "linked_list.unity.h"

int main(void) {
    test_LinkedList_alloc();
    test_LinkedList_head();
    test_LinkedList_tail();
    test_LinkedList_prepend();
    test_LinkedList_append();
    test_LinkedList_remove();
    test_LinkedList_reverse();

    return 0;
}
