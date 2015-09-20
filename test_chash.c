#include <stdlib.h>
#include <stdio.h>
#include <chash.h>

static int tests = 0, fails = 0;
#define test(_s) { printf("#%02d %s ", ++tests, _s); }
#define print_pass() printf("\033[0;32mPASSED\033[0;0m\n")
#define print_fail() printf("\033[0;31mFAILED\033[0;0m\n")
#define test_cond(_c) {if(_c) print_pass(); else {print_fail(); fails++;}}
#define expect(_s, _c) { test(_s); test_cond(_c); }

void testNewChash() { 
    struct hashTable * hash = newCHash(12);
    expect("Hash table size is 12.", hash->size == 12);
    int i;
    for (i =0; i < 12; i++) {
        expect("Hash entry is NULL.", hash -> table[i] == NULL);
    }
}

void testHashKey() {
    expect("Hash of 'cat', 8 is 4.", hashKey("cat", 8) == 4);
    expect("Hash of 'cat', 12 is 0.", hashKey("cat", 12) == 0);
    expect("Hash of 'dog', 6 is 5.", hashKey("dog", 6) == 5);
    expect("Hash of 'dog', 13 is 11.", hashKey("dog", 13) == 11);
}

int main() {
    printf("Running tests...\n");
    testNewChash();
    testHashKey();
    printf("Ran %d tests. %d failed.\n", tests, fails);
    return 0;
}
