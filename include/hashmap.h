#ifndef HASHMAP_H
#define HASHMAP_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 8
#define LOAD_FACTOR 0.8

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct HashMap {
    Node **buckets;
    int size;
    int count;
} HashMap;

void hashmap_init(HashMap **map);
void hashmap_insert(HashMap **map, const char *key, int value);
int hashmap_search(HashMap *map, const char *key);
void hashmap_delete(HashMap *map, const char *key);
void hashmap_destroy(HashMap *map);
void hashmap_resize(HashMap **map);
void hashmap_test();


#endif
// hashmap.h