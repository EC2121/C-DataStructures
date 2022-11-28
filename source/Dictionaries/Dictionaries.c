#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\Includes\SetsInclude.h"

typedef struct dictionary_entry
{
    key_data_t key_data;
    void *entry_val;
} dictionary_entry_t;

list_node_t *dict_insert(set_table_t **dict, const char *key, const size_t key_len, void *value, const size_t value_len)
{
    const list_node_t *is_node_already_in = set_table_search(*dict, key, key_len);
    if (is_node_already_in)
    {
        printf("%s IS ALREADY A KEY\n", (char *)key);
        return NULL;
    }
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % (*dict)->hashmap_size;
    list_node_t *head = (*dict)->nodes[index];
    if (!head)
    {
        (*dict)->nodes[index] = malloc(sizeof(list_node_t));
        dictionary_entry_t *dict_data = calloc(1, sizeof(dictionary_entry_t));
        if (!(*dict)->nodes[index] || !dict_data)
        {
            printf("FAILED TO ALLOCATE MEMORY ON HEAD ");
            return NULL;
        }
        (*dict)->nodes[index]->val = dict_data;
        dictionary_entry_t *entry = (dictionary_entry_t *)(*dict)->nodes[index]->val;
        key_data_t *entry_key_data = &entry->key_data;

        entry_key_data->key = malloc(key_len + 1);
        memcpy((char *)entry_key_data->key,key,key_len + 1);
        // strcpy_s(entry_key_data->key, key_len + 1, key);
        entry_key_data->key_len = key_len;
        entry->entry_val = malloc(value_len);
        memcpy(entry->entry_val, value, value_len);

        (*dict)->nodes[index]->next = NULL;
        (*dict)->nodes[index]->prev = NULL;
        return (*dict)->nodes[index];
    }

    list_node_t *new_item = malloc(sizeof(list_node_t));
    dictionary_entry_t *dict_data = calloc(1, sizeof(dictionary_entry_t));

    if (!new_item || !dict_data)
    {
        printf("FAILED TO ALLOCATE MEMORY ON TAIL ");
        return NULL;
    }
    new_item->val = dict_data;
    dictionary_entry_t *entry = (dictionary_entry_t *)new_item->val;
    key_data_t *entry_key_data = &entry->key_data;

    entry_key_data->key = malloc(key_len + 1);
    memcpy((char *)entry_key_data->key,key,key_len + 1);
    // strcpy_s(entry_key_data->key, key_len + 1, key);
    entry_key_data->key_len = key_len;
    entry->entry_val = malloc(value_len);
    memcpy(entry->entry_val, value, value_len);

    new_item->next = NULL;
    list_node_t *tail = head;
    while (head)
    {
        tail = head;
        head = head->next;
    }
    new_item->prev = tail;
    tail->next = new_item;
    (*dict)->collisions += 1;
    if ((*dict)->collisions > (*dict)->hashmap_size * 0.25f)
    {
        printf("INSERTING %s CAUSED TOO MANY COLLISIONS REGENARTION NEEDED\n", entry_key_data->key);
        (*dict) = set_table_regenerate(*dict);
    }

    return new_item;
}

void free_dict_entry(list_node_t *head)
{
    free((char *)((key_data_t *)head->val)->key);
    ((key_data_t *)head->val)->key = NULL;
    free(((dictionary_entry_t *)head->val)->entry_val);
    ((dictionary_entry_t *)head->val)->entry_val = NULL;
    free((dictionary_entry_t *)head->val);
    head->val = NULL;
}

int dict_remove(struct set_table *table, const char *key, const size_t key_len)
{
    list_node_t *head = set_table_search(table, key, key_len);
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    if (!head)
    {
        return 0;
    }

    if (head->next)
        head->next->prev = head->prev;

    if (head->prev)
    {
        head->prev->next = head->next;
    }
    else
    {
        table->nodes[index] = head->next;
        table->collisions -= 1;
    }

    free_dict_entry(head);
    return 1;
}

void print_dictionary(set_table_t *dict)
{
    int counter = 0;
    size_t table_size = dict->hashmap_size;
    list_node_t *node;
    while (counter < table_size)
    {
        node = dict->nodes[counter];
        while (node)
        {

            dictionary_entry_t *entry = (dictionary_entry_t *)node->val;
            key_data_t entry_key_data = entry->key_data;
            printf("%s:%s\n", (char *)entry_key_data.key, (char *)entry->entry_val);
            node = node->next;
        }
        counter++;
    }
}

int main()
{
    const size_t hashmap_size = 1;
    int a = 1;
    int *b = &a;
    set_table_t *dict = set_table_new(hashmap_size);
    printf("-----START INSERT-----\n");
    //VALUE LEN HAS TO BE +1 FOR STRINGS.
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
    if(result_node){
        printf("%s WAS FOUND\n",((key_data_t *)result_node->val)->key);
        result_node = result_node->next;
    }
    while (result_node)
    {
        printf("LINKED TO: %s\n", ((key_data_t *)result_node->val)->key);
        result_node = result_node->next;
    }
    printf("-----DICT TABLE SEARCH END-----\n");

}