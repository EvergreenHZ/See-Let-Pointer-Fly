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
