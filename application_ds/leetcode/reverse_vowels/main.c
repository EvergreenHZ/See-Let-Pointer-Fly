#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

int is_vower(char ch)
{
        if (ch == 'a' || ch == 'A' ||
            ch == 'e' || ch == 'E' ||
            ch == 'i' || ch == 'I' ||
            ch == 'o' || ch == 'O' ||
            ch == 'u' || ch == 'U') {
                return 1;
        } else {
                return 0;
        }
}

void reverse_vower(char* s)
{
        printf("%s\n", s);
        struct Vector index;
        vector_init(&index, 100);

        char tmp[100];
        int n = 0;
        while ( (tmp[n] = *s++) != '\0') {
                n++;
        }
        // 
        char *p = tmp;
        printf("%s\n", tmp);
        //int i = 1;
        while (*p) {
                if (is_vower(*p)) {
                        //printf("%4d ", i);
                        vector_push_back(&index, p);
                }
                p = p + 1;
                //i++;
        }

        int size = index.size;
        for (int i = 0; i < size / 2; i++) {
                char ch = *index.buffer[i];
                *index.buffer[i] = *index.buffer[size - i - 1];
                *index.buffer[size - i - 1] = ch;
        }

        printf("%s\n", tmp);
}
int main() {
        reverse_vower("leetcode");
  /* test_list(); */
  /* test_merge_two_lists(); */

  return 0;
}
