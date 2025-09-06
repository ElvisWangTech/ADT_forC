#include <stdlib.h>
#include <string.h>
#include "linked_list/single_list.h"
#include "Unity/src/unity.h"

// 测试数据
typedef struct
{
    int value;
} test_data_t;

// 比较函数
int int_cmp(void *a, void *b)
{
    int val_a = *(int *)a;
    int val_b = *(int *)b;
    return val_a - val_b;
}

// 测试数据销毁函数
void free_test_data(void *data)
{
    free(data);
}

// 测试前置和后置处理
void setUp(void)
{
    // 每个测试前的初始化
}

void tearDown(void)
{
    // 每个测试后的清理
}

// 测试链表创建
void test_sl_create_should_create_empty_list(void)
{
    sl_list_t *list = sl_create();

    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
    TEST_ASSERT_EQUAL(0, sl_size(list));

    sl_destroy(list);
}

// 测试节点创建
void test_sl_node_create_should_create_node_with_data(void)
{
    int *data = malloc(sizeof(int));
    *data = 42;

    sl_node_t *node = sl_node_create(data);

    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL_PTR(data, node->data);
    TEST_ASSERT_NULL(node->next);

    sl_node_destroy(node);
    free(data);
}

// 测试添加节点到链表头部
void test_sl_add_first_should_add_node_to_empty_list(void)
{
    sl_list_t *list = sl_create();
    int *data = malloc(sizeof(int));
    *data = 10;

    sl_node_t *node = sl_node_create(data);
    sl_add_first(list, node);

    TEST_ASSERT_EQUAL(1, sl_size(list));
    TEST_ASSERT_EQUAL_PTR(node, list->head);
    TEST_ASSERT_EQUAL_PTR(node, list->tail);
    TEST_ASSERT_NULL(node->next);

    sl_destroy(list);
    free(data);
}

// 测试添加多个节点到链表头部
void test_sl_add_first_should_add_multiple_nodes_in_reverse_order(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;
    int *data3 = malloc(sizeof(int));
    *data3 = 3;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);
    sl_node_t *node3 = sl_node_create(data3);

    sl_add_first(list, node1);
    sl_add_first(list, node2);
    sl_add_first(list, node3);

    TEST_ASSERT_EQUAL(3, sl_size(list));
    TEST_ASSERT_EQUAL_PTR(node3, list->head);
    TEST_ASSERT_EQUAL_PTR(node1, list->tail);

    TEST_ASSERT_EQUAL(3, *(int *)list->head->data);
    TEST_ASSERT_EQUAL(2, *(int *)list->head->next->data);
    TEST_ASSERT_EQUAL(1, *(int *)list->tail->data);

    sl_destroy(list);
    free(data1);
    free(data2);
    free(data3);
}

// 测试添加节点到链表尾部
void test_sl_add_last_should_add_node_to_empty_list(void)
{
    sl_list_t *list = sl_create();
    int *data = malloc(sizeof(int));
    *data = 10;

    sl_node_t *node = sl_node_create(data);
    sl_add_last(list, node);

    TEST_ASSERT_EQUAL(1, sl_size(list));
    TEST_ASSERT_EQUAL_PTR(node, list->head);
    TEST_ASSERT_EQUAL_PTR(node, list->tail);
    TEST_ASSERT_NULL(node->next);

    sl_destroy(list);
    free(data);
}

// 测试在指定位置添加节点
void test_sl_add_should_add_node_at_specific_index(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;
    int *data3 = malloc(sizeof(int));
    *data3 = 3;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);
    sl_node_t *node3 = sl_node_create(data3);

    sl_add_first(list, node1);
    sl_add_last(list, node3);
    sl_add(list, node2, 1); // 插入到中间

    TEST_ASSERT_EQUAL(3, sl_size(list));
    TEST_ASSERT_EQUAL(1, *(int *)sl_get_first(list)->data);
    TEST_ASSERT_EQUAL(2, *(int *)sl_get(list, 1)->data);
    TEST_ASSERT_EQUAL(3, *(int *)sl_get_last(list)->data);

    sl_destroy(list);
    free(data1);
    free(data2);
    free(data3);
}

// 测试移除节点
void test_sl_remove_should_remove_node_from_list(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);

    sl_add_first(list, node1);
    sl_add_last(list, node2);

    sl_node_t *removed = sl_remove(list, node1);

    TEST_ASSERT_EQUAL_PTR(node1, removed);
    TEST_ASSERT_EQUAL(1, sl_size(list));
    TEST_ASSERT_EQUAL_PTR(node2, list->head);
    TEST_ASSERT_EQUAL_PTR(node2, list->tail);
    TEST_ASSERT_NULL(node2->next);

    sl_destroy(list);
    free(data1);
    free(data2);
}

// 测试移除头节点
void test_sl_remove_first_should_remove_head_node(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);

    sl_add_first(list, node1);
    sl_add_last(list, node2);

    sl_node_t *removed = sl_remove_first(list);

    TEST_ASSERT_EQUAL_PTR(node1, removed);
    TEST_ASSERT_EQUAL(1, sl_size(list));
    TEST_ASSERT_EQUAL_PTR(node2, list->head);
    TEST_ASSERT_EQUAL_PTR(node2, list->tail);

    sl_destroy(list);
    free(data1);
    free(data2);
}

// 测试移除尾节点
void test_sl_remove_last_should_remove_tail_node(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);

    sl_add_first(list, node1);
    sl_add_last(list, node2);

    sl_node_t *removed = sl_remove_last(list);

    TEST_ASSERT_EQUAL_PTR(node2, removed);
    TEST_ASSERT_EQUAL(1, sl_size(list));
    TEST_ASSERT_EQUAL_PTR(node1, list->head);
    TEST_ASSERT_EQUAL_PTR(node1, list->tail);
    TEST_ASSERT_NULL(node1->next);

    sl_destroy(list);
    free(data1);
    free(data2);
}

// 测试获取节点
void test_sl_get_should_return_node_at_index(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 10;
    int *data2 = malloc(sizeof(int));
    *data2 = 20;
    int *data3 = malloc(sizeof(int));
    *data3 = 30;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);
    sl_node_t *node3 = sl_node_create(data3);

    sl_add_first(list, node1);
    sl_add_last(list, node2);
    sl_add_last(list, node3);

    TEST_ASSERT_EQUAL_PTR(node1, sl_get(list, 0));
    TEST_ASSERT_EQUAL_PTR(node2, sl_get(list, 1));
    TEST_ASSERT_EQUAL_PTR(node3, sl_get(list, 2));

    sl_destroy(list);
    free(data1);
    free(data2);
    free(data3);
}

// 测试获取节点索引
void test_sl_index_of_should_return_correct_index(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 10;
    int *data2 = malloc(sizeof(int));
    *data2 = 20;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);

    sl_add_first(list, node1);
    sl_add_last(list, node2);

    TEST_ASSERT_EQUAL(0, sl_index_of(list, node1));
    TEST_ASSERT_EQUAL(1, sl_index_of(list, node2));
    TEST_ASSERT_EQUAL((size_t)-1, sl_index_of(list, NULL));

    sl_destroy(list);
    free(data1);
    free(data2);
}

// 测试链表反转
void test_sl_reverse_should_reverse_list_order(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;
    int *data3 = malloc(sizeof(int));
    *data3 = 3;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);
    sl_node_t *node3 = sl_node_create(data3);

    sl_add_first(list, node1);
    sl_add_last(list, node2);
    sl_add_last(list, node3);

    sl_reverse(list);

    TEST_ASSERT_EQUAL(3, *(int *)sl_get_first(list)->data);
    TEST_ASSERT_EQUAL(2, *(int *)sl_get(list, 1)->data);
    TEST_ASSERT_EQUAL(1, *(int *)sl_get_last(list)->data);

    sl_destroy(list);
    free(data1);
    free(data2);
    free(data3);
}

// 测试链表排序
void test_sl_sort_should_sort_list_in_ascending_order(void)
{
    sl_list_t *list = sl_create();

    int *data3 = malloc(sizeof(int));
    *data3 = 3;
    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data4 = malloc(sizeof(int));
    *data4 = 4;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;

    sl_node_t *node3 = sl_node_create(data3);
    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node4 = sl_node_create(data4);
    sl_node_t *node2 = sl_node_create(data2);

    sl_add_first(list, node3);
    sl_add_last(list, node1);
    sl_add_last(list, node4);
    sl_add_last(list, node2);

    sl_sort(list, int_cmp);

    TEST_ASSERT_EQUAL(1, *(int *)sl_get_first(list)->data);
    TEST_ASSERT_EQUAL(2, *(int *)sl_get(list, 1)->data);
    TEST_ASSERT_EQUAL(3, *(int *)sl_get(list, 2)->data);
    TEST_ASSERT_EQUAL(4, *(int *)sl_get_last(list)->data);

    sl_destroy(list);
    free(data1);
    free(data2);
    free(data3);
    free(data4);
}

// 测试链表搜索
void test_sl_search_should_find_existing_node(void)
{
    sl_list_t *list = sl_create();

    int target = 42;
    int *data1 = malloc(sizeof(int));
    *data1 = 10;
    int *data2 = malloc(sizeof(int));
    *data2 = 42;
    int *data3 = malloc(sizeof(int));
    *data3 = 30;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);
    sl_node_t *node3 = sl_node_create(data3);

    sl_add_first(list, node1);
    sl_add_last(list, node2);
    sl_add_last(list, node3);

    sl_node_t *found = sl_search(list, &target, int_cmp);

    TEST_ASSERT_EQUAL_PTR(node2, found);
    TEST_ASSERT_EQUAL(42, *(int *)found->data);

    sl_destroy(list);
    free(data1);
    free(data2);
    free(data3);
}

// 测试链表清空
void test_sl_clear_should_remove_all_nodes(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);

    sl_add_first(list, node1);
    sl_add_last(list, node2);

    sl_clear(list);

    TEST_ASSERT_EQUAL(0, sl_size(list));
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);

    sl_destroy(list);
    free(data1);
    free(data2);
}

// 测试链表转数组
void test_sl_to_array_should_convert_list_to_array(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;
    int *data3 = malloc(sizeof(int));
    *data3 = 3;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);
    sl_node_t *node3 = sl_node_create(data3);

    sl_add_first(list, node1);
    sl_add_last(list, node2);
    sl_add_last(list, node3);

    sl_node_t **array = sl_to_array(list);

    TEST_ASSERT_NOT_NULL(array);
    TEST_ASSERT_EQUAL_PTR(node1, array[0]);
    TEST_ASSERT_EQUAL_PTR(node2, array[1]);
    TEST_ASSERT_EQUAL_PTR(node3, array[2]);

    free(array);
    sl_destroy(list);
    free(data1);
    free(data2);
    free(data3);
}

// 测试数组转链表
void test_sl_from_array_should_create_list_from_array(void)
{
    void *array[3];
    int data1 = 1, data2 = 2, data3 = 3;

    array[0] = &data1;
    array[1] = &data2;
    array[2] = &data3;

    sl_list_t *list = sl_from_array(array, 3);

    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(3, sl_size(list));
    TEST_ASSERT_EQUAL(1, *(int *)sl_get_first(list)->data);
    TEST_ASSERT_EQUAL(3, *(int *)sl_get_last(list)->data);

    sl_destroy(list);
}

// 测试边界条件
void test_sl_edge_cases_should_handle_null_inputs(void)
{
    sl_list_t *list = sl_create();

    // 测试空链表的各种操作
    TEST_ASSERT_NULL(sl_get_first(NULL));
    TEST_ASSERT_NULL(sl_get_last(NULL));
    TEST_ASSERT_NULL(sl_remove_first(NULL));
    TEST_ASSERT_NULL(sl_remove_last(NULL));
    TEST_ASSERT_EQUAL(0, sl_size(NULL));
    TEST_ASSERT_TRUE(sl_is_empty(NULL));

    // 测试空链表遍历
    sl_foreach(NULL, free_test_data); // 应该不崩溃

    sl_destroy(list);
}

// 测试字符串表示
void test_sl_to_string_should_create_correct_format(void)
{
    sl_list_t *list = sl_create();

    int data1 = 10;
    int data2 = 20;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);

    sl_add_first(list, node1);
    sl_add_last(list, node2);

    char *str = sl_to_string(list, "%d", ", ");

    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("10, 20", str);

    free(str);
    sl_destroy(list);
}

long sum = 0;
void sum_data(void *data)
{
    int *d = (int *)data;
    sum += *d;
}

// 测试链表遍历
void test_sl_foreach_should_visit_all_nodes(void)
{
    sl_list_t *list = sl_create();

    int *data1 = malloc(sizeof(int));
    *data1 = 1;
    int *data2 = malloc(sizeof(int));
    *data2 = 2;
    int *data3 = malloc(sizeof(int));
    *data3 = 3;

    sl_node_t *node1 = sl_node_create(data1);
    sl_node_t *node2 = sl_node_create(data2);
    sl_node_t *node3 = sl_node_create(data3);

    sl_add_first(list, node1);
    sl_add_last(list, node2);
    sl_add_last(list, node3);

    // 使用遍历功能收集数据
    sum = 0;
    sl_foreach(list, sum_data);

    TEST_ASSERT_EQUAL(6, sum);

    sl_destroy(list);
    free(data1);
    free(data2);
    free(data3);
}

// 测试链表大小检查
void test_sl_is_empty_should_return_true_for_empty_list(void)
{
    sl_list_t *list = sl_create();

    TEST_ASSERT_TRUE(sl_is_empty(list));

    int *data = malloc(sizeof(int));
    *data = 1;
    sl_node_t *node = sl_node_create(data);

    sl_add_first(list, node);
    TEST_ASSERT_FALSE(sl_is_empty(list));

    sl_remove_first(list);
    TEST_ASSERT_TRUE(sl_is_empty(list));

    sl_destroy(list);
    free(data);
}

// 测试运行器
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_sl_create_should_create_empty_list);
    RUN_TEST(test_sl_node_create_should_create_node_with_data);
    RUN_TEST(test_sl_add_first_should_add_node_to_empty_list);
    RUN_TEST(test_sl_add_first_should_add_multiple_nodes_in_reverse_order);
    RUN_TEST(test_sl_add_last_should_add_node_to_empty_list);
    RUN_TEST(test_sl_add_should_add_node_at_specific_index);
    RUN_TEST(test_sl_remove_should_remove_node_from_list);
    RUN_TEST(test_sl_remove_first_should_remove_head_node);
    RUN_TEST(test_sl_remove_last_should_remove_tail_node);
    RUN_TEST(test_sl_get_should_return_node_at_index);
    RUN_TEST(test_sl_index_of_should_return_correct_index);
    RUN_TEST(test_sl_reverse_should_reverse_list_order);
    RUN_TEST(test_sl_sort_should_sort_list_in_ascending_order);
    RUN_TEST(test_sl_search_should_find_existing_node);
    RUN_TEST(test_sl_clear_should_remove_all_nodes);
    RUN_TEST(test_sl_to_array_should_convert_list_to_array);
    RUN_TEST(test_sl_from_array_should_create_list_from_array);
    RUN_TEST(test_sl_edge_cases_should_handle_null_inputs);
    RUN_TEST(test_sl_to_string_should_create_correct_format);
    RUN_TEST(test_sl_is_empty_should_return_true_for_empty_list);

    return UNITY_END();
}
