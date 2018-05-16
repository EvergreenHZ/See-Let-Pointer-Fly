#pragma once 

#include <stdbool.h>

#define NOT_A_KEY -1

struct Satellite {
};

struct Node {
        int key;
        struct Node* next;
        //struct Satellite* data;
};

struct HashTable {
        struct Node* hash_list;
        //int size;
        int capacity;
};

bool is_prime(int);

struct HashTable* hash_init(int);

int hash(struct HashTable*, int key);

void hash_insert(struct HashTable*, int);

void hash_delete(struct HashTable*, int);

struct Node* hash_retrieve(struct HashTable*, int);

void hash_print(struct HashTable* h);
