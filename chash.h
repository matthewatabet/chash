#ifndef CHASH_H
#define CHASH_H

struct hashEntry {
    char *key;
    void *value;
    struct hashEntry *next;
};


struct hashTable {
    int size;
    struct hashEntry **table;
};

int hashKey(char * key, int size);
struct hashTable * newCHash(int size);
struct hashEntry * newHashEntry(char * key, void * value, int size);
void hashSet(struct hashTable * hash, char * key, void * value, int size);
void * hashGet(struct hashTable * hash, char * key);


#endif // CHASH_H
