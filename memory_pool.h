#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stddef.h>

// Block structure
typedef struct Block {
    struct Block* next;
    int is_free;    // 1 for free, 0 for allocated
    char data[];    // Flexible array member
} Block;

// Declare the functions
void initialize_memory_pool();
void initialize_memory_pool_linked_list();

#endif // MEMORY_POOL_H
