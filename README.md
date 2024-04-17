# forward_list
forward_list object in C

## Install

If you don't have CMake, install it first with your packet manager or via https://cmake.org/download/
In the directory run the command
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING='Release' -DENEABLE_SANITIZER=OFF -DBUILD_TESTING=OFF
```
and
```bash
cd build
```
Then, depending on your compilation system, compile the program with make, for example
```bash
make -k all
```
You can also request immediate installation with 
```bash
make install
```

## Constructor/Destructor
### Constructor
To initialise a list to the empty list, use the `fw_list_init` function.
```c
fw_list_t* fw_list_init(void);
```
Ex :
```c
fw_list_t* list = fw_list_init();
```

### Destructor
To free the list from memory, use the `fw_list_free` function.
```c
void fw_list_free(fw_list_t *forward_list);
```
Ex :
```c
fw_list_free(list);
```

## Element access
To access the value contained in the first element of the list we use `fw_list_front`.
```c
void* fw_list_front(fw_list_t *forward_list);
```
Ex :
```c
int* value = (int*)fw_list_front(list);
```
In the case of a non-empty list of integers

## Iterator

There are two types of iterator the constant iterator, which cannot modify the list and can only read `fw_list_citer_t`,
and its non-constant counterpart `fw_list_iter_t`.
To create an iterator we use the `fw_list_begin` function which returns an iterator on the first element,
we can also use `fw_list_before_begin` which returns an iterator on the element preceding the first element.
You can use the `fw_list_next` function to browse the list. which returns the iterator following the current iterator.
We use the `fw_list_get` function to retrieve the data referenced by an iterator.
The `fw_list_next` function returns an iterator on the element after the last element.
There is a version of this function for constant iterators
Ex :
```c
for (fw_list_citer_t i = fw_list_cbegin(list); i != fw_list_cend(); i = fw_list_cnext(i))
{
    printf("%d ", *(const int*)fw_list_cget(i));
}
```
To modify data in the list, you can either use the pointer returned by `fw_list_get` or rewrite all the data with `fw_list_set`.

## Capacity

To test whether the list is empty, use the `fw_list_empty` function.
Ex :
```c
if (fw_list_empty(list))
{
    printf("The list is empty");
}
```

## Modifier
### Clear

To clear a list so that it remains usable, use `fw_list_clear`.
```c
void fw_list_clear(fw_list_t **forward_list);
```
Ex :
```c
fw_list_clear(&list);
```

### Insertion
To insert a value after a referenced value that will be copied to the list, use `fw_list_insert_after`.
```c
fw_list_iter_t fw_list_insert_after(fw_list_iter_t iter, void const *value, size_t size_value);
```
Ex :
```c
int array[] = {5, 3, 4, 6, 7, 9};
fw_list_t* list = fw_list_init();
fw_list_iter_t it_list = fw_list_before_begin(list);
for (size_t i = 0; i < sizeof(array)/sizeof(*array); i++)
{
    fw_list_insert_after(it_list, &(array[i]), sizeof(int));
    it_list = fw_list_next(it_list);
}
```
Create the following list
`9 -> 7 -> 6 -> 4 -> 3 -> 5`

To insert a value at the beginning, use `fw_list_push_front`
```c
int fw_list_push_front(fw_list_t **forward_list, void const *value, size_t size_value);
```

### Remove
To delete a value after a pointed value, use `fw_list_erase_after`.
```c
int fw_list_erase_after(fw_list_iter_t iter);
```
Example with the previous case :
```c
fw_list_erase_after(fw_list_begin(list));
```
`list` will then be
`9 -> 6 -> 4 -> 3 -> 5`

To remove a value at the beginning, use `fw_list_pop_front`
```c
void fw_list_pop_front(fw_list_t **forward_list);
```

## Operations
To concatenate two lists, we use `fw_list_splice_after`
```c
void fw_list_splice_after(fw_list_t **forward_list1, fw_list_t **forward_list2);
```

To concatenate two sorted lists into one sorted list, we use `fw_list_merge`
```c
void fw_list_merge(fw_list_t **forward_list1, fw_list_t **forward_list2, int (*cmp)(const void*, const void*));
```

To sort a list, we use `fw_list_sort`
```c
void fw_list_sort(fw_list_t **forward_list, int (*cmp)(const void*, const void*));
```