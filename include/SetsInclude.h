#pragma once
#include "DoublyLinkedListIncludes.h"
#include <stddef.h>

typedef struct key_data
{
    const char *key;
    size_t key_len;
} key_data_t;

typedef struct set_table
{
    doubly_linked_list_node_t **nodes;
    size_t hashmap_size;
    size_t collisions;
} set_table_t;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

set_table_t *set_table_new(const size_t hashmap_size)
{
    set_table_t *table = malloc(sizeof(set_table_t));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(doubly_linked_list_node_t *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}


doubly_linked_list_node_t *set_table_search(set_table_t *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    doubly_linked_list_node_t *temp = table->nodes[index];
    while (temp)
    {
        if (!memcmp(((key_data_t *)temp->val)->key, key, strlen(key)))
        {
            // printf("Search complexity : %d\n", counter);
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}



set_table_t *set_table_regenerate(set_table_t *table)
{
    set_table_t *new_table = set_table_new(table->hashmap_size * 2);
    int counter = 0;
    size_t table_size = table->hashmap_size;
    doubly_linked_list_node_t *node;
    doubly_linked_list_node_t *next_node;
    while (counter < table_size)
    {
        node = table->nodes[counter];
        while (node)
        {
            next_node = node->next;
            size_t hash = djb33x_hash(((key_data_t *)node->val)->key, ((key_data_t *)node->val)->key_len);
            size_t index = hash % new_table->hashmap_size;
            doubly_linked_list_node_t *head = new_table->nodes[index];
            if (!head)
            {
                node->next = NULL;
                node->prev = NULL;
                new_table->nodes[index] = node;
            }
            else
            {
                doubly_linked_list_node_t *tail = head;
                while (head)
                {
                    tail = head;
                    head = head->next;
                }
                node->prev = tail;
                tail->next = node;
                new_table->collisions += 1;
            }
            node = next_node;
        }
        counter++;
    }
    free(table->nodes);
    free(table);
    return new_table;
}
