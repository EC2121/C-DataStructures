// typedef struct test_struct
// {
//     int a;
//     int b;
//     int c;
// } test_struct_t;

// int main()
// {
//     test_struct_t test;
//     test.a = 1;
//     test.b = 2;
//     test.c = 3;
//     printf("%llu\n",sizeof(list_item_t));
//     list_item_t *my_linked_list = NULL;
//     list_append_str(&my_linked_list,"CCCCCCCCCCCCccccccccccccccccccccccccccccccccc");
//     list_append_size_t(&my_linked_list,&test);
//     list_append_size_t(&my_linked_list,&test);
//     // list_append_size_t(&my_linked_list, 1);
//     // list_append_size_t(&my_linked_list, 2);
//     // list_append_size_t(&my_linked_list, 3);
//     // list_append_size_t(&my_linked_list, 4);
//     // list_append_size_t(&my_linked_list, "4");
//     // list_append_size_t(&my_linked_list, "5");
//     // list_append_size_t(&my_linked_list, "6");
//     // list_append_size_t(&my_linked_list, "7");
//     // list_append_size_t(&my_linked_list, "7");
//     // list_remove_at_index(&my_linked_list, 0);
//     // list_remove_at_index(&my_linked_list, 5);
//     // list_remove_at_index(&my_linked_list, 6);
//     list_reverse(&my_linked_list);
//     list_item_t *list_item = my_linked_list;
//     while (list_item)
//     {
//         printf("%s\n", (char *)list_item->node.val);
//         list_item = (list_item_t *)list_item->node.next;
//     }
//     printf("list entries : %d\n", list_len((list_node_t **)&my_linked_list));
//     return 0;
// }