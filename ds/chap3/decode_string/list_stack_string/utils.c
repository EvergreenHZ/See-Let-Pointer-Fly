#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "utils.h"


void string_add_string(char *sa, char *sb)
{
        int length_sa = sizeof(sa) / sizeof(char);
        int length_sb = sizeof(sb) / sizeof(char);

        char *tmp = malloc(sizeof(char) * (length_sa + length_sb) * 2);
        if (!tmp) Error("malloc failed!\n");
        strcmp(tmp, sa);
        strcat(tmp, sb);
        free(sa);
        sa = tmp;
}

void string_add_char(char *s, char ch)
{
        int length_s = sizeof(s) / sizeof(char);
        int i = 0;
        while (s[i++] != '\0') {}
        if (i < length_s - 1) {
                s[i - 1] = ch;
                s[i] = '\0';
                return ;
        }

        char *tmp = malloc(sizeof(char) * (length_s) * 2);
        if (!tmp) Error("malloc failed!\n");
        s[length_s] = ch;
        s[length_s + 1] = '\0';
}

void gen_string(char *s, int n)  // generate a null string
{
        if (n == 0) n++;
        s = malloc(sizeof(char) * n);
        if (s == NULL) Error("malloc falied!\n");
        s[0] = '\0';
}
