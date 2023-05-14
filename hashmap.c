#include "hashmap.h"



entry_t *init_entry(char *k, char *v)
{
    entry_t *e = (entry_t*)calloc(1, sizeof(entry_t));
    strncpy(e->key, k, KEY_SIZE);
    strncpy(e->value, v, VAL_SIZE);

    return e;
}


hashmap_t *init_hashmap()
{
    hashmap_t *h = (hashmap_t*)calloc(1, sizeof(hashmap_t));
    h->size = 0;
    h->capacity = INITIAL_CAPACITY;
    h->table = (entry_t**)calloc(h->capacity, sizeof(entry_t*));
    for (int i = 0; i < h->capacity; i++)
        h->table[i] = NULL;
    return h;
}


void delete_hashmap(hashmap_t **hp)
{
    if ((*hp)->size != 0)
    {
        for (int i = 0; i < (*hp)->capacity; i++)
            if ((*hp)->table[i] != NULL)
                delete_entry(&((*hp)->table[i]));
    }
    free((*hp)->table);
    free(*hp);
}


void delete_entry(entry_t **ep)
{
    if ((*ep) == NULL)
        return;
    free(*ep);
}


int hash(char key[])
{
    int h = 0;
    for (int i = 0; i < KEY_SIZE && key[i] != 0; i++)
        h += key[i] * (int)pow(31, strlen(key) -i-1);

    return (h < 0) ? -1*h : h;
}


const char *put(hashmap_t *h, char key[], char val[])
{
    int index = hash(key) % h->capacity;
    if (h->table[index] == NULL)
    {
        h->table[index] = init_entry(key, val);
        h->size++;
        return (const char*) val;
    }
    else if (!strncmp(key, h->table[index]->key, KEY_SIZE))
    {
        strncpy(h->table[index]->value, val, VAL_SIZE);
        return (const char *)val;
    }
    else
    {
        float load_factor = (float)(h->size) / h->capacity;
        if (load_factor > LOAD_FACTOR)
        {
            reallocate(h);
            return put(h, key, val);
        }
        else 
        {
            for (int i = (index+1)%h->capacity; i != index; 
                    i = (i+1)%h->capacity)
                if (h->table[i] == NULL)
                {
                    h->table[i] = init_entry(key, val);
                    h->size++;
                    return (const char *) val;
                }
        }
    }
    return NULL;
}


void reallocate(hashmap_t *h) 
{
    entry_t **oldTable = h->table;
    int newCapacity = h->capacity * 2 + 1;
    h->table = (entry_t**)calloc(newCapacity, sizeof(entry_t*));
    for (int i = 0; i < newCapacity; i++)
        h->table[i] = NULL;

    int oldCapacity = h->capacity;
    h->capacity = newCapacity;
    rehash(h, oldTable, oldCapacity);
    free(oldTable);
}


void rehash(hashmap_t *h, entry_t **t, int c)
{
    for (int i = 0; i < c; i++)
        if (t[i] != NULL)
            put(h, t[i]->key, t[i]->value);
}



char *get(hashmap_t *h, char key[])
{
    int index = hash(key)%h->capacity;
    if (h->table[index] == NULL)
        return NULL;
    else if (strncmp(key, h->table[index]->key, KEY_SIZE))
    {
        for (int i = (index+1)%h->capacity; i != index; 
            i = (i+1)%h->capacity)
            if (!strncmp(h->table[i]->key, key, KEY_SIZE))
                return h->table[i]->value;
        return NULL;
    }
    return h->table[index]->value;
}



void printMap(hashmap_t *h)
{
    if (!h->size)
    {
        printf("HashMap is empty\n");
        return;
    }
    for (int i = 0; i < h->capacity; i++)
        if (h->table[i] != NULL)
            printf("Key: %s, \tValue: %s\n", h->table[i]->key,
                                             h->table[i]->value);
}
