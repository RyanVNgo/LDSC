/** @file   init.c
 *  @brief  Function definitions for each initialization.
 *
 *  @author Ryan V. Ngo
 */

#include "LDSC.h"
#include "factory.h"
#include "type_masks.h"

/****************************** Initializations ******************************/

/** @brief  Initialize a LDSC_structure as a linked list.
 *  @return Pointer to new LDSC data structure.
 */
LDSC_structure* LDSC_linked_list_init() {
  return initialize_structure(LinkedList_ID);
}


/** @brief  Initialize a LDSC_structure as a queue.
 *  @return Pointer to new LDSC data structure.
 */
LDSC_structure* LDSC_queue_init() {
  return initialize_structure(Queue_ID);
}

/** @brief  Initialize a LDSC_structure as a stack.
 *  @return Pointer to new LDSC data structure.
 */
LDSC_structure* LDSC_stack_init() {
  return initialize_structure(Stack_ID);
}
