#ifndef LDSC_STACK_H
#define LDSC_STACK_H

#include <LDSC_errors.h>

typedef struct LDSC_stack LDSC_stack;
typedef struct privateData privateData;

struct LDSC_stack {
  /**
   * @brief Get size of the stack.
   * @param self Stack pointer.
   * @param status Error pointer.
   * @return Size of the stack as integer type.
   */
  int (*size)(LDSC_stack* self, LDSC_error* status); //!< Size member function */

  /**
   * @brief Push an item to the stack.
   * @param self Stack pointer.
   * @param dataPtr Pointer to data.
   * @param status Error pointer.
   * @details
   * Keep note that push performs a shallow copy of the data.
   */
  void (*push)(LDSC_stack* self, void* dataPtr, LDSC_error* status);
  
  /**
   * @brief Check if stack is empty.
   * @param self Stack pointer.
   * @param status Error pointer.
   * @return Integer where 1 = empty and 0 = not empty
   */
  int (*empty)(LDSC_stack* self, LDSC_error* status);

  /**
   * @brief Peek item at the top of the stack.
   * @param self Stack pointer.
   * @param status Error pointer.
   * @return Pointer to data at the top of the stack.
   */
  void* (*peek)(LDSC_stack* self, LDSC_error* status);

  /**
   * @brief Pop an item from the stack.
   * @param self Stack pointer.
   * @param status Error pointer.
   * @return Pointer to data at the top of the stack.
   */
  void* (*pop)(LDSC_stack* self, LDSC_error* status);

  /**
   * @brief Delete the stack.
   * @param self Stack pointer.
   * @param status Error pointer.
   */
  void (*delete)(LDSC_stack* self, LDSC_error* status);

  /**
   * @brief Opaque container for private data.
   */
  privateData* pd;
} ;

/**
 * @brief Create a new stack.
 * @return Pointer to an LDSC_stack.
 */
LDSC_stack* LDSC_stack_init(LDSC_error* status);

#endif
