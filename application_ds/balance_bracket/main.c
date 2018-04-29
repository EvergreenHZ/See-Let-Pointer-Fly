#include <stdio.h>
#include "stack.h"

#define IS_PARENTHESIS(c) ((c) == '(' || (c) == ')')
#define IS_SQUARE_BRACKET(c) ((c) == '[' || (c) == ']')
#define IS_CURLY_BRACE(c) ((c) == '{' || (c) == '}')
#define IS_BRACKETS(c) (IS_PARENTHESIS(c) || \
                        IS_SQUARE_BRACKET(c) || \
                        IS_CURLY_BRACE(c))
#define IS_OPEN(c) ((c) == '(' || \
                    (c) == '[' || \
                    (c) == '{')
#define IS_CLOSE(c) ((c) == ')' || \
                     (c) == ']' || \
                     (c) == '}')
char get_complement(char c)
{
        switch (c) {
                case '(':
                        return ')';
                case ')':
                        return '(';
                case '[':
                        return ']';
                case ']':
                        return '[';
                case '{':
                        return '}';
                case '}':
                        return '{';
        }
        return '\0';
}

int get_length(char *s)
{
        int n = 0;
        while (s[n] != '\0') {
                n++;
        }
        return n;
}

int is_balanced(char *s)
{
        Stack stack;
        stack_init(&stack);
        int length = get_length(s);

        for (int i = 0; i < length; i++) {
                char c = s[i];
                if (IS_BRACKETS(c)) {
                        if (IS_OPEN(c)) {
                                stack_push(&stack, c);
                        } else {  // close bracket
                                if (stack_size(&stack) == 0) {  // empty stack
                                        return 0;
                                }
                                if (stack_peek(&stack) == get_complement(c)) {
                                        stack_pop(&stack);
                                } else {
                                        return 0;
                                }
                        }
                } 
        }
        if (stack_size(&stack) != 0) {
                return 0;
        }
        return 1;
}

int main(int argc, char *argv[])
{
        char s[] = "{hello [ 1 + 2] (world!})";
        if (is_balanced(s)) {
                printf("s is balanced\n");
        } else {
                printf("s is not balanced\n");
        }
        if (is_balanced(argv[1])) {
                printf("s is balanced\n");
        } else {
                printf("s is not balanced\n");
        }


        //Stack stack;  // create a stack, dummy head; but I don't care

        //stack_init(&stack);

        //for (int i = 0; i < 10; i ++) {
        //        stack_push(&stack, i);
        //}

        //printf("size: %4d \n", stack_size(&stack));
        //list_print(&stack);
        //printf("size: %4d \n", stack_size(&stack));

        ////for (int i = 0; i < stack_size(&stack); i++) {
        //for (int i = 0; i < 10; i++) {
        //        printf("%4d ", stack_pop(&stack));
        //}
        //printf("\n");
        //printf("size: %4d \n", stack_size(&stack));
        //list_print(&stack);

        //stack_pop(&stack);
        //stack_destroy(&stack);

        return 0;
}
