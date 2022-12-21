#include "DoublyLinkedList.h"
#include "aiv-cunit.h"
#include "LinkedList.h"
#include "Sets.h"
#include "Dictionaries.h"


CUNIT_TEST(test_append_one_string)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");

    char *actual = my_linked_list->node.val;
    char *exptected = "item1";
    CUNIT_STRING_EQ(exptected, actual);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_append_two_string)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");
    LINKEDLIST_APPEND_STR(&my_linked_list, "item2");

    char *actual = my_linked_list->node.val;
    char *exptected = "item1";
    CUNIT_STRING_EQ(exptected, actual);
    actual = my_linked_list->node.next->val;
    exptected = "item2";
    CUNIT_STRING_EQ(exptected, actual);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_pop_from_one_item_list)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");

    linked_list_node_t *actual = linked_list_pop((linked_list_node_t **)&my_linked_list);

    CUNIT_STRING_EQ("item1", (char *)actual->val);
    CUNIT_IS_NULL(my_linked_list);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_pop_from_empty_list)
{
    linked_list_item_t *my_linked_list = NULL;

    linked_list_node_t *actual = linked_list_pop((linked_list_node_t **)&my_linked_list);

    CUNIT_IS_NULL(actual);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_pop_from_two_items_list)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");
    LINKEDLIST_APPEND_STR(&my_linked_list, "item2");

    linked_list_node_t *popped = linked_list_pop((linked_list_node_t **)&my_linked_list);

    CUNIT_STRING_EQ("item1", (char *)popped->val);
    CUNIT_STRING_EQ("item2", (char *)my_linked_list->node.val);
    printf("%s---PASSED\n", __FUNCTION__);
}
CUNIT_TEST(test_remove_from_null_list)
{
    linked_list_node_t *removed = LINKEDLIST_REMOVE_AT_INDEX(NULL, 0);

    CUNIT_IS_NULL(removed);

    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_remove_unexistant_item_from_one_item_list)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");

    linked_list_node_t *removed = LINKEDLIST_REMOVE_AT_INDEX(&my_linked_list, 2);

    CUNIT_IS_NULL(removed);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_remove_item_from_one_item_list)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");

    linked_list_node_t *removed = LINKEDLIST_REMOVE_AT_INDEX(&my_linked_list, 0);

    CUNIT_STRING_EQ("item1", (char *)removed->val);
    printf("%s---PASSED\n", __FUNCTION__);
}
CUNIT_TEST(test_get_tail_from_null_list)
{
    linked_list_item_t *my_linked_list = NULL;

    linked_list_node_t *tail = linked_list_get_tail((linked_list_node_t **)&my_linked_list);

    CUNIT_IS_NULL(tail);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_get_tail_from_one_item_list)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");
    
    linked_list_node_t *tail = linked_list_get_tail((linked_list_node_t **)&my_linked_list);

    CUNIT_STRING_EQ("item1", (char *)tail->val);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_get_tail_from_two_item_list)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");
    LINKEDLIST_APPEND_STR(&my_linked_list, "item2");

    linked_list_node_t *tail = linked_list_get_tail((linked_list_node_t **)&my_linked_list);

    CUNIT_STRING_EQ("item2", (char *)tail->val);
    printf("%s---PASSED\n", __FUNCTION__);
}
CUNIT_TEST(test_get_count_from_null_list)
{
    linked_list_item_t *my_linked_list = NULL;

    int count = linked_list_len((linked_list_node_t **)&my_linked_list);

    CUNIT_INT_EQ(0, count);
    printf("%s---PASSED\n", __FUNCTION__);
}
CUNIT_TEST(test_get_count_from_one_item_list)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");
    int count = linked_list_len((linked_list_node_t **)&my_linked_list);

    CUNIT_INT_EQ(1, count);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_get_count_from_two_item_list)
{
    linked_list_item_t *my_linked_list = NULL;
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");
    LINKEDLIST_APPEND_STR(&my_linked_list, "item1");

    int count = linked_list_len((linked_list_node_t **)&my_linked_list);
    
    CUNIT_INT_EQ(2, count);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_get_count_from_one_hundred_item_list)
{
    linked_list_item_t *my_linked_list = NULL;
    for (int i = 0; i < 100; ++i)
    {
        LINKEDLIST_APPEND_STR(&my_linked_list, "item1");
    }
    int count = linked_list_len((linked_list_node_t **)&my_linked_list);

    CUNIT_INT_EQ(100, count);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_RUNNER(

    test_append_one_string, test_append_two_string,
    test_pop_from_one_item_list, test_pop_from_empty_list, test_pop_from_two_items_list,
    test_remove_from_null_list, test_remove_unexistant_item_from_one_item_list, test_remove_item_from_one_item_list,
    test_get_tail_from_null_list, test_get_tail_from_one_item_list, test_get_tail_from_two_item_list,
    test_get_count_from_null_list, test_get_count_from_one_item_list, test_get_count_from_two_item_list, test_get_count_from_one_hundred_item_list
    );
