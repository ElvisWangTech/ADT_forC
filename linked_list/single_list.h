#ifndef __SINGLE_LIST_H__
#define __SINGLE_LIST_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct sl_node {
    struct sl_node *next;
    void *data;
} sl_node_t;

typedef struct sl_list {
    sl_node_t *head;
    sl_node_t *tail;
    size_t size;
} sl_list_t;

sl_list_t *sl_create(void);
void sl_destroy(sl_list_t *list);
void sl_clear(sl_list_t *list);
size_t sl_size(sl_list_t *list);
bool sl_is_empty(sl_list_t *list);

sl_node_t *sl_node_create(void *data);
void sl_node_destroy(sl_node_t *node);
void sl_add(sl_list_t *list, sl_node_t *node, size_t index);
void sl_add_first(sl_list_t *list, sl_node_t *node);
void sl_add_last(sl_list_t *list, sl_node_t *node);
sl_node_t *sl_remove(sl_list_t *list, sl_node_t *node);
sl_node_t *sl_remove_first(sl_list_t *list);
sl_node_t *sl_remove_last(sl_list_t *list);
sl_node_t *sl_get(sl_list_t *list, size_t index);
sl_node_t *sl_get_first(sl_list_t *list);
sl_node_t *sl_get_last(sl_list_t *list);
size_t sl_index_of(sl_list_t *list, sl_node_t *node);
void sl_foreach(sl_list_t *list, void (*func)(void *data));
void sl_sort(sl_list_t *list, int (*cmp)(void *a, void *b));
void sl_reverse(sl_list_t *list);
char *sl_to_string(sl_list_t *list, const char *format, const char *delimiter);
void sl_print(sl_list_t *list, const char *format, const char *delimiter);
sl_node_t *sl_search(sl_list_t *list, void *data, int (*cmp)(void *a, void *b));
sl_node_t **sl_to_array(sl_list_t *list);
sl_list_t *sl_from_array(void *array[], size_t size);

#endif // __SINGLE_LIST_H__