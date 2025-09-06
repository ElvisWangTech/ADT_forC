#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__

#include <stddef.h>
#include <stdbool.h>

// 双向链表节点
typedef struct dl_node
{
    struct dl_node *prev;
    struct dl_node *next;
    void *data;
} dl_node_t;

// 双向链表
typedef struct dl_list
{
    dl_node_t *head;
    dl_node_t *tail;
    size_t size;
} dl_list_t;

dl_list_t *dl_create(void);
void dl_destroy(dl_list_t *list);
void dl_clear(dl_list_t *list);
size_t dl_size(dl_list_t *list);
bool dl_is_empty(dl_list_t *list);

dl_node_t *dl_node_create(void *data);
void dl_node_destroy(dl_node_t *node);
void dl_add(dl_list_t *list, dl_node_t *node, size_t index);
void dl_add_first(dl_list_t *list, dl_node_t *node);
void dl_add_last(dl_list_t *list, dl_node_t *node);
dl_node_t *dl_remove(dl_list_t *list, dl_node_t *node);
dl_node_t *dl_remove_first(dl_list_t *list);
dl_node_t *dl_remove_last(dl_list_t *list);
dl_node_t *dl_get(dl_list_t *list, size_t index);
dl_node_t *dl_get_first(dl_list_t *list);
dl_node_t *dl_get_last(dl_list_t *list);
size_t dl_index_of(dl_list_t *list, dl_node_t *node);
void dl_foreach(dl_list_t *list, void (*func)(void *data));
void dl_sort(dl_list_t *list, int (*cmp)(void *a, void *b));
void dl_reverse(dl_list_t *list);
char *dl_to_string(dl_list_t *list, const char *format, const char *delimiter);
void dl_print(dl_list_t *list, const char *format, const char *delimiter);
dl_node_t *dl_search(dl_list_t *list, void *data, int (*cmp)(void *a, void *b));
dl_node_t **dl_to_array(dl_list_t *list);
dl_list_t *dl_from_array(void *array[], size_t size);

#endif // __DOUBLE_LIST_H__