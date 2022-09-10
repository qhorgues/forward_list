#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include "forward_list.h"

typedef struct forward_list_node_t
{
    struct forward_list_node_t* next;
} forward_list_node_t;

static forward_list_node_t* new_node(void const *const restrict value, size_t const value_size, forward_list_node_t *const next)
{
    forward_list_node_t* new = malloc(sizeof(forward_list_node_t) + value_size);
    if (new == NULL)
    {
        return NULL;
    }

    new->next = next;
    memcpy(new + 1, value, value_size);

    return new;
}

void forward_list_free_(forward_list_base_t *const restrict forward_list)
{
    forward_list_iter_t iter = forward_list->list;
    while (iter != NULL)
    {
        forward_list_iter_t const tmp_iter = iter->next;
        free(iter);
        iter = tmp_iter;
    }
    forward_list->list = NULL;
}

void* forward_list_get_(forward_list_base_t *const restrict forward_list, size_t const index)
{
    forward_list_iter_t iter = forward_list->list;
    for (size_t i = 0; i < index && iter != NULL; i++)
    {
        iter = iter->next;
    }
    return iter != NULL ? iter + 1 : NULL;
}

void const* forward_list_citer_get_(forward_list_citer_t const restrict iter)
{
    if (iter == NULL)
    {
        return NULL;
    }
    return iter +1;
}

void* forward_list_front_(forward_list_base_t *const restrict forward_list)
{
    return forward_list->list +1;
}

int forward_list_insert_iter_(forward_list_iter_t const restrict iter, void const *const restrict value, size_t const value_size)
{
    if (iter == NULL)
    {
        return EFAULT;
    }
    forward_list_iter_t new = new_node(value, value_size, iter->next);
    if (new == NULL)
    {
        return errno;
    }
    iter->next = new;
    return 0;
}

int forward_list_insert_index_(forward_list_base_t *const restrict forward_list, size_t const index, void const *const restrict value, size_t const value_size)
{
    forward_list_iter_t iter = forward_list->list;
    for (size_t i = 0; i < index && iter != NULL; i++)
    {
        iter = iter->next;
    }
    if (iter != NULL)
    {
        forward_list_iter_t new = new_node(value, value_size, iter->next);
        if (new == NULL)
        {
            return errno;
        }
        iter->next = new;
        return 0;
    }
    return EDOM;
}

int forward_list_push_front_(forward_list_base_t *const restrict forward_list, void const *const value, size_t const value_size)
{
    forward_list_iter_t new = new_node(value, value_size, forward_list->list);
    if (new == NULL)
    {
        return errno;
    }
    forward_list->list = new;
    return 0;
}

size_t forward_list_size_(forward_list_base_t *const restrict forward_list)
{
    size_t size_list = 0;
    forward_list_citer_t it_list = forward_list->list;
    while (it_list != NULL)
    {
        it_list = it_list->next;
        size_list++;
    }
    return size_list;
}

int forward_list_erase_index_(forward_list_base_t *const restrict forward_list, size_t const index)
{
    forward_list_iter_t iter = forward_list->list;
    if (index > 0)
    {
        for (size_t i = 0; i < index-1 && iter->next != NULL; i++)
        {
            iter = iter->next;
        }
        if (iter->next == NULL)
        {
            return EDOM;
        }
        forward_list_iter_t iter_next = iter->next->next;
        free(iter->next);
        iter->next = iter_next;
        return 0;
    }
    else if (iter != NULL)
    {
        forward_list_iter_t iter_next = iter->next;
        free(iter);
        forward_list->list = iter_next;
        return 0;
    }
    return EDOM;
}

int forward_list_erase_after_iter_(forward_list_iter_t const restrict iter)
{
    if (iter == NULL)
    {
        return EFAULT;
    }
    if (iter->next == NULL)
    {
        return EDOM;
    }
    forward_list_iter_t iter_next = iter->next->next;
    free(iter->next);
    iter->next = iter_next;
    return 0;
}

int forward_list_pop_front_(forward_list_base_t *const restrict forward_list)
{
    if (forward_list->list == NULL)
    {
        return EDOM;
    }
    forward_list_iter_t iter_next = forward_list->list->next;
    free(forward_list->list);
    forward_list->list = iter_next;
    return 0;
}

forward_list_citer_t forward_list_citer_(forward_list_base_t *const restrict forward_list)
{
    return forward_list->list;
}

forward_list_iter_t forward_list_iter_(forward_list_base_t *const restrict forward_list)
{
    return forward_list->list;
}

forward_list_citer_t forward_list_next_(forward_list_citer_t * restrict iter)
{
    if (iter == NULL || (*iter)->next == NULL)
    {
        return NULL;
    }
    (*iter) = (*iter)->next;
    return *iter;
}