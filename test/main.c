#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <forward_list.h>

int int_cmp(const void* a, const void* b)
{
    const int va = *(const int*)a;
    const int vb = *(const int*)b;
    
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int main(void)
{
    fw_list_t *list1 = fw_list_init();
    {
        int x = 12;
        list1 = fw_list_push_front(list1, &x, sizeof(x));
        x = 32;
        fw_list_iter_t iter = fw_list_begin(list1);
        fw_list_insert_after(iter, &x, sizeof(x));
        x = 24;
        list1 = fw_list_push_front(list1, &x, sizeof(x));
        x = 72;
        list1 = fw_list_push_front(list1, &x, sizeof(x));
    }

    list1 = fw_list_sort(list1, &int_cmp);
    for (fw_list_iter_t i = fw_list_begin(list1); i != fw_list_end(); i = fw_list_next(i))
    {
        printf("%d\n", *(int*)fw_list_get(i));
    }
    fw_list_free(list1);
    return 0;
}
