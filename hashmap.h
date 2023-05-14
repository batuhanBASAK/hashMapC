#ifndef HASH_MAP
#define HASH_MAP



#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define KEY_SIZE 32
#define VAL_SIZE 64
#define INITIAL_CAPACITY 101
#define LOAD_FACTOR 0.75f


typedef struct Entry{
    char key[KEY_SIZE];
    char value[VAL_SIZE];
}entry_t;


typedef struct {
    int size;
    int capacity;
    entry_t **table;
}hashmap_t;


entry_t *init_entry(char *k, char *v);
hashmap_t *init_hashmap();

void delete_hashmap(hashmap_t **hp);

void delete_entry(entry_t **ep);

int hash(char key[]);

const char *put(hashmap_t *h, char key[], char val[]);
        
void reallocate(hashmap_t *h);

void rehash(hashmap_t *h, entry_t **t, int c);

char *get(hashmap_t *h, char key[]);
void printMap(hashmap_t *h);







#endif
