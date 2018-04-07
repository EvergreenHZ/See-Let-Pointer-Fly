#include <stdio.h>

char  phone[10][4]={ {' ',  '\0', '\0', '\0' }, //0
        {'\0', '\0', '\0', '\0' }, //1
        {'a',  'b',  'c',  '\0' }, //2
        {'d',  'e',  'f',  '\0' }, //3
        {'g',  'h',  'i',  '\0' }, //4
        {'j',  'k',  'l',  '\0' }, //5
        {'m',  'n',  'o',  '\0' }, //6
        {'p',  'q',  'r',  's'  }, //7
        {'t',  'u',  'v',  '\0' }, //8
        {'w',  'x',  'y',  'z'  }  //9
};
// TODO:
void print_letters(char * digits)
{
}

int main()
{
        print_letters("23"); // 打印: ad, ae, af, bd, be, bf, cd, ce, cf.
        printf("\n");
}
