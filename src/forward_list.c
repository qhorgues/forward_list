#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <forward_list.h>

typedef struct fw_list_t
{
    struct fw_list_t* next;
} fw_list_t;

#define END_LIST_VALUE NULL

static fw_list_t* new_node(void const *value, size_t size_value, fw_list_t *next)
{
    fw_list_t* new = malloc(sizeof(fw_list_t) + size_value);
    if (new == NULL)
    {
        return NULL;
    }

    new->next = next;
    memcpy(new + 1, value, size_value);

    return new;
}


/**************** Constructor / Destructor ******************/


void fw_list_free(fw_list_t *forward_list)
{
    fw_list_iter_t iter = fw_list_begin(forward_list);
    while (iter != fw_list_end())
    {
        fw_list_iter_t const tmp_iter = iter->next;
        free(iter);
        iter = tmp_iter;
    }
}


/********************* Element access **********************/

void* fw_list_front(fw_list_t *forward_list)
{
    return forward_list +1;
}


/************************ Iterators ************************/



fw_list_citer_t fw_list_cbegin(fw_list_t *forward_list)
{
    return (fw_list_citer_t)(forward_list);
}

fw_list_iter_t fw_list_begin(fw_list_t *forward_list)
{
    return (fw_list_iter_t)(forward_list);
}

fw_list_citer_t fw_list_cend(void)
{
    return (fw_list_citer_t)(END_LIST_VALUE);
}

fw_list_iter_t fw_list_end(void)
{
    return (fw_list_iter_t)(END_LIST_VALUE);
}

void const* fw_list_cget(fw_list_citer_t iter)
{
    return iter +1;
}

void* fw_list_get(fw_list_iter_t iter)
{
    return iter +1;
}

void fw_list_set(fw_list_iter_t iter, void const *value, size_t size_value)
{
    #ifdef __STDC_LIB_EXT1_
        memcpy_s(iter +1, size_value, value, size_value);
    #else
        memcpy(iter +1, value, size_value);
    #endif
}

/*********** Capacity ***********/

bool fw_list_empty(fw_list_t const *forward_list)
{
    return forward_list == END_LIST_VALUE;
}

/********** Modifiers ***********/


fw_list_iter_t fw_list_insert_after(fw_list_iter_t iter, void const *value, size_t size_value)
{
    fw_list_iter_t new = new_node(value, size_value, iter->next);
    if (new == NULL)
    {
        return END_LIST_VALUE;
    }
    iter->next = new;
    return new;
}

int fw_list_erase_after(fw_list_iter_t iter)
{
    if (iter->next == END_LIST_VALUE)
    {
        errno = EDOM;
        return EDOM;
    }
    fw_list_iter_t iter_next = iter->next->next;
    free(iter->next);
    iter->next = iter_next;
    return 0;
}

int fw_list_push_front(fw_list_t **forward_list, void const *value, size_t size_value)
{
    fw_list_t* new = new_node(value, size_value, *forward_list);
    if (new == NULL)
    {
        return -1;
    }
    *forward_list = new;
    return 0;
}

void fw_list_pop_front(fw_list_t **forward_list)
{
    fw_list_t* iter_front = *forward_list;
    *forward_list = (*forward_list)->next;
    free(iter_front);
}

fw_list_citer_t fw_list_cnext(fw_list_citer_t iter)
{
    if (iter == END_LIST_VALUE)
    {
        errno = EFAULT;
        return END_LIST_VALUE;
    }
    return iter->next;
}

fw_list_iter_t fw_list_next(fw_list_iter_t iter)
{
    if (iter == END_LIST_VALUE)
    {
        errno = EFAULT;
        return END_LIST_VALUE;
    }
    return iter->next;
}

void fw_list_splice_after(fw_list_t **forward_list1, fw_list_t **forward_list2)
{
    if (fw_list_empty(*forward_list2))
    {
        return;
    }
    else if (fw_list_empty(*forward_list1))
    {
        *forward_list1 = *forward_list2;
        *forward_list2 = END_LIST_VALUE;
    }
    else
    {
        fw_list_iter_t iter = fw_list_before_begin(*forward_list1);
        fw_list_iter_t next = fw_list_next(iter);
        while (next != END_LIST_VALUE)
        {
            iter = next;
            next = fw_list_next(next);
        }
        
        iter->next = *forward_list2;
    }
    *forward_list2 = END_LIST_VALUE;
}

static fw_list_t* merge(fw_list_t *forward_list1, fw_list_t *forward_list2, int (*cmp)(const void*, const void*))
{
    if (forward_list1 == END_LIST_VALUE)
    {
        return forward_list2;
    }
    else if (forward_list2 == END_LIST_VALUE) {
        return forward_list1;
    }
 
    fw_list_t* result;
 
    // sélectionne `a` ou `b`, et se reproduit
    if ((*cmp)(fw_list_cget(forward_list1), fw_list_cget(forward_list2)) <= 0)
    {
        result = forward_list1;
        result->next = merge(forward_list1->next, forward_list2, cmp);
    }
    else {
        result = forward_list2;
        result->next = merge(forward_list1, forward_list2->next, cmp);
    }
 
    return result;
}

void fw_list_merge(fw_list_t **forward_list1, fw_list_t **forward_list2, int (*cmp)(const void*, const void*))
{
    *forward_list1 = merge(*forward_list1, *forward_list2, cmp);
    *forward_list2 = END_LIST_VALUE;
}

static void frontBackSplit(fw_list_t *list, fw_list_t **frontRef, fw_list_t **backRef)
{
    if (list == END_LIST_VALUE || list->next == END_LIST_VALUE)
    {
        *frontRef = list;
        *backRef = END_LIST_VALUE;
        return;
    }
 
    fw_list_t* slow = list;
    fw_list_t* fast = list->next;

    while (fast != END_LIST_VALUE)
    {
        fast = fast->next;
        if (fast != END_LIST_VALUE)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    *frontRef = list;
    *backRef = slow->next;
    slow->next = END_LIST_VALUE;
}
 
void fw_list_sort(fw_list_t **forward_list, int (*cmp)(const void*, const void*))
{
    // cas de base — longueur 0 ou 1
    if (*forward_list == END_LIST_VALUE || (*forward_list)->next == END_LIST_VALUE) {
        return;
    }
 
    fw_list_t* left;
    fw_list_t* right;
 
    // divise `head` en sous-listes `a` et `b`
    frontBackSplit(*forward_list, &left, &right);
 
    // trie récursivementment les sous-listes
    fw_list_sort(&left, cmp);
    fw_list_sort(&right, cmp);
 
    // réponse = fusionner les deux listes triées
    fw_list_merge(&left, &right, cmp);
    *forward_list = left;
}