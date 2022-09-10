#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#define FORWARD_LIST_VERSION "1.0.0"

#include <stddef.h>
#include <memory.h>
#include <stdbool.h>

struct forward_list_node_t;
typedef struct forward_list_node_t forward_list_node_t;

typedef struct forward_list_base_t {
    forward_list_node_t* list;
    //size_t size_list;
} forward_list_base_t;

/**
 * @brief forward_list_iter_t is pointeur to member of list
 */
typedef forward_list_node_t *forward_list_iter_t;


typedef forward_list_node_t const *forward_list_citer_t;


#define forward_list_t(Type)\
  struct { forward_list_base_t base; Type *ref; Type const *cref; Type tmp; }

#define forward_list_init(forward_list)\
    memset(forward_list, 0, sizeof(*(forward_list)))

#define forward_list_free(forward_list)\
    forward_list_free_(&(forward_list)->base)

#define forward_list_clear(forward_list)\
    forward_list_free(forward_list)

#define forward_list_get(forward_list, index)\
    ( (forward_list)->ref = forward_list_get_(&(forward_list)->base, index) )

#define forward_list_citer_get(forward_list, iter)\
    ( (forward_list)->cref = forward_list_citer_get_(iter) )

#define forward_list_front(forward_list)\
    ( (forward_list)->ref = forward_list_front_(&(forward_list)->base, 0) )

#define forward_list_insert_iter(forward_list, iter, value)\
    ( (forward_list)->tmp = (value),\
        forward_list_insert_iter_(iter, &(forward_list)->tmp, sizeof((forward_list)->tmp)) )

#define forward_list_insert_index(forward_list, value, index)\
    ( (forward_list)->tmp = (value),\
        forward_list_insert_index_(&(forward_list)->base, index, &(forward_list)->tmp, sizeof((forward_list)->tmp)) )

#define forward_list_push_front(forward_list, value)\
    ( (forward_list)->tmp = (value),\
        forward_list_push_front_(&(forward_list)->base, &(forward_list)->tmp, sizeof((forward_list)->tmp)) )

#define forward_list_size(forward_list)\
    forward_list_size_(&(forward_list)->base)

#define forward_list_erase_index(forward_list, index)\
    forward_list_erase_index_(&(forward_list)->base, index)

#define forward_list_erase_after_iter(forward_list, iter)\
    forward_list_remove_after_iter_(&(forward_list)->base, iter)

#define forward_list_pop_front(forward_list)\
    forward_list_pop_front_(&(forward_list)->base)


#define forward_list_iter(forward_list)\
    forward_list_iter_(&(forward_list)->base)

#define forward_list_citer(forward_list)\
    forward_list_citer_(&(forward_list)->base)


#define forward_list_next(iter)\
    forward_list_next_(iter)



void forward_list_free_(forward_list_base_t *const restrict forward_list);
void* forward_list_get_(forward_list_base_t *const restrict forward_list, size_t const index);
void const* forward_list_citer_get_(forward_list_citer_t const restrict iter);
void* forward_list_front_(forward_list_base_t *const restrict forward_list);
int forward_list_insert_iter_(forward_list_iter_t const restrict iter, void const *const restrict value, size_t const value_size);
int forward_list_insert_index_(forward_list_base_t *const restrict forward_list, size_t const index, void const *const restrict value, size_t const value_size);
int forward_list_push_front_(forward_list_base_t *const restrict forward_list, void const *const restrict value, size_t const value_size);
size_t forward_list_size_(forward_list_base_t *const restrict forward_list);
int forward_list_erase_index_(forward_list_base_t *const restrict forward_list, size_t const index);
int forward_list_erase_after_iter_(forward_list_iter_t const restrict iter);
int forward_list_pop_front_(forward_list_base_t *const restrict forward_list);
forward_list_iter_t forward_list_iter_(forward_list_base_t *const restrict forward_list);
forward_list_citer_t forward_list_citer_(forward_list_base_t *const restrict forward_list);
forward_list_citer_t forward_list_next_(forward_list_citer_t * restrict iter);

#endif