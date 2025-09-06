#include <stdlib.h>
#include "linked_list/double_list.h"
#include "Unity/src/unity.h"

// 测试数据
typedef struct {
    int value;
} test_data_t;

// 比较函数
int int_cmp(void* a, void* b) {
    int val_a = *(int*)a;
    int val_b = *(int*)b;
    return val_a - val_b;
}

// 测试数据销毁函数
void free_test_data(void* data) {
    free(data);
}

// 测试前置和后置处理
void setUp(void) {
    // 每个测试前的初始化
}

void tearDown(void) {
    // 每个测试后的清理
}

// 测试链表创建
void test_list_create_should_create_empty_list(void) {
    dl_list_t* list = dl_create();
    
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
    TEST_ASSERT_EQUAL(0, dl_size(list));
    
    dl_destroy(list);
}

// 测试节点创建
void test_node_create_should_create_node_with_data(void) {
    int* data = malloc(sizeof(int));
    *data = 42;
    
    dl_node_t* node = dl_node_create(data);
    
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL_PTR(data, node->data);
    TEST_ASSERT_NULL(node->prev);
    TEST_ASSERT_NULL(node->next);
    
    dl_node_destroy(node);
    free(data);
}

// 测试添加节点到链表头部
void test_add_first_should_add_node_to_empty_list(void) {
    dl_list_t* list = dl_create();
    int* data = malloc(sizeof(int));
    *data = 10;
    
    dl_node_t* node = dl_node_create(data);
    dl_add_first(list, node);
    
    TEST_ASSERT_EQUAL(1, dl_size(list));
    TEST_ASSERT_EQUAL_PTR(node, list->head);
    TEST_ASSERT_EQUAL_PTR(node, list->tail);
    TEST_ASSERT_NULL(node->prev);
    TEST_ASSERT_NULL(node->next);
    
    dl_destroy(list);
    free(data);
}

// 测试添加多个节点到链表头部
void test_add_first_should_add_multiple_nodes_in_reverse_order(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 1;
    int* data2 = malloc(sizeof(int)); *data2 = 2;
    int* data3 = malloc(sizeof(int)); *data3 = 3;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    dl_node_t* node3 = dl_node_create(data3);
    
    dl_add_first(list, node1);
    dl_add_first(list, node2);
    dl_add_first(list, node3);
    
    TEST_ASSERT_EQUAL(3, dl_size(list));
    TEST_ASSERT_EQUAL_PTR(node3, list->head);
    TEST_ASSERT_EQUAL_PTR(node1, list->tail);
    
    TEST_ASSERT_EQUAL(3, *(int*)list->head->data);
    TEST_ASSERT_EQUAL(2, *(int*)list->head->next->data);
    TEST_ASSERT_EQUAL(1, *(int*)list->tail->data);
    
    dl_destroy(list);
    free(data1); free(data2); free(data3);
}

// 测试添加节点到链表尾部
void test_add_last_should_add_node_to_empty_list(void) {
    dl_list_t* list = dl_create();
    int* data = malloc(sizeof(int));
    *data = 10;
    
    dl_node_t* node = dl_node_create(data);
    dl_add_last(list, node);
    
    TEST_ASSERT_EQUAL(1, dl_size(list));
    TEST_ASSERT_EQUAL_PTR(node, list->head);
    TEST_ASSERT_EQUAL_PTR(node, list->tail);
    
    dl_destroy(list);
    free(data);
}

// 测试在指定位置添加节点
void test_add_should_add_node_at_specific_index(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 1;
    int* data2 = malloc(sizeof(int)); *data2 = 2;
    int* data3 = malloc(sizeof(int)); *data3 = 3;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    dl_node_t* node3 = dl_node_create(data3);
    
    dl_add_first(list, node1);
    dl_add_last(list, node3);
    dl_add(list, node2, 1); // 插入到中间
    
    TEST_ASSERT_EQUAL(3, dl_size(list));
    TEST_ASSERT_EQUAL(1, *(int*)dl_get_first(list)->data);
    TEST_ASSERT_EQUAL(2, *(int*)dl_get(list, 1)->data);
    TEST_ASSERT_EQUAL(3, *(int*)dl_get_last(list)->data);
    
    dl_destroy(list);
    free(data1); free(data2); free(data3);
}

// 测试移除节点
void test_remove_should_remove_node_from_list(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 1;
    int* data2 = malloc(sizeof(int)); *data2 = 2;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    
    dl_node_t* removed = dl_remove(list, node1);
    
    TEST_ASSERT_EQUAL_PTR(node1, removed);
    TEST_ASSERT_EQUAL(1, dl_size(list));
    TEST_ASSERT_EQUAL_PTR(node2, list->head);
    TEST_ASSERT_EQUAL_PTR(node2, list->tail);
    
    dl_destroy(list);
    free(data1); free(data2);
}

// 测试移除头节点
void test_remove_first_should_remove_head_node(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 1;
    int* data2 = malloc(sizeof(int)); *data2 = 2;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    
    dl_node_t* removed = dl_remove_first(list);
    
    TEST_ASSERT_EQUAL_PTR(node1, removed);
    TEST_ASSERT_EQUAL(1, dl_size(list));
    TEST_ASSERT_EQUAL_PTR(node2, list->head);
    
    dl_destroy(list);
    free(data1); free(data2);
}

// 测试移除尾节点
void test_remove_last_should_remove_tail_node(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 1;
    int* data2 = malloc(sizeof(int)); *data2 = 2;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    
    dl_node_t* removed = dl_remove_last(list);
    
    TEST_ASSERT_EQUAL_PTR(node2, removed);
    TEST_ASSERT_EQUAL(1, dl_size(list));
    TEST_ASSERT_EQUAL_PTR(node1, list->tail);
    
    dl_destroy(list);
    free(data1); free(data2);
}

// 测试获取节点
void test_get_should_return_node_at_index(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 10;
    int* data2 = malloc(sizeof(int)); *data2 = 20;
    int* data3 = malloc(sizeof(int)); *data3 = 30;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    dl_node_t* node3 = dl_node_create(data3);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    dl_add_last(list, node3);
    
    TEST_ASSERT_EQUAL_PTR(node1, dl_get(list, 0));
    TEST_ASSERT_EQUAL_PTR(node2, dl_get(list, 1));
    TEST_ASSERT_EQUAL_PTR(node3, dl_get(list, 2));
    
    dl_destroy(list);
    free(data1); free(data2); free(data3);
}

// 测试获取节点索引
void test_index_of_should_return_correct_index(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 10;
    int* data2 = malloc(sizeof(int)); *data2 = 20;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    
    TEST_ASSERT_EQUAL(0, dl_index_of(list, node1));
    TEST_ASSERT_EQUAL(1, dl_index_of(list, node2));
    TEST_ASSERT_EQUAL((size_t)-1, dl_index_of(list, NULL));
    
    dl_destroy(list);
    free(data1); free(data2);
}

// 测试链表反转
void test_reverse_should_reverse_list_order(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 1;
    int* data2 = malloc(sizeof(int)); *data2 = 2;
    int* data3 = malloc(sizeof(int)); *data3 = 3;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    dl_node_t* node3 = dl_node_create(data3);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    dl_add_last(list, node3);
    
    dl_reverse(list);
    
    TEST_ASSERT_EQUAL(3, *(int*)dl_get_first(list)->data);
    TEST_ASSERT_EQUAL(2, *(int*)dl_get(list, 1)->data);
    TEST_ASSERT_EQUAL(1, *(int*)dl_get_last(list)->data);
    
    dl_destroy(list);
    free(data1); free(data2); free(data3);
}

// 测试链表排序
void test_sort_should_sort_list_in_ascending_order(void) {
    dl_list_t* list = dl_create();
    
    int* data3 = malloc(sizeof(int)); *data3 = 3;
    int* data1 = malloc(sizeof(int)); *data1 = 1;
    int* data4 = malloc(sizeof(int)); *data4 = 4;
    int* data2 = malloc(sizeof(int)); *data2 = 2;
    
    dl_node_t* node3 = dl_node_create(data3);
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node4 = dl_node_create(data4);
    dl_node_t* node2 = dl_node_create(data2);
    
    dl_add_first(list, node3);
    dl_add_last(list, node1);
    dl_add_last(list, node4);
    dl_add_last(list, node2);
    
    dl_sort(list, int_cmp);
    
    TEST_ASSERT_EQUAL(1, *(int*)dl_get_first(list)->data);
    TEST_ASSERT_EQUAL(2, *(int*)dl_get(list, 1)->data);
    TEST_ASSERT_EQUAL(3, *(int*)dl_get(list, 2)->data);
    TEST_ASSERT_EQUAL(4, *(int*)dl_get_last(list)->data);
    
    dl_destroy(list);
    free(data1); free(data2); free(data3); free(data4);
}

// 测试链表搜索
void test_search_should_find_existing_node(void) {
    dl_list_t* list = dl_create();
    
    int target = 42;
    int* data1 = malloc(sizeof(int)); *data1 = 10;
    int* data2 = malloc(sizeof(int)); *data2 = 42;
    int* data3 = malloc(sizeof(int)); *data3 = 30;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    dl_node_t* node3 = dl_node_create(data3);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    dl_add_last(list, node3);
    
    dl_node_t* found = dl_search(list, &target, int_cmp);
    
    TEST_ASSERT_EQUAL_PTR(node2, found);
    TEST_ASSERT_EQUAL(42, *(int*)found->data);
    
    dl_destroy(list);
    free(data1); free(data2); free(data3);
}

// 测试链表清空
void test_clear_should_remove_all_nodes(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 1;
    int* data2 = malloc(sizeof(int)); *data2 = 2;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    
    dl_clear(list);
    
    TEST_ASSERT_EQUAL(0, dl_size(list));
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
    
    dl_destroy(list);
    free(data1); free(data2);
}

// 测试链表转数组
void test_to_array_should_convert_list_to_array(void) {
    dl_list_t* list = dl_create();
    
    int* data1 = malloc(sizeof(int)); *data1 = 1;
    int* data2 = malloc(sizeof(int)); *data2 = 2;
    int* data3 = malloc(sizeof(int)); *data3 = 3;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    dl_node_t* node3 = dl_node_create(data3);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    dl_add_last(list, node3);
    
    dl_node_t** array = dl_to_array(list);
    
    TEST_ASSERT_NOT_NULL(array);
    TEST_ASSERT_EQUAL_PTR(node1, array[0]);
    TEST_ASSERT_EQUAL_PTR(node2, array[1]);
    TEST_ASSERT_EQUAL_PTR(node3, array[2]);
    
    free(array);
    dl_destroy(list);
    free(data1); free(data2); free(data3);
}

// 测试数组转链表
void test_from_array_should_create_list_from_array(void) {
    void* array[3];
    int data1 = 1, data2 = 2, data3 = 3;
    
    array[0] = &data1;
    array[1] = &data2;
    array[2] = &data3;
    
    dl_list_t* list = dl_from_array(array, 3);
    
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(3, dl_size(list));
    TEST_ASSERT_EQUAL(1, *(int*)dl_get_first(list)->data);
    TEST_ASSERT_EQUAL(3, *(int*)dl_get_last(list)->data);
    
    dl_destroy(list);
}

// 测试边界条件
void test_edge_cases_should_handle_null_inputs(void) {
    dl_list_t* list = dl_create();
    
    // 测试空链表的各种操作
    TEST_ASSERT_NULL(dl_get_first(NULL));
    TEST_ASSERT_NULL(dl_get_last(NULL));
    TEST_ASSERT_NULL(dl_remove_first(NULL));
    TEST_ASSERT_NULL(dl_remove_last(NULL));
    TEST_ASSERT_EQUAL(0, dl_size(NULL));
    TEST_ASSERT_TRUE(dl_is_empty(NULL));
    
    // 测试空链表遍历
    dl_foreach(NULL, free_test_data); // 应该不崩溃
    
    dl_destroy(list);
}

// 测试字符串表示
void test_to_string_should_create_correct_format(void) {
    dl_list_t* list = dl_create();
    
    int data1 = 10;
    int data2 = 20;
    
    dl_node_t* node1 = dl_node_create(data1);
    dl_node_t* node2 = dl_node_create(data2);
    
    dl_add_first(list, node1);
    dl_add_last(list, node2);
    
    char* str = dl_to_string(list, "%d", ", ");
    
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("10, 20", str);
    
    free(str);
    dl_destroy(list);
    free(data1); free(data2);
}

// 测试运行器
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_list_create_should_create_empty_list);
    RUN_TEST(test_node_create_should_create_node_with_data);
    RUN_TEST(test_add_first_should_add_node_to_empty_list);
    RUN_TEST(test_add_first_should_add_multiple_nodes_in_reverse_order);
    RUN_TEST(test_add_last_should_add_node_to_empty_list);
    RUN_TEST(test_add_should_add_node_at_specific_index);
    RUN_TEST(test_remove_should_remove_node_from_list);
    RUN_TEST(test_remove_first_should_remove_head_node);
    RUN_TEST(test_remove_last_should_remove_tail_node);
    RUN_TEST(test_get_should_return_node_at_index);
    RUN_TEST(test_index_of_should_return_correct_index);
    RUN_TEST(test_reverse_should_reverse_list_order);
    RUN_TEST(test_sort_should_sort_list_in_ascending_order);
    RUN_TEST(test_search_should_find_existing_node);
    RUN_TEST(test_clear_should_remove_all_nodes);
    RUN_TEST(test_to_array_should_convert_list_to_array);
    RUN_TEST(test_from_array_should_create_list_from_array);
    RUN_TEST(test_edge_cases_should_handle_null_inputs);
    RUN_TEST(test_to_string_should_create_correct_format);
    
    return UNITY_END();
}