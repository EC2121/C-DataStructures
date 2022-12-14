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

list_node_t* crate_dict_entry(const char *key, const size_t key_len, void *value, const size_t value_len)
{
    list_node_t *new_item = malloc(sizeof(list_node_t));
    dictionary_entry_t *dict_data = calloc(1, sizeof(dictionary_entry_t));
    if (!new_item || !dict_data)
    {
        printf("FAILED TO ALLOCATE MEMORY ON A DICT ENTRY");
        return NULL;
    }
    new_item->val = dict_data;
    dictionary_entry_t *entry = (dictionary_entry_t *)new_item->val;
    key_data_t *entry_key_data = &entry->key_data;

    entry_key_data->key = key;
    entry_key_data->key_len = key_len;
    entry->entry_val = malloc(value_len);
    memcpy(entry->entry_val, value, value_len);
    return new_item;
}
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
    list_node_t *cur_node = crate_dict_entry(key,key_len,value,value_len);
    if (!head)
    {   
        cur_node->next = NULL;
        cur_node->prev =NULL;
        (*dict)->nodes[index] = cur_node;
        return cur_node;
    }
    cur_node->next = NULL;
    list_node_t *tail = head;
    while (head)
    {
        tail = head;
        head = head->next;
    }
    cur_node->prev = tail;
    tail->next = cur_node;
    (*dict)->collisions += 1;
    if ((*dict)->collisions > (*dict)->hashmap_size * 0.25f)
    {
        printf("INSERTING %s CAUSED TOO MANY COLLISIONS REGENARTION NEEDED\n",((dictionary_entry_t *)cur_node->val)->key_data.key);
        (*dict) = set_table_regenerate(*dict);
    }

    return cur_node;
}

void free_dict_entry(list_node_t *head)
{
    ((dictionary_entry_t *)head->val)->key_data.key = NULL;
    free(((dictionary_entry_t *)head->val)->entry_val);
    ((dictionary_entry_t *)head->val)->entry_val = NULL;
    free((dictionary_entry_t *)head->val);
    head->val = NULL;
}

int dict_remove(struct set_table *table, const char *key, const size_t key_len)
{
    list_node_t *node = set_table_search(table, key, key_len);
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    if (list_remove_node(&table->nodes[index], node))
    {
        table->collisions -= 1;
    }
    free_dict_entry(node);
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
