#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <chash.h>

static int tests = 0, fails = 0;
#define test(_s) { printf("#%02d %s ", ++tests, _s); }
#define print_pass() printf("\033[0;32mPASSED\033[0;0m\n")
#define print_fail() printf("\033[0;31mFAILED\033[0;0m\n")
#define test_cond(_c) {if(_c) print_pass(); else {print_fail(); fails++;}}
#define expect(_s, _c) { test(_s); test_cond(_c); }

void testNewChash() { 
    struct hashTable * hash = newCHash(4);
    expect("Hash table size is 4.", hash->size == 4);
    int i;
    for (i =0; i < 4; i++) {
        expect("Hash entry is NULL.", hash -> table[i] == NULL);
    }
}

void testNewHashEntry() {
    char * name = "darci";
    struct hashEntry * entry = newHashEntry("name", name, sizeof(name));
    expect("New hashEntry has corect value set.",
           strcmp(entry -> value, name) == 0);
    expect("New hashEntry value has been copied.", name != entry -> value);
    expect("New entry has next set to NULL.", entry->next == NULL);
}

void testHashKey() {
    expect("Hash of 'cat', 8 is 4.", hashKey("cat", 8) == 4);
    expect("Hash of 'cat', 12 is 0.", hashKey("cat", 12) == 0);
    expect("Hash of 'dog', 6 is 5.", hashKey("dog", 6) == 5);
    expect("Hash of 'dog', 13 is 11.", hashKey("dog", 13) == 11);
}

void testHashSet() {
    struct hashTable * hash = newCHash(1);
    
    // test inserting new into new bucket.
    char * bunny = "Bunny";
    hashSet(hash, "B", bunny, sizeof(bunny));
    int hashId;
    hashId = hashKey("B", hash -> size);
    expect("New element has key 'B'.",
           strcmp(hash -> table[hashId] -> key, "B") == 0);
    expect("New element has value 'Bunnu'",
           strcmp(hash -> table[hashId] -> value, bunny) == 0);

    // test inserting at beginning of existing bucket.
    char * apple = "Apple";
    hashSet(hash, "A", apple, sizeof(apple));
    hashId = hashKey("A", hash -> size);
    expect("Insert at beginning of bucket.",
           strcmp(hash -> table[hashId] -> value, apple) == 0);
    expect("Previous element now at end of bucket.",
           strcmp(hash -> table[hashId] -> next -> value, bunny) == 0);

    // test inserting at end of existing bucket.
    char * cobbler = "cobbler";
    hashSet(hash, "C", cobbler, sizeof(cobbler));
    hashId = hashKey("C", hash -> size);
    expect("Insert at end of bucket.",
           strcmp(hash -> table[hashId] -> next -> next -> value,
                  cobbler) == 0);

    // update existing key
    char * carrot = "carrot";
    hashSet(hash, "C", "carrot", sizeof(carrot));
    expect("Updated existing key.",
           strcmp(hash -> table[hashId] -> next -> next -> value,
                  carrot) == 0);

    // set keys into different buckets.
    struct hashTable * hash_2 = newCHash(2);
    int hashIdA;
    int hashIdB;
    hashIdA = hashKey("A", hash_2 -> size);
    hashIdB = hashKey("B", hash_2 -> size);
    expect("Hashes are different", hashIdA != hashIdB);
    hashSet(hash_2, "A", apple, sizeof(apple));
    hashSet(hash_2, "B", bunny, sizeof(bunny));
    expect("A maps to apple.",
           strcmp(hash_2 -> table[hashIdA] -> value, apple) == 0);
    expect("B maps to bunny.",
           strcmp(hash_2 -> table[hashIdB] -> value, bunny) == 0);

}


void testHashGet() {
    struct hashTable * hash = newCHash(3);
    hashSet(hash, "A", "apple", sizeof("apple"));
    hashSet(hash, "B", "bunny", sizeof("bunny"));
    hashSet(hash, "C", "cobbler", sizeof("cobbler"));
    hashSet(hash, "D", "dawn", sizeof("dawn"));
    hashSet(hash, "E", "eagle", sizeof("eagle"));
    expect("A is for apple",
           strcmp((char *)hashGet(hash, "A"), "apple") == 0);
    expect("B is for bunny",
           strcmp((char *)hashGet(hash, "B"), "bunny") == 0);
    expect("C is for cobbler",
           strcmp((char *)hashGet(hash, "C"), "cobbler") == 0);
    expect("D is for dawn",
           strcmp((char *)hashGet(hash, "D"), "dawn") == 0);
    expect("E is for eagle",
           strcmp((char *)hashGet(hash, "E"), "eagle") == 0);
}

int main() {
    printf("Running tests...\n");
    testNewChash();
    testNewHashEntry();
    testHashKey();
    testHashSet();
    testHashGet();
    printf("Ran %d tests. %d failed.\n", tests, fails);
    return 0;
}
