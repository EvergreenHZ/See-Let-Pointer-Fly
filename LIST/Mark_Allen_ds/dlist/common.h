#pragma once

enum Status {
        ERR          = 0,
        OK           = 1,
};

#define SWAP(x, y, T)   \
do {                    \
        T SWAP = x;     \
        x = y;          \
        y = SWAP;       \
}while(0)

void Error(char *msg);

void* Malloc(size_t);

int random_int();
