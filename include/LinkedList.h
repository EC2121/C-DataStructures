#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LINKEDLIST_APPEND_PTR(list, str) linked_list_append((linked_list_node_t **)list, (linked_list_node_t *)list_item_new_sizet(str))
#define LINKEDLIST_APPEND_STR(list, str) linked_list_append((linked_list_node_t **)list, (linked_list_node_t *)list_item_new_str(str))
#define LINKEDLIST_REMOVE_AT_INDEX(list, index) linked_list_remove_at((linked_list_node_t **)list, index)
#define LINKEDLIST_REVERSE(list) lst_reverse((linked_list_node_t **)list)

typedef struct linked_list_node
{
    struct linked_list_node *next;
    void *val;
} linked_list_node_t;

typedef struct linked_list_item
{
    linked_list_node_t node;
} linked_list_item_t;

linked_list_node_t *linked_list_get_tail(linked_list_node_t **head)
{
    if (head == NULL)
    {
        return NULL;
    }
    linked_list_node_t *current_node = *head;
    linked_list_node_t *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

linked_list_node_t *linked_list_append(linked_list_node_t **head, linked_list_node_t *item)
{

    linked_list_node_t *tail = linked_list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}
linked_list_node_t *linked_list_pop(linked_list_node_t **head)
{
    if (head == NULL)
    {
        return NULL;
    }
    linked_list_node_t *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

linked_list_item_t *list_item_new_sizet(void *val)
{
    linked_list_item_t *item = malloc(sizeof(linked_list_item_t));
    if (!item)
    {
        return NULL;
    }
    item->node.val = malloc(sizeof(val));
    memcpy(item->node.val, val, sizeof(val));
    return item;
}

linked_list_item_t *list_item_new_str(char *val)
{
    linked_list_item_t *item = malloc(sizeof(linked_list_item_t));
    if (!item)
    {
        return NULL;
    }
    item->node.val = malloc(strlen(val) + 1);
    strcpy_s(item->node.val, strlen(val) + 1, val);
    return item;
}
int linked_list_len(linked_list_node_t **head)
{
    if(*head == NULL)
    {
        return 0;
    }
    int counter = 0;
    linked_list_node_t *cur_head = *head;
    while (cur_head)
    {
        cur_head = cur_head->next;
        counter++;
    }
    return counter;
}

void free_linked_list_node(linked_list_node_t *cur_head)
{
    free(cur_head->val);
    cur_head->val = NULL;
    free(cur_head);
    cur_head = NULL;
}

linked_list_node_t *linked_list_remove_at(linked_list_node_t **head, int index)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (index < 0 || index >= linked_list_len(head))
    {
        return NULL;
    }
    linked_list_node_t *prev = NULL;
    if (index == 0)
    {

        prev = *head;
        *head = (*head)->next;
        return prev;
        // free_linked_list_node(prev);
    }

    int counter = 0;
    linked_list_node_t *cur_head = *head;
    while (counter < index)
    {
        prev = cur_head;
        cur_head = cur_head->next;
        counter++;
    }

    prev->next = cur_head->next;
    return cur_head;
    // free_linked_list_node(cur_head);
}

void lst_reverse(linked_list_node_t **head)
{
    if (head == NULL)
    {
        return;
    }
    linked_list_node_t *curr_node = *head;
    linked_list_node_t *prev_node = NULL;
    linked_list_node_t *next_node = NULL;
    while (curr_node)
    {
        next_node = curr_node->next;
        curr_node->next = prev_node;
        prev_node = curr_node;
        curr_node = next_node;
    }
    *head = prev_node;
}
