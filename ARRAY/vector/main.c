#include "list.h"
#include <stdio.h>

int main()
{
        ListPtr list = list_create();
        for (int i = 0; i < 10; i++) {
                list_push_back(list, i);
        }
        list_print(list);

        for (int i = 0; i < 10; i++) {
                list_pop_front(list);
                list_print(list);
        }

        return 0;
}
