// #include "Sets.h"

// int main()
// {
//     const size_t hashmap_size = 1;
//     struct set_table *table = set_table_new(hashmap_size);
//     printf("-----START INSERT-----\n");
//     set_insert(&table, "HelloWorld!", 10);
//     set_insert(&table, "HelloWorld", 10);
//     set_insert(&table, "test", 4);
//     set_insert(&table, "test1", 5);
//     set_insert(&table, "test2", 5);
//     set_insert(&table, "test2", 5);
//     set_insert(&table, "test2", 5);
//     set_insert(&table, "test2", 5);
//     set_insert(&table, "test2", 5);
//     set_insert(&table, "test2", 5);
//     set_insert(&table, "1", 1);
//     set_insert(&table, "2", 1);
//     set_insert(&table, "3", 1);
//     set_insert(&table, "4", 1);
//     set_insert(&table, "5", 1);
//     set_insert(&table, "6", 1);
//     set_insert(&table, "7", 1);
//     set_insert(&table, "8", 1);
//     set_insert(&table, "9", 1);
//     set_insert(&table, "0", 1);
//     set_insert(&table, "0", 1);
//     set_insert(&table, "0", 1);
//     set_table_remove(table, "test", 4);
//     set_table_remove(table, "test1", 5);
//     set_table_remove(table, "test2", 5);
//     printf("HashmapSize = %llu\n", table->hashmap_size);
//     printf("-----END INSERT-----\n");
//     printf("-----SET TABLE PRINT START-----\n");
//     set_table_print(table);
//     printf("-----SET TABLE PRINT END-----\n");

//     printf("-----SET TABLE SEARCH START-----\n");
//     list_node_t *result_node = set_table_search(table, "HelloWorld", 10);
//     if (result_node)
//     {
//         printf("%s WAS FOUND\n", ((key_data_t *)result_node->val)->key);
//         result_node = result_node->next;
//     }
//     while (result_node)
//     {
//         printf("LINKED TO: %s\n", ((key_data_t *)result_node->val)->key);
//         result_node = result_node->next;
//     }
//     printf("-----SET TABLE SEARCH END-----\n");
// }