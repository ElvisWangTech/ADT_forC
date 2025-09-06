#include "double_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

dl_list_t *dl_create(void)
{
    dl_list_t *list = (dl_list_t *)malloc(sizeof(dl_list_t));
    if (list == NULL)
    {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void dl_destroy(dl_list_t *list)
{
    if (list == NULL)
    {
        return;
    }
    dl_clear(list);
    free(list);
}

void dl_clear(dl_list_t *list)
{
    if (list == NULL)
    {
        return;
    }
    dl_node_t *node = list->head;
    while (node != NULL)
    {
        dl_node_t *next = node->next;
        free(node);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

size_t dl_size(dl_list_t *list)
{
    if (list == NULL)
    {
        return 0;
    }
    return list->size;
}

bool dl_is_empty(dl_list_t *list)
{
    if (list == NULL)
    {
        return true;
    }
    return list->size == 0;
}

dl_node_t *dl_node_create(void *data)
{
    dl_node_t *node = (dl_node_t *)malloc(sizeof(dl_node_t));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void dl_node_destroy(dl_node_t *node)
{
    if (node == NULL)
    {
        return;
    }
    free(node);
}

void dl_add(dl_list_t *list, dl_node_t *node, size_t index)
{
    if (list == NULL || node == NULL)
    {
        return;
    }
    
    if (index <= 0) {
        dl_add_first(list, node);
        return;
    }
    
    if (index >= list->size) {
        dl_add_last(list, node);
        return;
    }
    
    // 找到插入位置
    dl_node_t *current = list->head;
    for (size_t i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        return;
    }
    
    // 插入到current之前
    node->prev = current->prev;
    node->next = current;
    if (current->prev != NULL) {
        current->prev->next = node;
    }
    current->prev = node;
    
    if (current == list->head) {
        list->head = node;
    }
    
    list->size++;
}

void dl_add_first(dl_list_t *list, dl_node_t *node)
{
    if (list == NULL || node == NULL)
    {
        return;
    }
    
    node->prev = NULL;
    node->next = list->head;
    
    if (list->head != NULL) {
        list->head->prev = node;
    }
    
    list->head = node;
    
    if (list->tail == NULL) {
        list->tail = node;
    }
    
    list->size++;
}

void dl_add_last(dl_list_t *list, dl_node_t *node)
{
    if (list == NULL || node == NULL)
    {
        return;
    }
    
    node->prev = list->tail;
    node->next = NULL;
    
    if (list->tail != NULL) {
        list->tail->next = node;
    }
    
    list->tail = node;
    
    if (list->head == NULL) {
        list->head = node;
    }
    
    list->size++;
}

dl_node_t *dl_remove(dl_list_t *list, dl_node_t *node)
{
    if (list == NULL || node == NULL)
    {
        return NULL;
    }
    
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        // node是头节点
        list->head = node->next;
    }
    
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        // node是尾节点
        list->tail = node->prev;
    }
    
    node->prev = NULL;
    node->next = NULL;
    
    list->size--;
    return node;
}

dl_node_t *dl_remove_first(dl_list_t *list)
{
    if (list == NULL || list->head == NULL)
    {
        return NULL;
    }
    
    dl_node_t *node = list->head;
    list->head = node->next;
    
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    
    node->next = NULL;
    list->size--;
    return node;
}

dl_node_t *dl_remove_last(dl_list_t *list)
{
    if (list == NULL || list->tail == NULL)
    {
        return NULL;
    }
    
    dl_node_t *node = list->tail;
    list->tail = node->prev;
    
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    
    node->prev = NULL;
    list->size--;
    return node;
}

dl_node_t *dl_get(dl_list_t *list, size_t index)
{
    if (list == NULL || index >= list->size)
    {
        return NULL;
    }
    
    dl_node_t *node;
    
    // 根据索引位置选择从头部还是尾部开始遍历
    if (index < list->size / 2) {
        node = list->head;
        for (size_t i = 0; i < index && node != NULL; i++) {
            node = node->next;
        }
    } else {
        node = list->tail;
        for (size_t i = list->size - 1; i > index && node != NULL; i--) {
            node = node->prev;
        }
    }
    
    return node;
}

dl_node_t *dl_get_first(dl_list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->head;
}

dl_node_t *dl_get_last(dl_list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->tail;
}

size_t dl_index_of(dl_list_t *list, dl_node_t *node)
{
    if (list == NULL || node == NULL)
    {
        return (size_t)-1;
    }
    
    size_t index = 0;
    dl_node_t *current = list->head;
    
    while (current != NULL) {
        if (current == node) {
            return index;
        }
        current = current->next;
        index++;
    }
    
    return (size_t)-1;
}

void dl_foreach(dl_list_t *list, void (*func)(void *data))
{
    if (list == NULL || func == NULL)
    {
        return;
    }
    
    dl_node_t *node = list->head;
    while (node != NULL)
    {
        func(node->data);
        node = node->next;
    }
}

void dl_sort(dl_list_t *list, int (*cmp)(void *a, void *b))
{
    if (list == NULL || cmp == NULL || list->size <= 1)
    {
        return;
    }
    
    // 使用插入排序，适合链表
    dl_node_t *sorted = NULL;
    dl_node_t *current = list->head;
    
    while (current != NULL)
    {
        dl_node_t *next = current->next;
        
        // 在已排序部分中找到合适位置
        if (sorted == NULL || cmp(current->data, sorted->data) < 0)
        {
            // 插入到头部
            current->next = sorted;
            current->prev = NULL;
            if (sorted != NULL) {
                sorted->prev = current;
            }
            sorted = current;
        }
        else
        {
            // 找到插入位置
            dl_node_t *temp = sorted;
            while (temp->next != NULL && cmp(current->data, temp->next->data) >= 0)
            {
                temp = temp->next;
            }
            
            current->next = temp->next;
            current->prev = temp;
            if (temp->next != NULL) {
                temp->next->prev = current;
            }
            temp->next = current;
        }
        
        current = next;
    }
    
    // 更新链表
    list->head = sorted;
    
    // 找到尾节点
    list->tail = NULL;
    dl_node_t *temp = list->head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    list->tail = temp;
}

void dl_reverse(dl_list_t *list)
{
    if (list == NULL || list->size <= 1)
    {
        return;
    }
    
    dl_node_t *current = list->head;
    dl_node_t *temp = NULL;
    
    // 交换每个节点的prev和next指针
    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;  // 注意：prev现在是原来的next
    }
    
    // 交换头尾指针
    temp = (dl_node_t *)list->head;
    list->head = list->tail;
    list->tail = temp;
}

char *dl_to_string(dl_list_t *list, const char *format, const char *delimiter)
{
    if (list == NULL || format == NULL || delimiter == NULL)
    {
        return NULL;
    }
    
    // 计算所需缓冲区大小
    size_t total_size = 1; // 空字符串
    dl_node_t *node = list->head;
    
    while (node != NULL)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), format, node->data);
        total_size += strlen(buffer);
        
        if (node->next != NULL) {
            total_size += strlen(delimiter);
        }
        
        node = node->next;
    }
    
    char *result = (char *)malloc(total_size);
    if (result == NULL) {
        return NULL;
    }
    
    result[0] = '\0';
    node = list->head;
    
    while (node != NULL)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), format, node->data);
        strcat(result, buffer);
        
        if (node->next != NULL) {
            strcat(result, delimiter);
        }
        
        node = node->next;
    }
    
    return result;
}

void dl_print(dl_list_t *list, const char *format, const char *delimiter)
{
    if (list == NULL || format == NULL || delimiter == NULL)
    {
        return;
    }
    
    char *str = dl_to_string(list, format, delimiter);
    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    }
}

dl_node_t *dl_search(dl_list_t *list, void *data, int (*cmp)(void *a, void *b))
{
    if (list == NULL || cmp == NULL)
    {
        return NULL;
    }
    
    dl_node_t *node = list->head;
    while (node != NULL)
    {
        if (cmp(node->data, data) == 0)
        {
            return node;
        }
        node = node->next;
    }
    
    return NULL;
}

dl_node_t **dl_to_array(dl_list_t *list)
{
    if (list == NULL || list->size == 0)
    {
        return NULL;
    }
    
    dl_node_t **array = (dl_node_t **)malloc(list->size * sizeof(dl_node_t *));
    if (array == NULL) {
        return NULL;
    }
    
    dl_node_t *node = list->head;
    for (size_t i = 0; i < list->size && node != NULL; i++) {
        array[i] = node;
        node = node->next;
    }
    
    return array;
}

dl_list_t *dl_from_array(void *array[], size_t size)
{
    if (array == NULL || size == 0)
    {
        return NULL;
    }
    
    dl_list_t *list = dl_create();
    if (list == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        dl_node_t *node = dl_node_create(array[i]);
        if (node == NULL) {
            dl_destroy(list);
            return NULL;
        }
        dl_add_last(list, node);
    }
    
    return list;
}