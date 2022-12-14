#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SetsInclude.h"

void set_table_print(struct set_table *table)
{
    int counter = 0;
    size_t table_size = table->hashmap_size;
    list_node_t *node;
    while (counter < table_size)
    {
        node = table->nodes[counter];
        while (node)
        {
            printf("%s\n", ((key_data_t *)node->val)->key);
            node = node->next;
        }
        counter++;
    }
}

void free_set_table_entry(list_node_t *head)
{
    ((key_data_t *)head->val)->key = NULL;
    free((key_data_t *)head->val);
    head->val = NULL;
}

int set_table_remove(set_table_t *table, const char *key, const size_t key_len)
{
    list_node_t *node = set_table_search(table, key, key_len);
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    if (list_remove_node(&table->nodes[index], node))
    {
        table->collisions -= 1;
    }
    free_set_table_entry(node);
    return 1;
}

list_node_t *crate_table_entry(const char *key, const size_t key_len)
{
    list_node_t *new_item = malloc(sizeof(list_node_t));
    key_data_t *key_data = calloc(1, sizeof(key_data_t));
    if (!new_item || !key_data)
    {
        printf("FAILED TO ALLOCATE MEMORY ON INSERT");
        return NULL;
    }
    new_item->val = key_data;
    key_data_t *entry = new_item->val;
    entry->key = key;
    entry->key_len = key_len;

    return new_item;
}

list_node_t *set_insert(struct set_table **table, const char *key, const size_t key_len)
{
    const list_node_t *is_node_already_in = set_table_search(*table, key, key_len);
    if (is_node_already_in)
    {
        printf("%s IS ALREADY A KEY\n", (char *)key);
        return NULL;
    }
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % (*table)->hashmap_size;
    list_node_t *head = (*table)->nodes[index];
    list_node_t *new_item = crate_table_entry(key,key_len);
    if (!head)
    {
        (*table)->nodes[index] = new_item;
        (*table)->nodes[index]->next = NULL;
        (*table)->nodes[index]->prev = NULL;
        return new_item;
    }

    list_append(&head, new_item);
    (*table)->collisions += 1;
    if ((*table)->collisions > (*table)->hashmap_size * 0.25f)
    {
        printf("INSERTING %s CAUSED TOO MANY COLLISIONS REGENARTION NEEDED\n", ((key_data_t *)new_item->val)->key);
        (*table) = set_table_regenerate(*table);
    }

    return new_item;
}

