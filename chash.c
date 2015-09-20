#include <stdlib.h>
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
