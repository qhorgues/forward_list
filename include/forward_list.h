#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#if defined(__cplusplus)
extern "C"
{
#endif

#define FORWARD_LIST_VERSION "1.0.0"

#include <stddef.h>
#include <stdbool.h>

struct forward_list_node_t;
typedef struct forward_list_node_t forward_list_node_t;

typedef struct forward_list_base_t {
    forward_list_node_t* list;
} forward_list_base_t;

/**
 * @brief forward_list_iter_t is pointeur to member of list
 */
typedef forward_list_node_t *forward_list_iter_t;


typedef forward_list_node_t const *forward_list_citer_t;


#define forward_list_t(Type)\
    struct { \
        forward_list_base_t base; \
        Type *ref; \
        Type const *cref; \
        Type tmp; \
    }


/**************** Constructor / Destructor ******************/

#define forward_list_init(forward_list)\
    forward_list_init_(&(forward_list).base)

#define forward_list_free(forward_list)\
    forward_list_free_(&(forward_list).base)

#define forward_list_is_init(forward_list)\
    forward_list_is_init_(&(forward_list).base)


/********************* Element access **********************/

#define forward_list_front(forward_list)\
    ( (forward_list)->ref = forward_list_front_(&(forward_list).base) )


/************************ Iterators ************************/

#define forward_list_cbefore_begin(forward_list)\
    forward_list_cbefore_begin_(&(forward_list).base)

#define forward_list_before_begin(forward_list)\
    forward_list_before_begin_(&(forward_list).base)

#define forward_list_cbegin(forward_list)\
    forward_list_cbegin_(&(forward_list).base)

#define forward_list_begin(forward_list)\
    forward_list_begin_(&(forward_list).base)

#define forward_list_cend()\
    forward_list_cend_()

#define forward_list_end()\
    forward_list_end_()

#define forward_list_cget(forward_list, const_iterator)\
    ( forward_list.cref = forward_list_cget_(const_iterator) )

#define forward_list_get(forward_list, iterator)\
    ( forward_list.ref = forward_list_get_(iterator) )

#define forward_list_set(forward_list, iterator, value) \
    ( forward_list.tmp = value,\
        forward_list_set_(iterator, forward_list.tmp, \
                                  sizeof((forward_list)->tmp)) )


/*********** Capacity ***********/

#define forward_list_empty(forward_list)\
    forward_list_empty_(&(forward_list).base)



/********** Modifiers ***********/

#define forward_list_clear(forward_list)\
    forward_list_clear_(&(forward_list).base)

#define forward_list_insert_after(forward_list, iterator, value)\
    (forward_list.tmp = value, \
        forward_list_insert_after_(iterator, &(forward_list).tmp, sizeof (value)))

#define forward_list_erase_after(forward_list, iterator)\
    forward_list_erase_after_(iterator)

#define forward_list_push_front(forward_list, value)\
    (forward_list.tmp = value, \
        forward_list_push_front_(&(forward_list).base, &(forward_list).tmp, sizeof (value)))

#define forward_list_pop_front(forward_list)\
    forward_list_pop_front_(&(forward_list).base)


/********** Operations ***********/

#define forward_list_splice_after(forward_list_1, forward_list_2) \
    forward_list_splice_after_(&(forward_list_1).base, &(forward_list_2).base)

int forward_list_init_(forward_list_base_t *const restrict forward_list);

void forward_list_free_(forward_list_base_t *const restrict forward_list);

bool forward_list_is_init_(forward_list_base_t *const restrict forward_list);

void* forward_list_front_(forward_list_base_t *const restrict forward_list);

forward_list_citer_t forward_list_cbefore_begin_(forward_list_base_t *const restrict forward_list);

forward_list_iter_t forward_list_before_begin_(forward_list_base_t *const restrict forward_list);

forward_list_citer_t forward_list_cbegin_(forward_list_base_t *const restrict forward_list);

forward_list_iter_t forward_list_begin_(forward_list_base_t *const restrict forward_list);

forward_list_citer_t forward_list_cend_(void);

forward_list_iter_t forward_list_end_(void);

void const* forward_list_cget_(forward_list_citer_t const restrict iter);

void* forward_list_get_(forward_list_iter_t const restrict iter);

void forward_list_set_(forward_list_iter_t restrict iter,
                                   void const *const restrict value, 
                                   size_t const size_value);

bool forward_list_empty_(forward_list_base_t *const restrict forward_list);

void forward_list_clear_(forward_list_base_t *const restrict forward_list);

forward_list_iter_t forward_list_insert_after_(forward_list_iter_t const restrict iter,
                              void const *const restrict value, 
                              size_t const size_value);

int forward_list_erase_after_(forward_list_iter_t const restrict iter);

forward_list_iter_t forward_list_push_front_(forward_list_base_t *const restrict forward_list, 
                             void const *const value, 
                             size_t const size_value);

int forward_list_pop_front_(forward_list_base_t *const restrict forward_list);

forward_list_citer_t forward_list_cnext(forward_list_citer_t iter);

forward_list_iter_t forward_list_next(forward_list_iter_t iter);

void forward_list_splice_after_(forward_list_base_t* restrict forward_list1, forward_list_base_t* restrict forward_list2);

// Alias fw

typedef forward_list_iter_t fw_list_iter_t;

typedef forward_list_citer_t fw_list_citer_t;

#define fw_list_t(Type)  \
            forward_list_t(Type)

#define fw_list_init(forward_list)  \
            forward_list_init(forward_list)

#define fw_list_free(forward_list)  \
            forward_list_free(forward_list)

#define fw_list_clear(forward_list)  \
            forward_list_clear(forward_list)

#define fw_list_get(forward_list, iterator)  \
            forward_list_get(forward_list, iterator)

#define fw_list_cget(forward_list, const_iterator)  \
            forward_list_cget(forward_list, const_iterator)

#define fw_list_set(forward_list, index, value)  \
            forward_list_set(forward_list, index, value)

#define fw_list_front(forward_list)  \
            forward_list_front(forward_list)

#define fw_list_insert_after(forward_list, iter, value)  \
            forward_list_insert_after(forward_list, iter, value)

#define fw_list_push_front(forward_list, value)  \
            forward_list_push_front(forward_list, value)

#define fw_list_erase_after(forward_list, iter)  \
            forward_list_erase_after(forward_list, iter)

#define fw_list_pop_front(forward_list)  \
            forward_list_pop_front(forward_list)

#define fw_list_begin(forward_list)  \
            forward_list_begin(forward_list)

#define fw_list_cbegin(forward_list)  \
            forward_list_cbegin(forward_list)

#define fw_list_before_begin(forward_list)  \
            forward_list_before_begin(forward_list)

#define fw_list_cbefore_begin(forward_list)  \
            forward_list_cbefore_begin(forward_list)

#define fw_list_end(forward_list)  \
            forward_list_end(forward_list)

#define fw_list_cend(forward_list)  \
            forward_list_cend(forward_list)


#define fw_list_cnext(iter)  \
            forward_list_cnext(iter)

#define fw_list_next(iter)  \
            forward_list_next(iter)

#define fw_list_splice_after(forward_list_1, forward_list_2) \
    forward_list_splice_after(forward_list_1, forward_list_2)


// default type

// int
typedef fw_list_t(int) forward_list_int_t;
typedef fw_list_t(int) fw_list_int_t;

// char
typedef fw_list_t(char) forward_list_char_t;
typedef fw_list_t(char) fw_list_char_t;

// float
typedef fw_list_t(float) forward_list_float_t;
typedef fw_list_t(float) fw_list_float_t;

// double
typedef fw_list_t(double) forward_list_double_t;
typedef fw_list_t(double) fw_list_double_t;

// long long
typedef fw_list_t(long long) forward_list_long_long_t;
typedef fw_list_t(long long) fw_list_long_long_t;

// char*
typedef fw_list_t(char*) forward_list_str_t;
typedef fw_list_t(char*) fw_list_str_t;

// void*
typedef fw_list_t(void*) forward_list_ptr_t;
typedef fw_list_t(void*) fw_list_ptr_t;


#if defined(__cplusplus)
}
#endif
    
#endif
