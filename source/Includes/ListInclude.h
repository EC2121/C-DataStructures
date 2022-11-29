
typedef struct list_node
{
    struct list_node *prev;
    struct list_node *next;
    void *val;

} list_node_t;

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
int list_remove_node(list_node_t **head, list_node_t *node)
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
