#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Block {
    struct Block* next;
    int is_free;         // 1 is for free, 0 is for allocated
    char data[];         // Flexible array member
} Block;

#define MEMORY_POOL_SIZE (1024 * 1024 * 100)  // 100MB
#define BLOCK_SIZE 64                         // Block size in bytes
#define NUM_BLOCKS (MEMORY_POOL_SIZE / (sizeof(Block) + BLOCK_SIZE))

void* memory_pool = NULL;
Block* free_list = NULL;  // Pointer to the first block in the free list

void initialize_memory_pool() {
    memory_pool = malloc(MEMORY_POOL_SIZE);
    if (memory_pool == NULL) {
        printf("Failed to allocate memory pool!\n");
        exit(1);
    }
    printf("Memory pool initialized with %ld blocks of size %d bytes\n", NUM_BLOCKS, BLOCK_SIZE);
}

void initialize_memory_pool_linked_list() {
    // Initialize the memory pool as a linked list of blocks
    free_list = (Block*)memory_pool;  // Start with the first block
    Block* current_block = free_list;

    for (int i = 0; i < NUM_BLOCKS - 1; i++) {
        current_block->is_free = 1;  // Mark the block as free
        current_block->next = (Block*)((char*)current_block + sizeof(Block) + BLOCK_SIZE);  // Link to the next block
        current_block = current_block->next;
    }

    // Last block points to NULL
    current_block->is_free = 1;
    current_block->next = NULL;
}

int main() {
    initialize_memory_pool();
    initialize_memory_pool_linked_list();
    return 0;
}
