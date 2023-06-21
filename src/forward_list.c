#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <forward_list.h>

typedef struct forward_list_node_t
{
    struct forward_list_node_t* next;
} forward_list_node_t;

#define END_LIST_VALUE NULL

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
    memcpy((char*)(new + 1), value, size_value);

    return new;
}


/**************** COnstructor / Destructor ******************/

int forward_list_init_(forward_list_base_t *const restrict forward_list)
{
    memset(forward_list, 0, sizeof(*(forward_list)));
    forward_list->list = malloc(sizeof(forward_list_node_t));
    if (forward_list->list == NULL)
    {
        errno = ENOMEM;
        return -1;
    }
    forward_list->list->next = END_LIST_VALUE;
    return 0;
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

bool forward_list_is_init_(forward_list_base_t *const restrict forward_list)
{
    return forward_list->list != NULL;
}

/********************* Element access **********************/

void* forward_list_front_(forward_list_base_t *const restrict forward_list)
{
    forward_list_iter_t front = forward_list->list->next;
    return front +1;
}


/************************ Iterators ************************/

forward_list_citer_t forward_list_cbefore_begin_(forward_list_base_t *const restrict forward_list)
{
    return (forward_list_citer_t)(forward_list->list);
}

forward_list_iter_t forward_list_before_begin_(forward_list_base_t *const restrict forward_list)
{
    return (forward_list_iter_t)(forward_list->list);
}

forward_list_citer_t forward_list_cbegin_(forward_list_base_t *const restrict forward_list)
{
    return (forward_list_citer_t)(forward_list->list->next);
}

forward_list_iter_t forward_list_begin_(forward_list_base_t *const restrict forward_list)
{
    return (forward_list_iter_t)(forward_list->list->next);
}

forward_list_citer_t forward_list_cend_(void)
{
    return (forward_list_citer_t)(END_LIST_VALUE);
}

forward_list_iter_t forward_list_end_(void)
{
    return (forward_list_iter_t)(END_LIST_VALUE);
}

void const* forward_list_cget_(forward_list_citer_t const restrict iter)
{
    return (iter != NULL) ? iter +1 : NULL;
}

void* forward_list_get_(forward_list_iter_t const restrict iter)
{
    return (iter != NULL) ? iter +1 : NULL;
}

void forward_list_set_(forward_list_iter_t restrict iter,
                                   void const *const restrict value, 
                                   size_t const size_value)
{
    memcpy(iter +1, value, size_value);
}

/*********** Capacity ***********/

bool forward_list_empty_(forward_list_base_t *const restrict forward_list)
{
    return forward_list->list->next == END_LIST_VALUE;
}

/********** Modifiers ***********/

void forward_list_clear_(forward_list_base_t *const restrict forward_list)
{
    forward_list_iter_t iter = forward_list->list->next;
    while (iter != END_LIST_VALUE)
    {
        forward_list_iter_t const tmp_iter = iter->next;
        free(iter);
        iter = tmp_iter;
    }
    forward_list->list->next = END_LIST_VALUE;
}


forward_list_iter_t forward_list_insert_after_(forward_list_iter_t const restrict iter,
                              void const *const restrict value, 
                              size_t const size_value)
{
    forward_list_iter_t new = new_node(value, size_value, iter->next);
    if (new == NULL)
    {
        return END_LIST_VALUE;
    }
    iter->next = new;
    return new;
}

int forward_list_erase_after_(forward_list_iter_t const restrict iter)
{
    if (iter->next == END_LIST_VALUE)
    {
        errno = EDOM;
        return EDOM;
    }
    forward_list_iter_t iter_next = iter->next->next;
    free(iter->next);
    iter->next = iter_next;
    return 0;
}

forward_list_iter_t forward_list_push_front_(forward_list_base_t *const restrict forward_list, 
                             void const *const value, 
                             size_t const size_value)
{
    forward_list_iter_t new = new_node(value, size_value, forward_list->list->next);
    if (new == NULL)
    {
        return END_LIST_VALUE;
    }
    forward_list->list->next = new;
    return new;
}

int forward_list_pop_front_(forward_list_base_t *const restrict forward_list)
{
    forward_list_iter_t iter_next = forward_list->list->next->next;
    free(forward_list->list->next);
    forward_list->list->next = iter_next;
    return 0;
}

forward_list_citer_t forward_list_cnext(forward_list_citer_t iter)
{
    if (iter == END_LIST_VALUE)
    {
        errno = EFAULT;
        return END_LIST_VALUE;
    }
    return iter->next;
}

forward_list_iter_t forward_list_next(forward_list_iter_t iter)
{
    if (iter == END_LIST_VALUE)
    {
        errno = EFAULT;
        return END_LIST_VALUE;
    }
    return iter->next;
}

void forward_list_merge_(forward_list_base_t* restrict forward_list1, forward_list_base_t* restrict forward_list2)
{
    if (forward_list1->list == NULL)
    {
        forward_list_init_(forward_list1);
        if (forward_list2->list != NULL)
        {
            forward_list1->list->next = forward_list2->list->next;
            forward_list2->list->next = END_LIST_VALUE;
        }
        return;
    }
    else if (forward_list2->list == NULL)
    {
        return;
    }
    else if (forward_list2->list->next == END_LIST_VALUE)
    {
        forward_list_free_(forward_list2);
    }
    else
    {
        fw_list_iter_t iter = forward_list_before_begin_(forward_list1);
        for (; fw_list_next(iter) != END_LIST_VALUE; iter = fw_list_next(iter));
        
        iter->next = forward_list2->list->next;
        forward_list2->list->next = END_LIST_VALUE;
        forward_list_free_(forward_list2);
    }
}