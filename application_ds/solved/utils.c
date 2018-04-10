#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "utils.h"


char* string_add_string(char *sa, char *sb)
{
         strcat(sa, sb);
         return sa;
}

char* string_add_char(char *s, char ch)
{
        char *tmp = malloc(sizeof(char) * 2);
        if (!tmp) Error("malloc failed!\n");
        tmp[0] = ch;
        tmp[1] = '\0';
        strcat(s, tmp);
        free(tmp);
        return s;
}

char* gen_string(int n)  // generate a null string
{
        char *s = NULL;
        if (n == 0) n++;
        s = malloc(sizeof(char) * n);
        if (s == NULL) Error("malloc falied!\n");
        s[0] = '\0';
        return s;
}


void Error(const char *msg)
{
        printf("%s\n", msg);
        exit(-1);
}
