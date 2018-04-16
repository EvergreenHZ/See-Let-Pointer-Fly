#include <stdio.h>
#include "utils.h"
#include "stack_string.h"
#include "stack.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
/* 
 * I just suppose all inputs are valid.
 */

int isNum(char ch)
{
        return (ch >= '0' && ch <= '9');
}


// TODO:
void decode_string(char *s)
{
        int array_size = 0;
        for (; ; array_size++) {
                if (s[array_size] == '\0') {
                        //array_size--;
                        break;
                }
        }
        //printf("size of array: %4d\n", array_size);
        Stack sstack;
        StackInt _intstack;

        stack_init(&sstack);
        stack_int_init(&_intstack, 100);

        char *result;
        char *tmp;

        result = gen_string(0);
        tmp = gen_string(0);
        int n = 0;
        for (int i = 0; i <  array_size; i++) {
                if (isNum(s[i])) {
                        n = 0;
                        for (; isNum(s[i]); i++) {
                                n = n * 10 + s[i] - '0';
                        }
                        //printf("current n: %d\n", n);
                }
                if (s[i] == '[') {
                        tmp = gen_string(0);
                        stack_push(&sstack, tmp);
                        stack_int_push(&_intstack, n);
                } else if (s[i] == ']') {
                        n = stack_int_peek(&_intstack);
                        tmp = gen_string(0);

                        for (; n > 0; n--) {  // cat for n times to tmp
                                tmp = string_add_string(tmp, *stack_peek(&sstack));
                        }
                        stack_pop(&sstack);
                        stack_int_pop(&_intstack);

                        if (!stack_empty(&sstack)) {
                                *stack_peek(&sstack) = string_add_string(*stack_peek(&sstack), tmp);
                        } else {
                                result = string_add_string(result, tmp);
                        }
                } else {
                        if (!stack_empty(&sstack)) {  // collect chars
                                *stack_peek(&sstack) = string_add_char(*stack_peek(&sstack), s[i]);
                        } else {
                                result = string_add_char(result, s[i]);
                        }
                }
        }
        printf("%s\n", result);
}

int main()
{
        decode_string("3[a]2[bc]");  // 输出 aaabcbc
        decode_string("3[a2[c]]");  // 输出 accaccacc
        decode_string("2[abc]3[cd]ef");  // 输出 abcabccdcdcdef
}
