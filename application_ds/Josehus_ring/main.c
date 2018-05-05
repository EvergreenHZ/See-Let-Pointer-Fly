#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

// I don't need dummy node

/**
 * denote M as step and N as number of people
 * Make sure N >= 1, M >= 0
 */
int solu(int M, int N)
{
        if (N == 1) {
                return 1;
        } else {  // N >= 2
                NodePtr clist = clist_init(1);
                for (int i = 2; i <= N; i++) {
                        clist_push_back(clist, i);
                }
                NodePtr p = clist;
                while (clist_size(p) != 1) {
                        int step = M % clist_size(p);
                        NodePtr q;
                        while (step != 0) {
                                p = p->next;
                                step --;
                        }
                        q = p;
                        p = p->next;
                        clist_remove_current(p, q);
                }
                return p->data;
        }
}

int main(int argc, char* argv[])
{
        int M = atoi(argv[1]);
        int N = atoi(argv[2]);
        printf ("M: %d N: %d\n", M, N);
        //int M, N;
        //M = 1, N = 5;

        //int id = solu(atoi(argv[1]), atoi(argv[2]));
        int id = solu(M, N);
        printf ("the winner is number %d!\n", id);
        return 0;
}
