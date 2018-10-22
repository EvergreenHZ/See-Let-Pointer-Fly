#include <stdio.h>
#include "xstring.h"
#include "string.h"
#include "common.h"

void test_matcher() {
        xstring s;
        string_init(&s, 15);
        strcpy(&(s.T[1]), "abcababcababaac");
        printf("%s\n", (s.T + 1));
        printf("%d\n", s.T[0]);

        xstring p;
        string_init(&p, 10);
        //strcpy(&(p.T[1]), "ABBCD");
        strcpy(&(p.T[1]), "abcababaac");
        printf("%s\n", (p.T + 1));
        printf("%d\n", p.T[0]);

        kmp_matcher(&s, &p);
}

int main()
{
        test_matcher();

        return 0;
}
