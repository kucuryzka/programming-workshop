#include "list_f.h"
#include <stdio.h>
#include <stdlib.h>

void init_list(linked_list *list) {
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void add_to_head(linked_list *list, int value) {
  node *new_node = malloc(sizeof(node));
  if (!new_node) {
    return;
  }

  new_node->data = value;
  new_node->next = list->head;
  list->head = new_node;
  if (list->tail == NULL) {
    list->tail = new_node;
  }
  list->size++;
}

void add_to_tail(linked_list *list, int value) {
  node *new_node = malloc(sizeof(node));
  if (!new_node) {
    return;
  }

  new_node->data = value;
  new_node->next = NULL;
  if (list->head == NULL) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
  }
  list->size++;
}

void add_to_middle(linked_list *list, int position, int value) {
  if (position == 0) {
    add_to_head(list, value);
    return;
  }
  if (position == list->size) {
    add_to_tail(list, value);
    return;
  }

  if (position > list->size || position < 0) {
    return;
  }

  node *new_node = malloc(sizeof(node));
  new_node->data = value;
  node *current = list->head;
  for (int i = 0; i < position - 1; i++) {
    current = current->next;
  }
  new_node->next = current->next;
  current->next = new_node;
  list->size++;
}

void remove_element(linked_list *list, int position) {
  if (position > list->size || position < 0) {
    return;
  }

  if (position == 0) {
    node *temp = list->head;
    list->head = list->head->next;
    free(temp);
    if (list->head == NULL) {
      list->tail = NULL;
    }
  } else {
    node *current = list->head;
    for (int i = 0; i < position - 1; i++) {
      current = current->next;
    }
    node *temp = current->next;
    current->next = current->next->next;
    free(temp);
    if (current->next == NULL) {
      list->tail = current;
    }
  }
  list->size--;
}

int find_element(linked_list *list, int position) {
  if (position > list->size || position < 0) {
    return -1;
  }

  node *current = list->head;
  for (int i = 0; i < position; i++) {
    current = current->next;
  }
  return current->data;
}

int count_elements(linked_list *list) { return list->size; }
