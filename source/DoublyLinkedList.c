// #include "DoublyLinkedList.h"

// int main()
// {
//     struct list_item *my_linked_list = NULL;
//     list_append_str(&my_linked_list, "Hello World");
//     list_append_str(&my_linked_list, "Test001");
//     list_append_str(&my_linked_list, "Test002");
//     list_append_str(&my_linked_list, "3");
//     list_append_str(&my_linked_list, "4");
//     list_append_str(&my_linked_list, "5");
//     list_append_str(&my_linked_list, "6");
//     list_append_str(&my_linked_list, "7");
//     list_append_after_index(&my_linked_list, "Append After", 1);
//     list_append_before_index(&my_linked_list, "Append before", 4);
//     list_remove_at_index(&my_linked_list,9);
//     list_remove_at_index(&my_linked_list,0);
//     printf("-----BEFORE SHUFFLE-----\n");
//     struct list_item *list_item = my_linked_list;
//     while (list_item)
//     {
//         printf("%s\n", (char *)list_item->node.val);
//         list_item = (struct list_item *)list_item->node.next;
//     }
//     printf("-----AFTER SHUFFLE-----\n");
//     list_shuffle(&my_linked_list);
//     list_item = my_linked_list;
//     while (list_item)
//     {
//         printf("%s\n", (char *)list_item->node.val);
//         list_item = (struct list_item *)list_item->node.next;
//     }
//     printf("-----END SHUFFLE-----\n");

//     printf("list entries : %d\n", list_len((struct list_node **)&my_linked_list));
//     return 0;
// }