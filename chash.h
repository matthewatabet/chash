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


#endif // CHASH_H
