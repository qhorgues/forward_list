#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <forward_list.h>
#include <string.h>

struct Vector3
{
    double x;
    double y;
    double z;
};

int int_cmp(const void* a, const void* b)
{
    const int va = *(const int*)a;
    const int vb = *(const int*)b;
    
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int str_cmp(const void*a, const void* b)
{
    return strcmp(a, b);
}

int main(void)
{
    fw_list_t *list1 = fw_list_init();
    {
        int x = 12;
        fw_list_push_front(&list1, &x, sizeof(x));
        x = 32;
        fw_list_iter_t iter = fw_list_begin(list1);
        fw_list_insert_after(iter, &x, sizeof(x));
        x = 24;
        fw_list_push_front(&list1, &x, sizeof(x));
        x = 72;
        fw_list_push_front(&list1, &x, sizeof(x));
    }

    fw_list_sort(&list1, &int_cmp);
    for (fw_list_iter_t i = fw_list_begin(list1); i != fw_list_end(); i = fw_list_next(i))
    {
        printf("%d\n", *(int*)fw_list_get(i));
    }
    fw_list_free(list1);

    fw_list_t *list_str = fw_list_init();
    fw_list_push_front(&list_str, "Une première chaine de caractere", 
                                            sizeof("Une première chaine de caractere"));
    fw_list_push_front(&list_str, "Et un seconde chaine de caractere", 
                                            sizeof("Et un seconde chaine de caractere"));
    fw_list_insert_after(fw_list_begin(list_str), "Une autre chaine", sizeof("Une autre chaine"));
    fw_list_erase_after(fw_list_before_begin(list_str));

    printf("%s\n-----------------------------\n", (char*)fw_list_front(list_str));

    fw_list_pop_front(&list_str);

    fw_list_insert_after(fw_list_begin(list_str), "Une quatième chaine de cararctère", 
                                                    sizeof("Une quatième chaine de cararctère"));

    fw_list_iter_t second = fw_list_next(fw_list_begin(list_str));

    fw_list_insert_after(second, "Chaine de cararctere", sizeof("Chaine de cararctere"));

    for (fw_list_citer_t i = fw_list_cbegin(list_str); i != fw_list_cend(); i = fw_list_cnext(i))
    {
        printf("%s\n", (const char*)fw_list_cget(i));
    }
    printf("-----------------------------\n");

    fw_list_sort(&list_str, &str_cmp);

    for (fw_list_citer_t i = fw_list_cbegin(list_str); i != fw_list_cend(); i = fw_list_cnext(i))
    {
        printf("%s\n", (const char*)fw_list_cget(i));
    }

    printf("-----------------------------\n");

    fw_list_erase_after(fw_list_next(fw_list_begin(list_str))); // unsafe

    for (fw_list_citer_t i = fw_list_cbegin(list_str); i != fw_list_cend(); i = fw_list_cnext(i))
    {
        printf("%s\n", (const char*)fw_list_cget(i));
    }

    fw_list_free(list_str);

    fw_list_t* list_vector = fw_list_init();

    struct Vector3 u = {23.4, 12.8, 6.3};
    fw_list_push_front(&list_vector, &u, sizeof(u));

    u = (struct Vector3){12., 4.7, 1.1};
    fw_list_push_front(&list_vector, &u, sizeof(u));

    for (fw_list_citer_t i = fw_list_begin(list_vector); i != fw_list_cend(); i = fw_list_cnext(i))
    {
        const struct Vector3 *v = fw_list_cget(i);
        printf("(%.1lf, %.1lf, %.1lf)\n", v->x, v->y, v->z);
    }
    fw_list_free(list_vector);

    return 0;
}
