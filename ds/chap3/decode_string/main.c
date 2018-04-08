#include <stdio.h>
#include "queue.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
/* 
 * I just suppose all inputs are valid.
 */

int isNum(char ch)
{
        return (ch >= '0' && ch <= '9');
}

void print_queue_k_times(Queue* q, int n)
{
        char s[100];
        int i = 0;
        while (!queue_empty(q)) {
                char ch = queue_dequeue(q);
                s[i++] = ch;
        }
        s[i] = '\0';

        for (int k = 0; k < n; k++) {
                printf("%s", s);
        }
}

// TODO:
void decode_string(char *s)
{
        //int count = 0;
        //int length = ARRAY_SIZE(s);
        //int n = 0;
        //Queue queue;
        //queue_init(&queue);

        //for (int i = 0; i < length; i++) {
        //        if (isNum(s[i])) {
        //                n = 0;
        //                for (; isNum(s[i]); i++) {
        //                        n = n * 10 + s[i] - '0';
        //                }
        //        }
        //        
        //        // pass '[', and collect chars, call print
        //        for (++i; i < length && s[i] != ']'; i++) {
        //                queue_enqueue(&queue, s[i]);
        //        }
        //        i++;  // pass ']'
        //        print_queue_k_times(&queue, n);
        //        n = 0;
        //        queue_destroy(&queue);
        //        queue_init(&queue);
        //}
        //printf("\n");
}

int main()
{
  decode_string("3[a]2[bc]");  // 输出 aaabcbc
  decode_string("3[a2[c]]");  // 输出 accaccacc
  decode_string("2[abc]3[cd]ef");  // 输出 abcabccdcdcdef
}
