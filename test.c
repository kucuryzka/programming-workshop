#include <assert.h>
#include <stdio.h>
#include "functions.h"

void test_init_list() {
    linked_list list;
    init_list(&list);
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.size == 0);
}

void test_add_to_head() {
    linked_list list;
    init_list(&list);
    add_to_head(&list, 10);
    assert(list.head->data == 10);
    assert(list.tail->data == 10);
    assert(list.size == 1);
}

void test_add_to_tail() {
    linked_list list;
    init_list(&list);
    add_to_tail(&list, 10);
    assert(list.head->data == 10);
    assert(list.tail->data == 10);
    assert(list.size == 1);
}

void test_add_to_middle() {
    linked_list list;
    init_list(&list);
    add_to_head(&list, 10);
    add_to_tail(&list, 20);
    add_to_middle(&list, 1, 15);
    assert(list.head->data == 10);
    assert(list.head->next->data == 15);
    assert(list.tail->data == 20);
    assert(list.size == 3);
}

void test_remove_element() {
    linked_list list;
    init_list(&list);
    add_to_head(&list, 10);
    add_to_tail(&list, 20);
    remove_element(&list, 0);
    assert(list.head->data == 20);
    assert(list.tail->data == 20);
    assert(list.size == 1);
}

void test_find_element() {
    linked_list list;
    init_list(&list);
    add_to_head(&list, 10);
    add_to_tail(&list, 20);
    assert(find_element(&list, 0) == 10);
    assert(find_element(&list, 1) == 20);
}

void test_count_elements() {
    linked_list list;
    init_list(&list);
    add_to_head(&list, 10);
    add_to_tail(&list, 20);
    assert(count_elements(&list) == 2);
}

int main() {
    test_init_list();
    test_add_to_head();
    test_add_to_tail();
    test_add_to_middle();
    test_remove_element();
    test_find_element();
    test_count_elements();

    return 0;
}
