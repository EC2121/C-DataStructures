#include "Dictionaries.h"

int main()
{
    const size_t hashmap_size = 1;
    int a = 1;
    int *b = &a;
    set_table_t *dict = set_table_new(hashmap_size);
    printf("-----START INSERT-----\n");
    // VALUE LEN HAS TO BE +1 FOR STRINGS.
    dict_insert(&dict, "ciao", 4, "TEST", 5);
    dict_insert(&dict, "1ciao", 5, "TEST", 5);
    dict_insert(&dict, "2ciao", 5, "TEST", 5);
    dict_insert(&dict, "3ciao", 5, "TEST", 5);
    dict_insert(&dict, "4ciao", 5, "TEST", 5);
    dict_insert(&dict, "5ciao", 5, "TEST", 5);
    dict_insert(&dict, "6ciao", 5, "TEST6", 6);
    dict_insert(&dict, "7ciao", 5, "TEST7", 6);
    dict_insert(&dict, "8ciao", 5, "TEST8", 6);
    dict_insert(&dict, "9ciao", 5, "TEST9", 6);
    dict_insert(&dict, "9ciao", 5, "TEST", 5);
    dict_insert(&dict, "9ciao", 5, "test", 5);
    dict_insert(&dict, "9ciao", 5, "test", 5);
    dict_insert(&dict, "9ciao", 5, "TEST", 5);
    dict_insert(&dict, "9ciao", 5, "TEST", 5);
    dict_insert(&dict, "9ciao", 5, "TEST", 5);
    dict_insert(&dict, "9ciao", 5, "TEST", 5);
    dict_insert(&dict, "10ciao", 6, "TEST", 5);
    dict_insert(&dict, "11ciao", 6, "TEST", 5);
    dict_insert(&dict, "12ciao", 6, "TEST", 5);
    printf("HashmapSize = %llu\n", dict->hashmap_size);
    dict_remove(dict, "1ciao", 5);
    dict_remove(dict, "2ciao", 5);
    dict_remove(dict, "3ciao", 5);
    dict_remove(dict, "4ciao", 5);
    printf("-----END INSERT-----\n");
    printf("-----PRINT START-----\n");
    print_dictionary(dict);
    printf("-----PRINT END-----\n");

    printf("-----DICT TABLE SEARCH START-----\n");
    list_node_t *result_node = set_table_search(dict, "ciao", 4);
    if (result_node)
    {
        printf("%s WAS FOUND\n", ((key_data_t *)result_node->val)->key);
        result_node = result_node->next;
    }
    while (result_node)
    {
        printf("LINKED TO: %s\n", ((key_data_t *)result_node->val)->key);
        result_node = result_node->next;
    }
    printf("-----DICT TABLE SEARCH END-----\n");
}