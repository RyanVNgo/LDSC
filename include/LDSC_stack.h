#ifndef LDSC_STACK_H
#define LDSC_STACK_H

typedef struct LDSC_stack LDSC_stack;
typedef struct stackPrivate stackPrivate;

struct LDSC_stack {
  /**
   * @brief Get size of the stack.
   * @param self Stack pointer.
   * @return Size of the stack as integer type.
   */
  int (*size)(LDSC_stack* self); //!< Size member function */

  /**
   * @brief Push an item to the stack.
   * @param self Stack pointer.
   * @param dataPtr Pointer to data.
   * @details
   * Keep note that push performs a shallow copy of the data.
   */
  void (*push)(LDSC_stack* self, void* dataPtr);
  
  /**
   * @brief Check if stack is empty.
   * @param self Stack pointer.
   * @return Integer where 1 = empty and 0 = not empty
   */
  int (*isEmpty)(LDSC_stack* self);

  /**
   * @brief Peek item at the top of the stack.
   * @param self Stack pointer.
   * @return Pointer to data at the top of the stack.
   */
  void* (*peek)(LDSC_stack* self);

  /**
   * @brief Pop an item from the stack.
   * @param self Stack pointer.
   * @return Pointer to data at the top of the stack.
   */
  void* (*pop)(LDSC_stack* self);

  /**
   * @brief Delete the stack.
   * @param self Stack pointer.
   */
  void (*delete)(LDSC_stack* self);

  /**
   * @brief Opaque container for private data.
   */
  stackPrivate* pd;
} ;

/**
 * @brief Create a new stack.
 * @par Parameters
 *  None.
 * @return Pointer to an LDSC_stack.
 */
LDSC_stack* LDSC_stack_init();

#endif
