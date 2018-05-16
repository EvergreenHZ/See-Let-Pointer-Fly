#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "hash.h"

bool is_prime(int x)
{
        int y = x / 2 + 1;
        for (int i = 2; i < y; i++) {
                if (x % i == 0) {
                        return false;
                }
        }
        return true;
}

static int find_good_prime_number(int x)
{
        for (int i = x; ; i++) {
                if (is_prime(i)) {
                        return i;
                }
        }
}

struct HashTable* hash_init(int cap)
{
        struct HashTable* h = Malloc(sizeof(struct HashTable));
        h->capacity = find_good_prime_number(cap);
        //h->size = 0;
        h->hash_list = Malloc(sizeof(struct HashTable) * h->capacity);
        for (int i = 0; i < h->capacity; i++) {
                h->hash_list[i].key = NOT_A_KEY;
                h->hash_list[i].next = NULL;
        }

        return h;
}

int hash(struct HashTable* h, int key)
{
        return key % h->capacity;
}

void hash_insert(struct HashTable* h, int key)
{
        struct Node *node = Malloc(sizeof(struct Node));
        node->key = key;
        node->next = NULL;

        int position = hash(h, key);

        if (h->hash_list[position].key == NOT_A_KEY) {
                h->hash_list[position].key = key;
        } else {
                node->next = h->hash_list[position].next;
                h->hash_list[position].next = node;
        }
        //h->size ++;
}

void hash_delete(struct HashTable* h, int key)
{
        int position = hash(h, key);

        if (h->hash_list[position].key == key) {  // head
                struct Node *p = &h->hash_list[position];
                if (p->next == NULL) {
                        p->key = NOT_A_KEY;
                } else {
                        struct Node *q = p->next;
                        while (q->next) {
                                p = p->next;
                                q = q->next;
                        }
                        h->hash_list[position].key = q->key;
                        p->next = NULL;
                        free(q);
                }
        } else {  // in the list
                struct Node *p = &h->hash_list[position];
                struct Node *q = p->next;

                while (q) {
                        if (q->key == key) {
                                break;
                        }
                        p = p->next;
                        q = q->next;
                }
                if (q == NULL) {
                        printf("key not found!\n");
                        return ;
                }
                p->next = q->next;
                free(q);
        }
}

struct Node* hash_retrieve(struct HashTable* h, int key)
{
        int position = hash(h, key);
        struct Node *p = &h->hash_list[position];
        while (p) {
                if (p->key == key) {
                        return p;
                } else {
                        p = p->next;
                }
        }
        return NULL;
}

void hash_print(struct HashTable* h)
{
        for (int i = 0; i < h->capacity; i++) {
                if (h->hash_list[i].key == NOT_A_KEY) {
                        continue;
                } else {
                        struct Node* p = &(h->hash_list[i]);
                        printf("%d: ", i);
                        while (p) {
                                printf("%d ", p->key);
                                p = p->next;
                        }
                        printf("\n");
                }
        }
}
