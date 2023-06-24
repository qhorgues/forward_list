# forward_list
forward_list object in C

## Install

If you don't have CMake, install it first with your packet manager or via https://cmake.org/download/
In the directory run the command
```bash
cmake -S . -B build -C ./  -DCMAKE_BUILD_TYPE:STRING='Release' -DENEABLE_SANITIZER=OFF -DBUILD_TESTING=OFF
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
To initialise a list to the empty list, use the `fw_list_init` function.
```c
fw_list_t* fw_list_init(void);
```
Ex :
```c
fw_list_t* list = fw_list_init();
```

To free the list from memory, use the `fw_list_free` function.
```c
void fw_list_free(fw_list_t *forward_list);
```
Ex :
```c
fw_list_free(list);
```

To clear a list so that it remains usable, use `fw_list_clear`.
```c
void fw_list_clear(fw_list_t **forward_list);
```
Ex :
```c
fw_list_clear(&list);
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


