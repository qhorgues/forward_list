#include <stdio.h>
#include <errno.h>
#include <forward_list.h>

int main(void)
{
    fw_list_str_t list;
    fw_list_init(&list);
    fw_list_index_insert(&list, 0, "Salut ca va");
    fw_list_push_front(&list, "Oui et toi");
    fw_list_index_insert(&list, 2, "Nickel");
    fw_list_index_insert(&list, fw_list_size(&list), "cool");

    fw_list_citer_t iter = fw_list_citer(&list);
    do
    {
        printf("%s\n", *fw_list_citer_get(&list, iter));
    } while (fw_list_citer_next(&iter) != NULL);
    

    fw_list_free(&list);

    fw_list_int_t list2;
    fw_list_init(&list2);

    fw_list_push_front(&list2, 4);
    fw_list_push_front(&list2, 5);
    fw_list_push_front(&list2, 25);
    fw_list_push_front(&list2, 52);
    fw_list_set(&list2, 2ull, 64);

    fw_list_iter_t iter2 = fw_list_iter(&list2);
    do
    {
        int const* value = fw_list_iter_get(&list2, iter2);
        if (value != NULL)
            printf("%d, %p\n", *value, (void*)iter);
        else
        {
            perror("fw_list_iter_get");
        }
    } while (fw_list_iter_next(&iter2) != NULL);

    fw_list_free(&list2);
    return 0;
}