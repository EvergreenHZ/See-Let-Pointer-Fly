#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stack.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int isOp(const char* op)
{
        return (!strcmp(op, "+") ||
                !strcmp(op, "-") ||
                !strcmp(op, "*") ||
                !strcmp(op, "/"));
}

long isNum(const char *num)
{
        char *endptr;
        long value = strtol(num, &endptr, 10);
        if (endptr == num || *endptr != '\0' || errno == ERANGE) {
                return 0;
        }
        return value;
}


// TODO:
int rpn(char **tokens, int len) {
        int err = 0;  //?
        Stack stack;
        stack_init(&stack);

        int value = 0;
        for (int i = 0; i < len && !err; i++) {
                if ((value = isNum(tokens[i]))) {  // is number
                        stack_push(&stack, value);
                } else if (isOp(tokens[i])) {  // is operator
                        if (stack_size(&stack) < 2) {
                                return 0;  // error
                        }
                        int lhs, rhs;
                        rhs = stack_pop(&stack);
                        lhs = stack_pop(&stack);

                        int evlValue;
                        if (!strcmp(tokens[i], "+")) {  // operator is "+"
                                evlValue = lhs + rhs;
                        } else if (!strcmp(tokens[i], "-")) {
                                evlValue = lhs - rhs;
                        } else if (!strcmp(tokens[i], "*")) {
                                evlValue = lhs * rhs;
                        } else if (!strcmp(tokens[i], "/")) {
                                evlValue = lhs / rhs;
                        }

                        stack_push(&stack, evlValue);
                } else {
                        return 0;  // error
                }
        }

        if (stack_size(&stack) == 1) {
                return stack_pop(&stack);  // auto release
        }

        return 0;  // error
}

int main() {
        char *s1[] = {"2", "1", "+", "3", "*"};
        char *s2[] = {"4", "13", "5", "/", "+"};

        printf("%d\n", rpn(s1, ARRAY_SIZE(s1))); // 9
        printf("%d\n", rpn(s2, ARRAY_SIZE(s2))); // 6
}
