#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <forward_list.h>

typedef struct forward_list_node_t
{
    struct forward_list_node_t* next;
} forward_list_node_t;

static forward_list_node_t* new_node(void const *const restrict value,
                                     size_t const size_value, 
                                     forward_list_node_t *const next)
{
    forward_list_node_t* new = malloc(sizeof(forward_list_node_t) + size_value);
    if (new == NULL)
    {
        return NULL;
    }

    new->next = next;
    memcpy(new + 1, value, size_value);

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

void* forward_list_get_(forward_list_base_t *const restrict forward_list,
                        size_t const index)
{
    forward_list_iter_t iter = forward_list->list;
    for (size_t i = 0; i < index && iter != NULL; i++)
    {
        iter = iter->next;
    }
    if (iter == NULL)
    {
        errno = EDOM;
        return NULL;
    }
    return iter +1;
}

void const* forward_list_citer_get_(forward_list_citer_t const restrict iter)
{
    if (iter == NULL)
    {
        errno = EFAULT;
        return NULL;
    }
    return iter +1;
}

void* forward_list_iter_get_(forward_list_iter_t const restrict iter)
{
    if (iter == NULL)
    {
        errno = EFAULT;
        return NULL;
    }
    return iter +1;
}

void forward_list_set_(forward_list_base_t *const restrict forward_list, 
                       size_t const index, 
                       void const *const restrict value, 
                       size_t const size_value)
{
    forward_list_iter_t iter = forward_list->list;
    for (size_t i = 0; i < index && iter != NULL; i++)
    {
        iter = iter->next;
    }
    if (iter == NULL)
    {
        errno = EDOM;
        return;
    }
    memcpy(iter +1, value, size_value);
}

void forward_list_iter_set_(forward_list_iter_t restrict iter,
                                   void const *const restrict value, 
                                   size_t const size_value)
{
    if (iter == NULL)
    {
        errno = EFAULT;
        return;
    }
    memcpy(iter +1, value, size_value);
}

void* forward_list_front_(forward_list_base_t *const restrict forward_list)
{
    return forward_list->list +1;
}

int forward_list_iter_insert_(forward_list_iter_t const restrict iter,
                              void const *const restrict value, 
                              size_t const size_value)
{
    if (iter == NULL)
    {
        errno = EFAULT;
        return EFAULT;
    }
    forward_list_iter_t new = new_node(value, size_value, iter->next);
    if (new == NULL)
    {
        return errno;
    }
    iter->next = new;
    return 0;
}

int forward_list_index_insert_(forward_list_base_t *const restrict forward_list,
                               size_t const index, 
                               void const *const restrict value,
                               size_t const size_value)
{
    if (index > 0)
    {
        forward_list_iter_t iter = forward_list->list;
        for (size_t i = 0; i < index -1 && iter != NULL; i++)
        {
            iter = iter->next;
        }
        if (iter != NULL)
        {
            forward_list_iter_t new = new_node(value, size_value, iter->next);
            if (new == NULL)
            {
                return errno;
            }
            iter->next = new;
            return 0;
        }
        errno = EDOM;
        return EDOM;
    }
    else
    {
        return forward_list_push_front_(forward_list, value, size_value);
    }
    
}

int forward_list_push_front_(forward_list_base_t *const restrict forward_list, 
                             void const *const value, 
                             size_t const size_value)
{
    forward_list_iter_t new = new_node(value, size_value, forward_list->list);
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

int forward_list_erase_index_(forward_list_base_t *const restrict forward_list, 
                              size_t const index)
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
            errno = EDOM;
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
    errno = EDOM;
    return EDOM;
}

int forward_list_erase_after_iter_(forward_list_iter_t const restrict iter)
{
    if (iter == NULL)
    {
        errno = EFAULT;
        return EFAULT;
    }
    if (iter->next == NULL)
    {
        errno = EDOM;
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
        errno = EDOM;
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

forward_list_citer_t forward_list_citer_next_(forward_list_citer_t * restrict iter)
{
    if (*iter == NULL)
    {
        errno = EFAULT;
        return NULL;
    }
    else if ((*iter)->next == NULL)
    {
        return NULL;
    }
    (*iter) = (*iter)->next;
    return *iter;
}

forward_list_iter_t forward_list_iter_next_(forward_list_iter_t * restrict iter)
{
    if (*iter == NULL)
    {
        errno = EFAULT;
        return NULL;
    }
    else if ((*iter)->next == NULL)
    {
        return NULL;
    }
    (*iter) = (*iter)->next;
    return *iter;
}