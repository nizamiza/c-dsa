#include "../shared/test.c"
#include "./linked_list.test.c"

int main(void) {
    if (!test_LinkedList_alloc()) {
        print_failed_test("LinkedList_alloc");
    }

    return 0;
}
