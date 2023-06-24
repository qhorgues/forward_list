#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#if defined(__cplusplus)
extern "C"
{
#endif

#define FORWARD_LIST_VERSION "2.0.0"

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Structure representing the chained list
 * 
 */
struct fw_list_t;
typedef struct fw_list_t fw_list_t;

/**
 * @brief Iterator for browsing the list
 */
typedef fw_list_t *fw_list_iter_t;

/**
 * @brief Iterator to browse the list without modifying it
 */
typedef fw_list_t const *fw_list_citer_t;

/**
 * @brief Initialise the list to the empty list
 * 
 * @return fw_list_t* Returns a pointer to the empty list
 */
fw_list_t* fw_list_init(void);

/**
 * @brief Free the list in memory
 * @warning The list is considered invalid after the call to free
 * and must therefore be reset before it can be used again.
 * 
 * @param[in] forward_list A pointer to the list to free
 */
void fw_list_free(fw_list_t *forward_list);

/**
 * @brief Returns a pointer to the data in the first link
 * @warning Undefined behaviour if the list is empty
 * @param[in] forward_list The chained list
 * @return void* Pointer to data
 */
void* fw_list_front(fw_list_t *forward_list);

/**
 * @brief Returns an iterator on constant data pointing to
 * the first element of the list or NULL if the list is empty.
 * 
 * @param[in] forward_list The chained list
 * @return fw_list_citer_t iterator on the first élément
 */
fw_list_citer_t fw_list_cbegin(fw_list_t *forward_list);

/**
 * @brief Returns an iterator on data pointing to
 * the first element of the list or NULL if the list is empty.
 * 
 * @param[in] forward_list The chained list
 * @return fw_list_iter_t iterator on the first élément
 */
fw_list_iter_t fw_list_begin(fw_list_t *forward_list);

/**
 * @brief Return an constant iterator on the element after the last element
 * @warning The returned pointer points to invalid data Any 
 * operation to retrieve the data causes undefined behaviour
 * @return fw_list_citer_t constant iterator after the last élément
 */
fw_list_citer_t fw_list_cend(void);

/**
 * @brief Return an iterator on the element after the last element
 * @warning The returned pointer points to invalid data Any 
 * operation to retrieve the data causes undefined behaviour
 * @return fw_list_citer_t iterator after the last élément
 */
fw_list_iter_t fw_list_end(void);

/**
 * @brief Recover a constant pointer to the data of a link referenced by
 * the constant iterator in parameter
 * @warning The function does not check whether the iterator is valid 
 * or whether it does not refer to any links, and can undefined behavior.
 * @param[in] iter The iterator referencing the link to be read
 * @return void const* Constant pointer to data
 */
void const* fw_list_cget(fw_list_citer_t iter);

/**
 * @brief Recover a pointer to the data of a link referenced by
 * the constant iterator in parameter
 * @warning The function does not check whether the iterator is valid 
 * or whether it does not refer to any links, and can undefined behavior.
 * @param[in] iter The iterator referencing the link to be read
 * @return void* pointer to data
 */
void* fw_list_get(fw_list_iter_t iter);

/**
 * @brief Rewrites data stored in a link, the data must be
 * the same size or smaller than the previous one.
 * @warning Writing any data larger than the start size
 * defined when the node was created results in undefined behaviour.
 * @param[in] iter The iterator referring to the link to be modified
 * @param[in] value A pointer to the data to be written
 * @param[in] size_value The number of bytes taken up by this data
 */
void fw_list_set(fw_list_iter_t iter, void const *value, size_t size_value);

/**
 * @brief Check if the list is empty
 * 
 * @param[in] forward_list The test list
 * @return true If the list is empty
 * @return false If the list is not empty
 */
bool fw_list_empty(fw_list_t const *forward_list);

/**
 * @brief Free all the links in the memory
 * and return the list to the empty state
 * 
 * @param forward_list The list to be emptied
 */
void fw_list_clear(fw_list_t **forward_list);

/**
 * @brief Inserts a new link after the one referenced by the iterator
 * @exception malloc exception
 * @param[in] iter The iterator refers to the link preceding
 * the new link to be inserted.
 * @param[in] value A pointer to the data to be written
 * @param[in] size_value The number of bytes taken up by this data
 * @return fw_list_iter_t The iterator on the new link 
 * or NULL if the operation fails.
 */
fw_list_iter_t fw_list_insert_after(fw_list_iter_t iter, void const *value, size_t size_value);

/**
 * @brief Deletes the link following the referenced link
 * @exception EDOM Outside the domain
 * @param[in] iter The link preceding the link to be deleted
 * @return int 0 if the operation is successful -1 if the next link does not exist
 */
int fw_list_erase_after(fw_list_iter_t iter);

/**
 * @brief Inserts a new link at the top of the list
 * @exception malloc exception
 * @param[in] forward_list A pointer to the pointer to the list
 * @param[in] value A pointer to the data to be written
 * @param[in] size_value The number of bytes taken up by this data
 * @return fw_list_iter_t 0 if the operation is successful
 * or -1 if the operation fails
 */
int fw_list_push_front(fw_list_t **forward_list, void const *value, size_t size_value);

/**
 * @brief Deletes the element at the top of the list 
 * @warning Does not check whether the list is empty,
 * so causes indeterminate behaviour in the event of an empty or invalid list
 * 
 * @param[in] forward_list A pointer to the pointer to the list
 */
void fw_list_pop_front(fw_list_t **forward_list);

/**
 * @brief returns a constant iterator on the next link
 * 
 * @param[in] iter the constant iterator
 * @return fw_list_citer_t constant iterator on the next link
 */
fw_list_citer_t fw_list_cnext(fw_list_citer_t iter);

/**
 * @brief returns a iterator on the next link
 * 
 * @param[in] iter the iterator
 * @return fw_list_iter_t iterator on the next link
 */
fw_list_iter_t fw_list_next(fw_list_iter_t iter);

/**
 * @brief Adds list 2 to the end of list 1
 * 
 * @param[in, out] forward_list1 The first list
 * @param[in, out] forward_list2 The second list, which is added to 
 * the first list and emptied
 */
void fw_list_splice_after(fw_list_t **forward_list1, fw_list_t **forward_list2);

/**
 * @brief Merges two sorted lists and returns a sorted list
 * 
 * @param[in, out] forward_list1 The first sorted list, resultant list
 * @param[in, out] forward_list2 The second sorted list, reset to the empty list
 * @param[in] cmp comparison function which returns ​a negative integer value
 * if the first argument is less than the second, a positive integer value 
 * if the first argument is greater than the second 
 * and zero if the arguments are equivalent.
 * The signature of the comparison function should be equivalent to the following:
 * @code
 * int cmp(const void *a, const void *b);
 * @endcode
 * The function must not modify the objects passed to it and must return consistent results when called for the same objects, regardless of their positions in the array.
 */
void fw_list_merge(fw_list_t **forward_list1, fw_list_t **forward_list2, int (*cmp)(const void*, const void*));

/**
 * @brief Sorts the list passed in parameter according to the comparison function
 * 
 * @param[in, out] forward_list The list that will be sorted
 * @param[in] cmp comparison function which returns ​a negative integer value if the first argument is less than the second, a positive integer value if the first argument is greater than the second and zero if the arguments are equivalent.
 * The signature of the comparison function should be equivalent to the following:
 * @code
 * int cmp(const void *a, const void *b);
 * @endcode
 * The function must not modify the objects passed to it and must return consistent results when called for the same objects, regardless of their positions in the array.
 */
void fw_list_sort(fw_list_t **forward_list, int (*cmp)(const void*, const void*));

/**
 * @brief Returns an constant iterator on the element
 * preceding the first element of the list
 * @warning The returned pointer points to invalid data Any 
 * operation to retrieve the data causes undefined behaviour
 */
#define fw_cbefore_begin(forward_list) \
    (fw_list_citer_t)(&forward_list)

/**
 * @brief Returns an iterator on the element
 * preceding the first element of the list
 * @warning The returned pointer points to invalid data Any 
 * operation to retrieve the data causes undefined behaviour
 */
#define fw_list_before_begin(forward_list) \
    (fw_list_iter_t)(&forward_list)

#if defined(__cplusplus)
}
#endif
    
#endif
