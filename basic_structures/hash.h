
typedef struct HASH {
    Generic *table;
} HASH;

Generic HASH_Create() {
    HASH *new_hash = (HASH*) malloc(sizeof(HASH));
    new_hash->table = calloc(MAX_HASH_SIZE, sizeof(Generic));
    return new_hash;
}

Generic HASH_Insert(Hash *hash, Generic data, Integer index) {
    hash->table[index] = data;
}
