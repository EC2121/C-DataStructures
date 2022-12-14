#include "LinkedList.h"
#include "aiv-cunit.h"


CUNIT_TEST(test_append_one_string)
{
    list_item_t *my_linked_list = NULL;
    list_append_str(&my_linked_list, "item1");

    char *actual = my_linked_list->node.val;
    char *exptected = "item1";
    CUNIT_STRING_EQ(exptected,actual);
    printf("%s---PASSED\n", __FUNCTION__);

}

CUNIT_TEST(test_append_two_string)
{
    list_item_t *my_linked_list = NULL;
    list_append_str(&my_linked_list, "item1");
    list_append_str(&my_linked_list, "item2");

    char *actual = my_linked_list->node.val;
    char *exptected = "item1";
    CUNIT_STRING_EQ(exptected,actual);
    actual = my_linked_list->node.next->val;
    exptected = "item2";
    CUNIT_STRING_EQ(exptected,actual);
    printf("%s---PASSED\n", __FUNCTION__);
}

CUNIT_TEST(test_pop_from_one_item_list)
{
    list_item_t *my_linked_list = NULL;
    list_append_str(&my_linked_list, "item1");
    list_node_t *actual = list_pop((list_node_t **)&my_linked_list);
    CUNIT_STRING_EQ("item1",(char*)actual->val);
    CUNIT_IS_NULL(my_linked_list);
    printf("%s---PASSED\n", __FUNCTION__);

}

CUNIT_TEST(test_pop_from_empty_list)
{
    list_item_t *my_linked_list = NULL;
    list_node_t *actual = list_pop((list_node_t **)&my_linked_list);
    CUNIT_IS_NULL(actual);
    printf("%s---PASSED\n", __FUNCTION__);

}

CUNIT_TEST(test_pop_from_two_items_list)
{
    list_item_t *my_linked_list = NULL;
    list_append_str(&my_linked_list, "item1");
    list_append_str(&my_linked_list, "item2");
    list_node_t *popped = list_pop((list_node_t **)&my_linked_list);
    CUNIT_STRING_EQ("item1",(char *)popped->val);
    CUNIT_STRING_EQ("item2",(char *)my_linked_list->node.val);
    printf("%s---PASSED\n", __FUNCTION__);

}
CUNIT_TEST(test_remove_from_null_list)
{
    list_node_t *removed = list_remove_at_index(NULL,0);
    CUNIT_IS_NULL(removed);
    printf("%s---PASSED\n", __FUNCTION__);

}

CUNIT_TEST(test_remove_unexistant_item_from_one_item_list)
{
    list_item_t *my_linked_list = NULL;
    list_append_str(&my_linked_list, "item1");
    list_node_t *removed = list_remove_at_index(&my_linked_list,2);
    CUNIT_IS_NULL(removed);
    printf("%s---PASSED\n", __FUNCTION__);

}

CUNIT_TEST(test_remove_item_from_one_item_list)
{
    list_item_t *my_linked_list = NULL;
    list_append_str(&my_linked_list, "item1");
    list_node_t *removed = list_remove_at_index(&my_linked_list,0);
    CUNIT_STRING_EQ("item1",(char *)removed->val);
    printf("%s---PASSED\n", __FUNCTION__);

}

CUNIT_RUNNER(

test_append_one_string, test_append_two_string,
test_pop_from_one_item_list, test_pop_from_empty_list, test_pop_from_two_items_list,
test_remove_from_null_list,test_remove_unexistant_item_from_one_item_list,test_remove_item_from_one_item_list

);

