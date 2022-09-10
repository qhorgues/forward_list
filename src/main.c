#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "forward_list/forward_list.h"

int main(void)
{
    forward_list_t(const char*) list;
    forward_list_init(&list);

    forward_list_push_front(&list, "Salut ca va");
    forward_list_push_front(&list, "Oui et toi");
    forward_list_push_front(&list, "nickel");
    forward_list_push_front(&list, "cool");

    forward_list_citer_t iter = forward_list_citer(&list);
    do
    {
        printf("%s\n", *forward_list_citer_get(&list, iter));
    } while (forward_list_next(&iter) != NULL);
    

    forward_list_free(&list);

    forward_list_t(int) list2;
    forward_list_init(&list2);

    forward_list_push_front(&list2, 4);
    forward_list_push_front(&list2, 5);
    forward_list_push_front(&list2, 25);
    forward_list_push_front(&list2, 52);

    forward_list_citer_t iter2 = forward_list_citer(&list2);
    do
    {
        printf("%d\n", *forward_list_citer_get(&list2, iter2));
    } while (forward_list_next(&iter2) != NULL);

    forward_list_free(&list2);
    return 0;
}