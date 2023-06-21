#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <forward_list.h>
#include <stdint.h>


int main(void)
{
    printf("list1\n\n");
  
    fw_list_int_t list;
    fw_list_init(&list);
    fw_list_push_front(&list, 12);
    fw_list_push_front(&list, 24);

    for (fw_list_citer_t iter = fw_list_cbegin(&list); iter != fw_list_cend(); iter = fw_list_cnext(iter))
    {
        int const* value = fw_list_cget(&list, iter); 
        printf("%d, %p\n", *value, (void const*)value);
    }

    printf("\nlist2\n\n");

    fw_list_int_t list2;
    fw_list_init(&list2);

    fw_list_push_front(&list2, 4);
    fw_list_push_front(&list2, 5);
    fw_list_insert_after(&list2, fw_list_begin(&list2), 18);
    fw_list_erase_after(&list2, forward_list_before_begin(&list2));
    fw_list_pop_front(&list2);
    fw_list_push_front(&list2, 25);
    fw_list_push_front(&list2, 52);

    for (fw_list_citer_t iter2 = fw_list_cbegin(&list2); iter2 != fw_list_cend(); iter2 = fw_list_cnext(iter2))
    {
        int const* value = fw_list_cget(&list2, iter2);
        printf("%d, %p\n", *value, (void const*)iter2);
        
    }

    printf("\n\nMerge\n\n");
    fw_list_merge(&list, &list2); 
    for (fw_list_citer_t iter = fw_list_cbegin(&list); iter != fw_list_cend(); iter = fw_list_cnext(iter))
    {
        int const* value = fw_list_cget(&list, iter); 
        printf("%d, %p\n", *value, (void const*)value);
    }
    fw_list_free(&list);

    printf("\n\nList float\n\n");
    
    fw_list_float_t list_float;
    fw_list_init(&list_float);
    fw_list_push_front(&list_float, 12.2f);
    fw_list_push_front(&list_float, 24.5f);
    for (fw_list_citer_t iter = fw_list_cbegin(&list_float); iter != fw_list_cend(); iter = fw_list_cnext(iter))
    {
        float const* value = fw_list_cget(&list_float, iter); 
        printf("%f, %p\n", *value, (void const*)value);
    }

    fw_list_free(&list_float);

    printf("\n\nList str\n\n");
    forward_list_base_t list_str;
    forward_list_init_(&list_str);

    forward_list_push_front_(&list_str, "Ceci est un test", 17ull);

    forward_list_free_(&list_str);
    
    return 0;
}
