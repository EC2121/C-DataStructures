#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\Includes\SetsInclude.h"


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
    free(((key_data_t *)head->val)->key);
    ((key_data_t *)head->val)->key = NULL;
    free((key_data_t *)head->val);
    head->val = NULL;
}
int set_table_remove(struct set_table *table, const char *key, const size_t key_len)
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

    free_set_table_entry(head);
    return 1;
}


list_node_t *set_insert(struct set_table **table, char *key, const size_t key_len)
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
    if (!head)
    {
        (*table)->nodes[index] = malloc(sizeof(list_node_t));
        key_data_t *key_data = calloc(1, sizeof(key_data_t));
        if (!(*table)->nodes[index] || !key_data)
        {
            return NULL;
        }
        (*table)->nodes[index]->val = key_data;
        key_data_t *entry = (*table)->nodes[index]->val;
        entry->key = malloc(key_len + 1);
        strcpy_s(entry->key, key_len + 1, key);
       
        entry->key_len = key_len;
        (*table)->nodes[index]->next = NULL;
        (*table)->nodes[index]->prev = NULL;
        return (*table)->nodes[index];
    }
    list_node_t *new_item = malloc(sizeof(list_node_t));
    key_data_t *key_data = calloc(1, sizeof(key_data_t));
    if (!new_item || !key_data)
    {
        return NULL;
    }
    new_item->val = key_data;
    key_data_t *entry = new_item->val;
    entry->key = malloc(key_len + 1);
    strcpy_s(entry->key, key_len + 1, key);
    entry->key_len = key_len;
    new_item->next = NULL;
    list_node_t *tail = head;
    while (head)
    {
        tail = head;
        head = head->next;
    }
    new_item->prev = tail;
    tail->next = new_item;
    (*table)->collisions += 1;
    if ((*table)->collisions > (*table)->hashmap_size * 0.25f)
    {   
        printf("INSERTING %s CAUSED TOO MANY COLLISIONS REGENARTION NEEDED\n",((key_data_t *)new_item->val)->key);
        (*table) = set_table_regenerate(*table);
    }
    return new_item;
}


int main()
{
    const size_t hashmap_size = 1;
    struct set_table *table = set_table_new(hashmap_size);
    printf("-----START INSERT-----\n");
    set_insert(&table, "HelloWorld!", 4);
    set_insert(&table, "HelloWorld!", 4);
    set_insert(&table, "1", 1);
    set_insert(&table, "2", 1);
    set_insert(&table, "3", 1);
    set_insert(&table, "4", 1);
    set_insert(&table, "5", 1);
    set_insert(&table, "6", 1);
    set_insert(&table, "7", 1);
    set_insert(&table, "8", 1);
    set_insert(&table, "9", 1);
    set_insert(&table, "0", 1);
    set_insert(&table, "0", 1);
    set_insert(&table, "0", 1);
    set_table_remove(table,"ciao",4);
    printf("HashmapSize = %llu\n",table->hashmap_size);
    printf("-----END INSERT-----\n");
    printf("-----SET TABLE PRINT START-----\n");
    set_table_print(table);
    printf("-----SET TABLE PRINT END-----\n");

    
    printf("-----SET TABLE SEARCH START-----\n");
    list_node_t *result_node = set_table_search(table, "1", 1);
    if(result_node){
        printf("%s WAS FOUND\n",((key_data_t *)result_node->val)->key);
        result_node = result_node->next;
    }
    while (result_node)
    {
        printf("LINKED TO: %s\n", ((key_data_t *)result_node->val)->key);
        result_node = result_node->next;
    }
    printf("-----SET TABLE SEARCH END-----\n");

}