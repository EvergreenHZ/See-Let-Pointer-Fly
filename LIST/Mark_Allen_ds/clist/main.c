#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

int main()
{
        struct Node clist;
        clist_init(&clist);
        for (int i = 0; i < 10; i++) {
                clist_insert_after(&clist, NULL, i);
        }
        clist_print(&clist);

        for (int i = 0; i < 10; i++) {
                clist_remove_after(&clist, NULL);
                clist_print(&clist);
        }

        return 0;
}
