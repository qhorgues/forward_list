#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#if defined(__cplusplus)
extern "C"
{
#endif

#define FORWARD_LIST_VERSION "1.0.0"

#include <stddef.h>
#include <stdbool.h>

struct fw_list_t;
typedef struct fw_list_t fw_list_t;
/**
 * @brief fw_list_iter_t is pointeur to member of list
 */
typedef fw_list_t *fw_list_iter_t;
typedef fw_list_t const *fw_list_citer_t;

void fw_list_free(fw_list_t *forward_list);
void* fw_list_front(fw_list_t *forward_list);
fw_list_citer_t fw_list_cbegin(fw_list_t *forward_list);
fw_list_iter_t fw_list_begin(fw_list_t *forward_list);
fw_list_citer_t fw_list_cend(void);
fw_list_iter_t fw_list_end(void);
void const* fw_list_cget(fw_list_citer_t iter);
void* fw_list_get(fw_list_iter_t iter);
void fw_list_set(fw_list_iter_t iter, void const *value, size_t size_value);
bool fw_list_empty(fw_list_t const *forward_list);
fw_list_iter_t fw_list_insert_after(fw_list_iter_t iter, void const *value, size_t size_value);
int fw_list_erase_after(fw_list_iter_t iter);
int fw_list_push_front(fw_list_t **forward_list, void const *value, size_t size_value);
void fw_list_pop_front(fw_list_t **forward_list);
fw_list_citer_t fw_list_cnext(fw_list_citer_t iter);
fw_list_iter_t fw_list_next(fw_list_iter_t iter);
void fw_list_splice_after(fw_list_t **forward_list1, fw_list_t **forward_list2);
void fw_list_merge(fw_list_t **forward_list1, fw_list_t **forward_list2, int (*cmp)(const void*, const void*));
void fw_list_sort(fw_list_t **forward_list, int (*cmp)(const void*, const void*));


static inline fw_list_t* fw_list_init(void)
{
    return fw_list_end();
}

static inline void fw_list_clear(fw_list_t **forward_list)
{
    fw_list_free(*forward_list);
    *forward_list = fw_list_end();
}

#define fw_cbefore_begin(forward_list) \
    (fw_list_citer_t)(&forward_list)

#define fw_list_before_begin(forward_list) \
    (fw_list_iter_t)(&forward_list)

#if defined(__cplusplus)
}
#endif
    
#endif
