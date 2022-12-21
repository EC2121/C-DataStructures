#include <stddef.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "DoublyLinkedListIncludes.h"
#define DOUBLY_LINKED_LIST_APPEND_STR(list, str) doubly_linked_list_append((doubly_linked_list_node_t **)list, (doubly_linked_list_node_t *)doubly_linked_list_item_new(str))
#define DOUBLY_LINKED_LIST_REMOVE_AT(list, index) doubly_linked_list_remove_at(doubly_linked_list_node_t**)list, index)
#define DOUBLY_LINKED_doubly_linked_list_reverse(list) doubly_linked_list_reverse((doubly_linked_list_node_t**)list)
#define DOUBLY_LINKED_LIST_APPEND_AFTER_INDEX(list, item, index) doubly_linked_list_append_after((doubly_linked_list_node_t **)list, (doubly_linked_list_node_t *)doubly_linked_list_item_new(item), index)
#define DOUBLY_LINKED_LIST_APPEND_BEFORE_INDEX(list, item, index) doubly_linked_list_append_before((doubly_linked_list_node_t **)list, (doubly_linked_list_node_t *)doubly_linked_list_item_new(item), index)
#define DOUBLY_LINKED_LIST_SHUFFLE(list) doubly_linked_list_shuffle((doubly_linked_list_node_t **)list)

struct doubly_linked_list_item
{
    doubly_linked_list_node_t node;
};

int doubly_linked_list_len(doubly_linked_list_node_t **head)
{

    int counter = 0;
    doubly_linked_list_node_t *cur_head = *head;
    while (cur_head)
    {
        cur_head = cur_head->next;
        counter++;
    }
    return counter;
}


doubly_linked_list_node_t *doubly_linked_list_append_after(doubly_linked_list_node_t **head, doubly_linked_list_node_t *item, int index)
{
    if (index == 0)
    {
        item->prev = *head;
        item->next = (*head)->next->next;
        (*head)->next = item;

        return item;
    }

    if (index > doubly_linked_list_len(head) || index < 0)
    {
        return item;
    }
    int counter = 0;
    doubly_linked_list_node_t *curr_node = *head;
    while (counter < index)
    {
        curr_node = curr_node->next;
        counter++;
    }
    item->next = curr_node->next;
    item->prev = curr_node;
    curr_node->next = item;

    return item;
}

doubly_linked_list_node_t *doubly_linked_list_append_before(doubly_linked_list_node_t **head, doubly_linked_list_node_t *item, int index)
{
    if (index > doubly_linked_list_len(head) || index < 0)
    {
        return NULL;
    }

    if (index == 0)
    {
        item->next = *head;
        (*head)->prev = item;
        item->prev = NULL;
        *head = item;
        return item;
    }


    int counter = 0;
    doubly_linked_list_node_t *curr_node = *head;
    while (counter < index)
    {
        curr_node = curr_node->next;
        counter++;
    }
    item->next = curr_node;
    item->prev = curr_node->prev;
    curr_node->prev->next = item;

    return item;
}
doubly_linked_list_node_t *doubly_linked_list_pop(doubly_linked_list_node_t **head)
{
    doubly_linked_list_node_t *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

struct doubly_linked_list_item *doubly_linked_list_item_new(const char *string)
{
    struct doubly_linked_list_item *item = malloc(sizeof(struct doubly_linked_list_item));
    if (!item)
    {
        return NULL;
    }
    item->node.val = malloc(strlen(string) + 1);
    strcpy_s(item->node.val, strlen(string) + 1, string);
    return item;
}
void free_dobuly_linked_list_node(doubly_linked_list_node_t *cur_head){
    
    free(cur_head->val);
    cur_head->val = NULL;
    free(cur_head);
    cur_head = NULL;
}

int doubly_linked_list_remove(doubly_linked_list_node_t **head, int index)
{
    if (index < 0 || index >= doubly_linked_list_len(head)) return 0;
    doubly_linked_list_node_t *prev = NULL;
    if (index == 0)
    {
        prev = *head;
        *head = prev->next;
        prev->next = NULL;
        prev->prev = NULL;
        free_dobuly_linked_list_node(prev);
        
        return 1;
    }

    int counter = 0;
    doubly_linked_list_node_t *cur_node = *head;
    while (counter < index)
    {
        prev = cur_node;
        cur_node = cur_node->next;
        counter++;
    }

    prev->next = cur_node->next;


    if (prev->next) prev->next->prev = prev;
    free_dobuly_linked_list_node(cur_node);
    return 1;
}

void doubly_linked_list_reverse(doubly_linked_list_node_t **head)
{
    doubly_linked_list_node_t *curr_node = *head;
    doubly_linked_list_node_t *prev_node = NULL;
    doubly_linked_list_node_t *next_node = NULL;
    while (curr_node)
    {
        next_node = curr_node->next;
        curr_node->next = prev_node;
        prev_node = curr_node;
        curr_node = next_node;
    }
    *head = prev_node;
}

doubly_linked_list_node_t *doubly_linked_list_return_item_at(doubly_linked_list_node_t **head, int index)
{
    if (index < 0 || index >= doubly_linked_list_len(head)) return NULL;
    doubly_linked_list_node_t *prev = NULL;
    if (index == 0)
    {
        prev = *head;
        *head = (*head)->next;
        prev->next = NULL;
        prev->prev = NULL;
        return prev;
    }

    int counter = 0;
    doubly_linked_list_node_t *cur_node = *head;
    while (counter < index)
    {
        prev = cur_node;
        cur_node = cur_node->next;
        counter++;
    }

    prev->next = cur_node->next;


    if (prev->next) prev->next->prev = prev;

    return cur_node;
}

doubly_linked_list_node_t *doubly_linked_list_remove_item_at(doubly_linked_list_node_t **head, int index)
{
    int counter = 0;
    doubly_linked_list_node_t *cur_node = *head;
    while (counter < index)
    {
        cur_node = cur_node->next;
        counter++;
    }
    return cur_node;
}

void doubly_linked_list_shuffle(doubly_linked_list_node_t **head)
{

    srand(time(NULL));
    int doubly_linked_list_length = doubly_linked_list_len(head);
    doubly_linked_list_node_t *prev = NULL;
    doubly_linked_list_node_t *cur_node = doubly_linked_list_return_item_at(head, rand() % doubly_linked_list_length);
    doubly_linked_list_node_t *temp_head = cur_node;
    doubly_linked_list_length--;

    while (doubly_linked_list_length)
    {

        cur_node->prev = prev;
        cur_node->next = doubly_linked_list_return_item_at(head, rand() % doubly_linked_list_length);
        prev = cur_node;
        cur_node = cur_node->next;
        doubly_linked_list_length--;
    }

    *head = temp_head;
}
