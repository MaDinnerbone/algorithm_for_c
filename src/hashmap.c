#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hashmap.h>


// hash fuction
unsigned int hash_function(HashMap *map, const char *str) {
    unsigned int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = (hash * 31 + str[i]) % map->size;
    }
    return hash;
}

// initialize hashmap
void hashmap_init(HashMap **map) {
    *map = malloc(sizeof(HashMap));
    (*map)->size = INITIAL_SIZE;
    (*map)->count = 0;
    (*map)->buckets = calloc(INITIAL_SIZE, sizeof(Node *));
}

// insert element
void hashmap_insert(HashMap **map, const char *key, int value) {
    if ((*map)->count >= ((*map)->size * LOAD_FACTOR)) {
        hashmap_resize(map);
    }

    unsigned int index = hash_function(*map, key);
    Node *new_node = malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = (*map)->buckets[index];
    (*map)->buckets[index] = new_node;
    (*map)->count++;
}

// dynamic dilatation
void hashmap_resize(HashMap **map) {
    int old_size = (*map)->size;
    (*map)->size *= 2;  // increase the size of hashmap
    Node **old_buckets = (*map)->buckets;

    // craete new hash array
    (*map)->buckets = calloc((*map)->size, sizeof(Node *));
    
    // copy old element
    for (int i = 0; i < old_size; i++) {
        Node *current = old_buckets[i];
        while (current != NULL) {
            unsigned int new_index = hash_function(*map, current->key);
            Node *next = current->next;
            current->next = (*map)->buckets[new_index];
            (*map)->buckets[new_index] = current;
            current = next;
        }
    }

    free(old_buckets); // free memory
}

// destroy hashmap
void hashmap_destroy(HashMap *map) {
    for (int i = 0; i < map->size; i++) {
        Node *current = map->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}

// search element
int hashmap_search(HashMap *map, const char *key) {
    unsigned int index = hash_function(map, key);
    Node *current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1;  // not found
}

// test fuction
void hashmap_test() {
    HashMap *map = NULL;
    hashmap_init(&map);

    for (int i = 0; i < 16; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        hashmap_insert(&map, key, i);
    }

    int value = hashmap_search(map, "key10");
    printf("Value for key10: %d\n", value);

    hashmap_destroy(map);
}
