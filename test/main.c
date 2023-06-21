#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <forward_list.h>

int main(void)
{
    printf("\n list 1 \n\n");

    fw_list_int_t list1;
    fw_list_init(list1);
    fw_list_push_front(list1, 12);
    fw_list_push_front(list1, 24);

    for (fw_list_citer_t iter = fw_list_cbegin(list1); iter != fw_list_cend(); iter = fw_list_cnext(iter))
    {
        int const* value = fw_list_cget(list1, iter); 
        printf("%d, %p\n", *value, (void const*)value);
    }

    printf("\n list 2 \n\n");

    fw_list_int_t list2;
    fw_list_init(list2);

    fw_list_push_front(list2, 4);
    fw_list_push_front(list2, 5);
    fw_list_insert_after(list2, fw_list_begin(list2), 18);
    fw_list_erase_after(list2, forward_list_before_begin(list2));
    fw_list_pop_front(list2);
    fw_list_push_front(list2, 25);
    fw_list_push_front(list2, 52);

    for (fw_list_citer_t iter2 = fw_list_cbegin(list2); iter2 != fw_list_cend(); iter2 = fw_list_cnext(iter2))
    {
        int const* value = fw_list_cget(list2, iter2);
        printf("%d, %p\n", *value, (void const*)value);
        
    }

    printf("\n list 1 + 2 \n\n");

    fw_list_splice_after(list1, list2);
    for (fw_list_citer_t iter = fw_list_cbegin(list1); iter != fw_list_cend(); iter = fw_list_cnext(iter))
    {
        int const* value = fw_list_cget(list1, iter); 
        printf("%d, %p\n", *value, (void const*)value);
    }

    fw_list_free(list1);

    printf("\n list string \n\n");

    char str[][10] = {"un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit"};

    fw_list_str_t list_str;
    fw_list_init(list_str);

    fw_list_iter_t list_str_iter = fw_list_before_begin(list_str);

    for (int i = 0; i < 8; i++)
    {
        fw_list_insert_after(list_str, list_str_iter, str[i]);
        list_str_iter = fw_list_next(list_str_iter);
    }

    for (fw_list_citer_t iter = fw_list_cbegin(list_str); iter != fw_list_cend(); iter = fw_list_cnext(iter))
    {
        char* const* value = fw_list_cget(list_str, iter); 
        printf("%s, %p\n", *value, (void const*)value);
    }

    fw_list_free(list_str);

    return 0;
}
