#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "..\Includes\ListInclude.h"
#define list_append_str(list, str) list_append((struct list_node **)list, (struct list_node *)list_item_new(str))
#define list_remove_at_index(list, index) list_remove_at((struct list_node **)list, index)
#define list_reverse_def(list) list_reverse((struct list_node **)list)
#define list_append_after_index(list, item, index) list_append_aftr_index((struct list_node **)list, (struct list_node *)list_item_new(item), index)
#define list_append_before_index(list, item, index) list_append_befr_index((struct list_node **)list, (struct list_node *)list_item_new(item), index)
#define list_shuffle(list) list_shffle((struct list_node **)list)

struct list_item
{
    struct list_node node;
};

int list_len(list_node_t **head)
{

    int counter = 0;
    list_node_t *cur_head = *head;
    while (cur_head)
    {
        cur_head = cur_head->next;
        counter++;
    }
    return counter;
}

list_node_t *list_get_tail(list_node_t **head)
{
    list_node_t *current_node = *head;
    list_node_t *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

list_node_t *list_append(list_node_t **head, list_node_t *item)
{
    list_node_t *tail = list_get_tail(head);
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

list_node_t *list_append_aftr_index(list_node_t **head, list_node_t *item, int index)
{
    if (index == 0)
    {
        item->prev = *head;
        item->next = (*head)->next->next;
        (*head)->next = item;

        return item;
    }

    if (index > list_len(head) || index < 0)
    {
        return item;
    }
    int counter = 0;
    list_node_t *curr_node = *head;
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

list_node_t *list_append_befr_index(list_node_t **head, list_node_t *item, int index)
{
    if (index == 0)
    {
        item->next = *head;
        (*head)->prev = item;
        item->prev = NULL;
        *head = item;
        return item;
    }

    if (index > list_len(head) || index < 0)
    {
        return item;
    }
    int counter = 0;
    list_node_t *curr_node = *head;
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
list_node_t *list_pop(list_node_t **head)
{
    list_node_t *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

struct list_item *list_item_new(const char *string)
{
    struct list_item *item = malloc(sizeof(struct list_item));
    if (!item)
    {
        return NULL;
    }
    item->node.val = malloc(strlen(string) + 1);
    strcpy_s(item->node.val, strlen(string) + 1, string);
    return item;
}
void free_linked_list_node(list_node_t *cur_head){
    
    free(cur_head->val);
    cur_head->val = NULL;
    free(cur_head);
    cur_head = NULL;
}
int list_remove_at(list_node_t **head, int index)
{
    if (index < 0 || index >= list_len(head)) return 0;
    list_node_t *prev = NULL;
    if (index == 0)
    {
        prev = *head;
        *head = prev->next;
        prev->next = NULL;
        prev->prev = NULL;
        free_linked_list_node(prev);
        return 1;
    }

    int counter = 0;
    list_node_t *cur_node = *head;
    while (counter < index)
    {
        prev = cur_node;
        cur_node = cur_node->next;
        counter++;
    }

    prev->next = cur_node->next;


    if (prev->next) prev->next->prev = prev;
    free_linked_list_node(cur_node);
    return 1;
}

void list_reverse(list_node_t **head)
{
    list_node_t *curr_node = *head;
    list_node_t *prev_node = NULL;
    list_node_t *next_node = NULL;
    while (curr_node)
    {
        next_node = curr_node->next;
        curr_node->next = prev_node;
        prev_node = curr_node;
        curr_node = next_node;
    }
    *head = prev_node;
}

list_node_t *list_return_item_at_index(list_node_t **head, int index)
{
    if (index < 0 || index >= list_len(head)) return NULL;
    list_node_t *prev = NULL;
    if (index == 0)
    {
        prev = *head;
        *head = (*head)->next;
        prev->next = NULL;
        prev->prev = NULL;
        return prev;
    }

    int counter = 0;
    list_node_t *cur_node = *head;
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

list_node_t *get_item_at_index(list_node_t **head, int index)
{
    int counter = 0;
    list_node_t *cur_node = *head;
    while (counter < index)
    {
        cur_node = cur_node->next;
        counter++;
    }
    return cur_node;
}

void list_shffle(list_node_t **head)
{

    srand(time(NULL));
    int list_length = list_len(head);
    list_node_t *prev = NULL;
    list_node_t *cur_node = list_return_item_at_index(head, rand() % list_length);
    list_node_t *temp_head = cur_node;
    list_length--;

    while (list_length)
    {

        cur_node->prev = prev;
        cur_node->next = list_return_item_at_index(head, rand() % list_length);
        prev = cur_node;
        cur_node = cur_node->next;
        list_length--;
    }

    *head = temp_head;
}
int main()
{
    struct list_item *my_linked_list = NULL;
    list_append_str(&my_linked_list, "Hello World");
    list_append_str(&my_linked_list, "Test001");
    list_append_str(&my_linked_list, "Test002");
    list_append_str(&my_linked_list, "3");
    list_append_str(&my_linked_list, "4");
    list_append_str(&my_linked_list, "5");
    list_append_str(&my_linked_list, "6");
    list_append_str(&my_linked_list, "7");
    list_append_after_index(&my_linked_list, "Append After", 1);
    list_append_before_index(&my_linked_list, "Append before", 4);
    list_remove_at_index(&my_linked_list,9);
    list_remove_at_index(&my_linked_list,0);
    printf("-----BEFORE SHUFFLE-----\n");
    struct list_item *list_item = my_linked_list;
    while (list_item)
    {
        printf("%s\n", (char *)list_item->node.val);
        list_item = (struct list_item *)list_item->node.next;
    }
    printf("-----AFTER SHUFFLE-----\n");
    list_shuffle(&my_linked_list);
    list_item = my_linked_list;
    while (list_item)
    {
        printf("%s\n", (char *)list_item->node.val);
        list_item = (struct list_item *)list_item->node.next;
    }
    printf("-----END SHUFFLE-----\n");

    printf("list entries : %d\n", list_len((struct list_node **)&my_linked_list));
    return 0;
}