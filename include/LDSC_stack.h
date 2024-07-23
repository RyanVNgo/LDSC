#ifndef LDSC_STACK_H
#define LDSC_STACK_H

typedef struct LDSC_stack LDSC_stack;

/**
 * @brief Create a new stack
 * @return Pointer to a new stack
 */
LDSC_stack* LDSC_stack_init();

/**
 * @brief Get the length of the stack
 * @param stackIn Pointer to LDSC_stack
 * @return Integer representing number of items in the stack
 */
int LDSC_stack_length(LDSC_stack* stackIn);

/**
 * @brief Check if stack is empty
 * @param stackIn Pointer to LDSC_stack
 * @return Integer where empty = 1, non-empty = 0, fail = -1
 */
int LDSC_stack_isEmpty(LDSC_stack* stackIn);

/**
 * @brief Push new item to the stack
 * @param stackIn Pointer to LDSC_stack
 * @param dataPtr Pointer of data to store
 */
void LDSC_stack_push(LDSC_stack* stackIn, void* dataPtr);

/**
 * @brief Get item on top of stack
 * @param stackIn Pointer to LDSC_stack
 * @return Pointer to data stored at top
 */
void* LDSC_stack_peek(LDSC_stack* stackIn);

/**
 * @brief Remove and return item on top of stack
 * @param stackIn Pointer to LDSC_stack
 * @return Pointer to data stored at top
 */
void* LDSC_stack_pop(LDSC_stack* stackIn);

#endif
