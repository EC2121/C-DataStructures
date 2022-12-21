#pragma once
#include <stdlib.h>
typedef struct doubly_linked_list_node
{
    struct doubly_linked_list_node *prev;
    struct doubly_linked_list_node *next;
    void *val;

} doubly_linked_list_node_t;

doubly_linked_list_node_t *doubly_linked_list_get_tail(doubly_linked_list_node_t **head)
{
    doubly_linked_list_node_t *current_node = *head;
    doubly_linked_list_node_t *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}
int doubly_linked_list_remove_node(doubly_linked_list_node_t **head, doubly_linked_list_node_t *node)
{
    if (!head || !node)
        return 0;
    
    if (node->next)
        node->next->prev = node->prev;

    if (node->prev)
        node->prev->next = node->next;
    else
    {
        *head = node->next;
    }
    return 1;
}
doubly_linked_list_node_t *doubly_linked_list_append(doubly_linked_list_node_t **head, doubly_linked_list_node_t *item)
{
    doubly_linked_list_node_t *tail = doubly_linked_list_get_tail(head);
    if (!tail)
    {
        *head = item;
        item->prev = NULL;
    }
    else
    {
        tail->next = item;
        item->prev = tail;
    }

    item->next = NULL;
    return item;
}
