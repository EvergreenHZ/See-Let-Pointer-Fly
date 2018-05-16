#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main()
{
        struct HashTable* h = hash_init(19);

        for (int i = 0; i < 100; i ++) {
                hash_insert(h, i);
        }

        hash_print(h);
        return 0;
}
