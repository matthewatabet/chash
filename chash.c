#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <chash.h>

/*
 * Hash a string key. Return an integer hash value.
 * Size is the size of the hash table we're inserting into.
 */
int hashKey(char *key, int size) {
    long int hash_value = 0;
    int i;
    for (i = 0; i < strlen(key); i ++) {
        hash_value = hash_value << 8;
        hash_value += key[i];
    }

    return hash_value % size;
}


/*
 * Create a new hash table of a given size.
 */
struct hashTable * newCHash(int size) {
    
    if (size < 1) return NULL;

    // allocate memory for the hashtable.
    struct hashTable * hash = malloc(sizeof(struct hashTable));
    if (hash == NULL) return NULL;

    // allocate memory for each of the initial headers.
    hash->table = malloc(sizeof(struct hashEntry) * size);
    if (hash->table == NULL) return NULL;

    int i;
    for (i = 0; i < size; i++) {
        hash->table[i] = NULL;
    }

    hash->size = size;

    return hash;

}

/*
 * Create and return a new hash entry containing the given value.
 */
struct hashEntry * newHashEntry(char * key, void * value, int size) {

    struct hashEntry * entry = malloc(sizeof(struct hashEntry));
    if (entry == NULL) return NULL;

    entry -> key = strdup(key);
    if (entry -> key == NULL) return NULL;

    entry -> value = malloc(size);
    if (entry -> value == NULL) return NULL;

    memcpy(entry -> value, value, size);

    entry->next = NULL;

    return entry;
}


/*
 * Set a hash key to a given value
 */

void hashSet(struct hashTable * hash, char * key, void * value, int size) {
    
    int hashed_key;
    hashed_key = hashKey(key, hash->size);

    struct hashEntry * curr = NULL;
    struct hashEntry * prev = NULL;
    curr = hash -> table[hashed_key];

    // Find the insertion point for our key.
    while (curr != NULL && strcmp(key, curr -> key) > 0) {
        prev = curr;
        curr = curr -> next;
    }

    // Check if we should update the existing key's value.
    if (curr != NULL &&
        curr -> key != NULL &&
        strcmp(curr -> key, key) == 0) {
            free(curr -> value);
            curr -> value = malloc(size);
            memcpy(curr -> value, value, size);
    }
    // Create a new entry.
    else {
        struct hashEntry * newEntry = NULL;
        newEntry = newHashEntry(key, value, size);

        // Insert at head.
        if (curr == hash -> table[hashed_key]) {
            newEntry -> next = curr;
            hash -> table[hashed_key] = newEntry;
        }
        // Insert at end.
        else if (curr == NULL) {
            prev -> next = newEntry;
        }
        // Insert into middle.
        else {
            prev -> next = newEntry;
            newEntry -> next = curr;
        }
    }
}
