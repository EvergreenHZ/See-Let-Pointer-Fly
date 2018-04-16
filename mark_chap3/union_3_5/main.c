/*
 * this code works fine!
 */
#include <stdio.h>
#include "list.h"

void list_copy(List src, List dst)
{
        NodePtr p = src->next;
        while (p) {
                list_push_back(dst, p->data);
                p = p->next;
        }
        return ;
}

void list_cat(List dst, List src)
{
        NodePtr p = src->next;
        while (p) {
                list_push_back(dst, p->data);
                p = p->next;
        }

        return ;
}

// TODO
void list_intersection_sorted(List src1, List src2, List dst)
{
        if (list_size(src1) == 0) {
                list_copy(src2, dst);
        } else if (list_size(src2) == 0) {
                list_copy(src1, dst);
        } else {  // both srcs are not empty
                NodePtr p, q;
                p = src1->next;
                q = src2->next;

                while (p && q) {
                        if (p->data > q->data) {
                                list_push_back(dst, q->data);
                                q = q->next;
                        } else if (p->data < q->data) {
                                list_push_back(dst, p->data);
                                p = p->next;
                        } else {  // equal
                                list_push_back(dst, p->data);
                                NodePtr tmp = p;
                                // skip all the same data
                                while (p->next && (tmp->data == (p->next->data))) {
                                        p = p->next;
                                }
                                while (q->next && (tmp->data == (q->next->data))) {
                                        q = q->next;
                                }

                                if (p->data == tmp->data) {
                                        p = p->next;
                                }
                                if (q->data == tmp->data) {
                                        q = q->next;
                                }
                        }
                }
                
                if (p) {
                        while (p->data == list_last_node(dst)->data) {
                                p = p->next;
                        }
                        while (p) {
                                list_push_back(dst, p->data);
                                p = p->next;
                        }
                        return ;
                }

                if (q) {
                        while (q->data == list_last_node(dst)->data) {
                                q = q->next;
                        }
                        while (q) {
                                list_push_back(dst, q->data);
                                q = q->next;
                        }
                        return ;
                }
        }
}


int main()
{
        struct Node src1, src2, dst;  // a dummy node
        list_init(&src1);
        list_init(&src2);
        list_init(&dst);


        for (int i = 0; i < 10; i++) {
                list_push_back(&src1, 2 * i);
                list_push_back(&src2, 2 * i + 1);
        }

        for (int i = 10; i < 20; i++) {
                list_push_back(&src1, 2 * i + 1);
                list_push_back(&src2, 2 * i + 1);
        }
        //list_print(&src1);
        //list_print(&src2);
        //list_print(&dst);

        list_intersection_sorted(&src1, &src2, &dst);

        list_print(&src1);
        list_print(&src2);
        list_print(&dst);

        struct Node src3, src4;
        list_init(&src3);
        list_init(&src4);

        list_intersection_sorted(&src3, &dst, &src4);
        list_print(&src4);

        list_destroy(&src1);
        list_destroy(&src2);
        list_destroy(&dst);
        list_destroy(&src3);
        list_destroy(&src4);

        return 0;
}
