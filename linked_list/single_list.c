#include "single_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// 创建新链表
sl_list_t *sl_create(void)
{
    sl_list_t *list = (sl_list_t *)malloc(sizeof(sl_list_t));
    if (list == NULL)
    {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// 销毁链表
void sl_destroy(sl_list_t *list)
{
    if (list == NULL)
    {
        return;
    }
    sl_clear(list);
    free(list);
}

// 清空链表
void sl_clear(sl_list_t *list)
{
    if (list == NULL)
    {
        return;
    }
    sl_node_t *node = list->head;
    while (node != NULL)
    {
        sl_node_t *next = node->next;
        free(node);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// 获取链表大小
size_t sl_size(sl_list_t *list)
{
    if (list == NULL)
    {
        return 0;
    }
    return list->size;
}

// 检查链表是否为空
bool sl_is_empty(sl_list_t *list)
{
    if (list == NULL)
    {
        return true;
    }
    return list->size == 0;
}

// 创建新节点
sl_node_t *sl_node_create(void *data)
{
    sl_node_t *node = (sl_node_t *)malloc(sizeof(sl_node_t));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

// 销毁节点
void sl_node_destroy(sl_node_t *node)
{
    if (node == NULL)
    {
        return;
    }
    free(node);
}

// 在指定位置添加节点
void sl_add(sl_list_t *list, sl_node_t *node, size_t index)
{
    if (list == NULL || node == NULL)
    {
        return;
    }

    if (index <= 0 || list->head == NULL)
    {
        sl_add_first(list, node);
        return;
    }

    if (index >= list->size)
    {
        sl_add_last(list, node);
        return;
    }

    sl_node_t *current = list->head;
    for (size_t i = 0; i < index - 1 && current != NULL; i++)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        return;
    }

    node->next = current->next;
    current->next = node;
    list->size++;
}

// 在链表头部添加节点
void sl_add_first(sl_list_t *list, sl_node_t *node)
{
    if (list == NULL || node == NULL)
    {
        return;
    }

    node->next = list->head;
    list->head = node;

    if (list->tail == NULL)
    {
        list->tail = node;
    }

    list->size++;
}

// 在链表尾部添加节点
void sl_add_last(sl_list_t *list, sl_node_t *node)
{
    if (list == NULL || node == NULL)
    {
        return;
    }

    if (list->tail == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

// 移除指定节点
sl_node_t *sl_remove(sl_list_t *list, sl_node_t *node)
{
    if (list == NULL || node == NULL)
    {
        return NULL;
    }

    if (list->head == node)
    {
        return sl_remove_first(list);
    }

    sl_node_t *current = list->head;
    while (current != NULL && current->next != node)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        return NULL;
    }

    current->next = node->next;
    if (node == list->tail)
    {
        list->tail = current;
    }

    node->next = NULL;
    list->size--;
    return node;
}

// 移除头节点
sl_node_t *sl_remove_first(sl_list_t *list)
{
    if (list == NULL || list->head == NULL)
    {
        return NULL;
    }

    sl_node_t *node = list->head;
    list->head = node->next;

    if (list->head == NULL)
    {
        list->tail = NULL;
    }

    node->next = NULL;
    list->size--;
    return node;
}

// 移除尾节点
sl_node_t *sl_remove_last(sl_list_t *list)
{
    if (list == NULL || list->head == NULL)
    {
        return NULL;
    }

    if (list->head == list->tail)
    {
        return sl_remove_first(list);
    }

    sl_node_t *current = list->head;
    while (current->next != list->tail)
    {
        current = current->next;
    }

    sl_node_t *node = list->tail;
    current->next = NULL;
    list->tail = current;
    list->size--;
    return node;
}

// 获取指定位置的节点
sl_node_t *sl_get(sl_list_t *list, size_t index)
{
    if (list == NULL || index >= list->size)
    {
        return NULL;
    }

    sl_node_t *node = list->head;
    for (size_t i = 0; i < index && node != NULL; i++)
    {
        node = node->next;
    }

    return node;
}

// 获取头节点
sl_node_t *sl_get_first(sl_list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->head;
}

// 获取尾节点
sl_node_t *sl_get_last(sl_list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->tail;
}

// 获取节点索引
size_t sl_index_of(sl_list_t *list, sl_node_t *node)
{
    if (list == NULL || node == NULL)
    {
        return (size_t)-1;
    }

    size_t index = 0;
    sl_node_t *current = list->head;

    while (current != NULL)
    {
        if (current == node)
        {
            return index;
        }
        current = current->next;
        index++;
    }

    return (size_t)-1;
}

// 遍历链表
void sl_foreach(sl_list_t *list, void (*func)(void *data))
{
    if (list == NULL || func == NULL)
    {
        return;
    }

    sl_node_t *node = list->head;
    while (node != NULL)
    {
        func(node->data);
        node = node->next;
    }
}

// 排序链表（插入排序）
void sl_sort(sl_list_t *list, int (*cmp)(void *a, void *b))
{
    if (list == NULL || cmp == NULL || list->size <= 1)
    {
        return;
    }

    sl_node_t *sorted = NULL;
    sl_node_t *current = list->head;

    while (current != NULL)
    {
        sl_node_t *next = current->next;

        // 在已排序部分中找到合适位置
        if (sorted == NULL || cmp(current->data, sorted->data) < 0)
        {
            // 插入到头部
            current->next = sorted;
            sorted = current;
        }
        else
        {
            // 找到插入位置
            sl_node_t *temp = sorted;
            while (temp->next != NULL && cmp(current->data, temp->next->data) >= 0)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    // 更新链表
    list->head = sorted;

    // 找到尾节点
    list->tail = NULL;
    sl_node_t *temp = list->head;
    while (temp != NULL && temp->next != NULL)
    {
        temp = temp->next;
    }
    list->tail = temp;
}

// 反转链表
void sl_reverse(sl_list_t *list)
{
    if (list == NULL || list->size <= 1)
    {
        return;
    }

    sl_node_t *prev = NULL;
    sl_node_t *current = list->head;
    sl_node_t *next = NULL;

    list->tail = list->head;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;
}

// 转换为字符串表示
char *sl_to_string(sl_list_t *list, const char *format, const char *delimiter)
{
    if (list == NULL || format == NULL || delimiter == NULL)
    {
        return NULL;
    }

    // 计算所需缓冲区大小
    size_t total_size = 1; // 空字符串
    sl_node_t *node = list->head;

    while (node != NULL)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), format, node->data);
        total_size += strlen(buffer);

        if (node->next != NULL)
        {
            total_size += strlen(delimiter);
        }

        node = node->next;
    }

    char *result = (char *)malloc(total_size);
    if (result == NULL)
    {
        return NULL;
    }

    result[0] = '\0';
    node = list->head;

    while (node != NULL)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), format, node->data);
        strcat(result, buffer);

        if (node->next != NULL)
        {
            strcat(result, delimiter);
        }

        node = node->next;
    }

    return result;
}

// 打印链表
void sl_print(sl_list_t *list, const char *format, const char *delimiter)
{
    if (list == NULL || format == NULL || delimiter == NULL)
    {
        return;
    }

    char *str = sl_to_string(list, format, delimiter);
    if (str != NULL)
    {
        printf("%s\n", str);
        free(str);
    }
}

// 搜索节点
sl_node_t *sl_search(sl_list_t *list, void *data, int (*cmp)(void *a, void *b))
{
    if (list == NULL || cmp == NULL)
    {
        return NULL;
    }

    sl_node_t *node = list->head;
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

// 转换为数组
sl_node_t **sl_to_array(sl_list_t *list)
{
    if (list == NULL || list->size == 0)
    {
        return NULL;
    }

    sl_node_t **array = (sl_node_t **)malloc(list->size * sizeof(sl_node_t *));
    if (array == NULL)
    {
        return NULL;
    }

    sl_node_t *node = list->head;
    for (size_t i = 0; i < list->size && node != NULL; i++)
    {
        array[i] = node;
        node = node->next;
    }

    return array;
}

// 从数组创建链表
sl_list_t *sl_from_array(void *array[], size_t size)
{
    if (array == NULL || size == 0)
    {
        return NULL;
    }

    sl_list_t *list = sl_create();
    if (list == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        sl_node_t *node = sl_node_create(array[i]);
        if (node == NULL)
        {
            sl_destroy(list);
            return NULL;
        }
        sl_add_last(list, node);
    }

    return list;
}