#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для инициализации списка
void init_list(linked_list *list) {
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

// Функция для добавления элемента в начало списка
void add_to_head(linked_list *list, int value) {
  node *new_node = malloc(sizeof(node));
  new_node->data = value;
  new_node->next = list->head;
  list->head = new_node;
  if (list->tail == NULL) {
    list->tail = new_node;
  }
  list->size++;
}

// Функция для добавления элемента в конец списка
void add_to_tail(linked_list *list, int value) {
  node *new_node = malloc(sizeof(node));
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

// Функция для добавления элемента в середину списка по позиции
void add_to_middle(linked_list *list, int position, int value) {
  if (position == 0) {
    add_to_head(list, value);
    return;
  }
  if (position == list->size) {
    add_to_tail(list, value);
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

// Функция для удаления элемента по позиции
void remove_element(linked_list *list, int position) {
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

// Функция для поиска элемента по позиции
int find_element(linked_list *list, int position) {
  node *current = list->head;
  for (int i = 0; i < position; i++) {
    current = current->next;
  }
  return current->data;
}

// Функция для подсчёта количества элементов
int count_elements(linked_list *list) { return list->size; }

// Функция для вывода списка
void print_list(linked_list *list) {
  node *current = list->head;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}
    printf("\n");
}
