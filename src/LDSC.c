/** @file   LDSC.c
 *  @brief  Function definitions for generalized methods.
 *
 *  @author Ryan V. Ngo
 */

#include "LDSC.h"
#include "factory.h"
#include "type_masks.h"

#include <stdlib.h>

/****************************** Private Methods ******************************/

void _data_del_standard(void* data_ptr) {
  return free(data_ptr);
};

/****************************** Generalized Methods ******************************/

/** @brief  Get the length of the structure (number of elements).
 *
 *  @param  structure   (I) - poitner to a LDSC data structure.
 *  @return Length of structure (number of elements).
 */
int LDSC_length(const LDSC_structure* structure) {
  if (!structure) return LDSC_ERROR;
  return structure->length;
}

/** @brief  Check for whether or not the structure is empty (0 elements).
 *
 *  @param  structure   (I) - poitner to a LDSC data structure.
 *  @return 1 == True, 0 == False.
 */
int LDSC_empty(const LDSC_structure* structure) {
  if (!structure) return LDSC_ERROR;
  return (structure->length == 0);
}

/** @brief  Delete the data structure.
 *
 *  Note that if data_del is NULL, then the data pointed to by the structure
 *  will be de-allocated with a free(). If a more complex de-allocation is
 *  necessary, provide the function pointer through data_del.
 *  
 *  @param  structure   (IO) - Pointer to data structure.
 *  @param  data_del    (I) - Pointer to custom data de-alloc function.
 *  @return Void.
 */
void LDSC_delete(LDSC_structure* structure, void (*data_del)(void*)) {
  /* set data del to standard if not passed */
  if (!data_del) data_del = _data_del_standard;

  /* delete and free nodes */
  Node* current_node = structure->head;
  while (current_node != NULL) {
    void* next_node = current_node->next;
    data_del(current_node->data_ptr);
    free(current_node);
    current_node = next_node;
  }

  /* free primary structure */
  free(structure);
  return;
}

/** @brief  Add an element to the end of the structure.
 *  
 *  @param  structure   (IO) - Pointer to data structure.
 *  @param  data_ptr    (I) - Pointer to the data.
 *  @return 0 == OK, !0 == Error.
 */
int LDSC_append(LDSC_structure* structure, void* data_ptr) {
  /* if structure or data is NULL */
  if (!structure || !data_ptr) return LDSC_ERROR;
  
  /* is a valid structure for append */
  if (!(structure->id & APPEND_MASK)) return LDSC_INVALID_STRUCT;

  /* initialize the node */
  Node* new_node = node_init(structure->id);
  new_node->data_ptr = data_ptr;

  /* insert new node (empty structure) */
  if (structure->length == 0) {
    structure->head = new_node;
    if (structure->id & HEAD_TAIL_MASK) {
      structure->tail = new_node;
    }
    structure->length++;
    return 0;
  }

  /***** insert new node (non-empty structure) *****/
  /* get last node */
  Node* last_node = NULL;
  if (structure->id & HEAD_TAIL_MASK) {
    last_node = structure->tail;
  } else {
    last_node = structure->head;
    while (last_node->next != NULL) {
      last_node = last_node->next;
    }
  }

  /* set next of current tail */
  last_node->next = new_node; 

  /* if DL, set new node's prev to current tail */
  if (structure->id & DOUBLY_LINKED_MASK) {
    new_node->prev = last_node; 
  }

  /* set structure tail to new node */
  structure->tail = new_node;

  /* increase structure length */
  structure->length++;
  
  return 0;
}

/** @brief  Add an element to the front of the structure.
 *
 *  @param  structure   (IO) - Pointer to data structure.
 *  @param  data_ptr    (I) - Pointer to the data.
 *  @return 0 == OK, !0 == Error.
 */
int LDSC_prepend(LDSC_structure* structure, void* data_ptr) {
  /* if structure or data is NULL */
  if (!structure || !data_ptr) return LDSC_ERROR;
  
  /* is a valid structure for append */
  if (!(structure->id & PREPEND_MASK)) return LDSC_INVALID_STRUCT;

  /* initialize the node */
  Node* new_node = node_init(structure->id);
  new_node->data_ptr = data_ptr;

  /* insert new node (empty structure) */
  if (structure->length == 0) {
    structure->head = new_node;
    if (structure->id & HEAD_TAIL_MASK) {
      structure->tail = new_node;
    }
    structure->length++;
    return 0;
  }

  /***** insert new node (non-empty structure) *****/
  /* set next of new node */
  new_node->next = structure->head;

  /* set prev of current head if applicable */
  if (structure->id & DOUBLY_LINKED_MASK) {
    structure->head->prev = new_node;
  }

  /* set structure head to new node */
  structure->head = new_node;

  /* increase structure length */
  structure->length++;

  return 0;
}

/** @brief  Add an element at the index.
 *
 *  @param  structure   (IO) - Pointer to data structure.
 *  @param  data_ptr    (I) - Pointer to the data.
 *  @param  index       (I) - Index, can be negative.
 *  @return 0 == OK, !0 == Error.
 */
int LDSC_insert(LDSC_structure* structure, void* data_ptr, int index) {
  /* if structure or data is NULL */
  if (!structure || !data_ptr) return LDSC_ERROR;
  
  /* is a valid structure for append */
  if (!(structure->id & INSERT_MASK)) return LDSC_INVALID_STRUCT;

  /* invalid index */
  if (index > structure->length || index < -(structure->length + 1)) return LDSC_INVALID_INDEX;

  /* initialize the node */
  Node* new_node = node_init(structure->id);
  new_node->data_ptr = data_ptr;

  /* insert new node (empty structure) */
  if (structure->length == 0) {
    structure->head = new_node;
    if (structure->id & HEAD_TAIL_MASK) {
      structure->tail = new_node;
    }
    structure->length++;
    return 0;
  }

  /***** head insert case *****/
  if (index == 0 || index == -(structure->length + 1)) {
    /* set next of new node */
    new_node->next = structure->head;

    /* set prev of current head if applicable */
    if (structure->id & DOUBLY_LINKED_MASK) {
      structure->head->prev = new_node;
    }

    /* set structure head to new node */
    structure->head = new_node;

    /* increase structure length */
    structure->length++;

    return 0;
  }


  /***** tail insert case *****/
  if (index == structure->length || index == -1) {
    /* get last node */
    Node* last_node = NULL;
    if (structure->id & HEAD_TAIL_MASK) {
      last_node = structure->tail;
    } else {
      last_node = structure->head;
      while (last_node->next != NULL) {
        last_node = last_node->next;
      }
    }

    /* set next of current tail */
    last_node->next = new_node; 

    /* if DL, set new node's prev to current tail */
    if (structure->id & DOUBLY_LINKED_MASK) {
      new_node->prev = last_node; 
    }

    /* set structure tail to new node */
    structure->tail = new_node;

    /* increase structure length */
    structure->length++;
    
    return 0;
  }

  /***** standard insert case *****/
  /* set index to positive equivalent if negative */
  /**
   * This can be optimized by traversing backwards in the case
   * that the tail is available and the structure is
   * doubly linked. This may/will be a future implementation
   */
  if (index < 0) index = structure->length + 1 + index;

  /* reach node before insert */
  Node* prev_node = structure->head;
  for (int i = 0; i < index - 1; i++) {
    prev_node = prev_node->next;
  }

  /* set next of new node */
  new_node->next = prev_node->next;

  /* set next of previous node */
  prev_node->next = new_node;

  /* if doubly linked, set prev of new node and next of new node */
  if (structure->id & DOUBLY_LINKED_MASK) {
    new_node->prev = prev_node;
    new_node->next->prev = new_node;
  }

  /* increase structure length */
  structure->length++;

  return 0;
}

/** @brief  Add an element to the top/head.
 *
 *  @param  structure   (IO) - Pointer to data structure.
 *  @param  data_ptr    (I) - Pointer to the data.
 *  @return 0 == OK, !0 == Error.
 */
int LDSC_push(LDSC_structure* structure, void* data_ptr) {
  /* if structure or data is NULL */
  if (!structure || !data_ptr) return LDSC_ERROR;
  
  /* is a valid structure for append */
  if (!(structure->id & PUSH_MASK)) return LDSC_INVALID_STRUCT;

  /* initialize the node */
  Node* new_node = node_init(structure->id);
  new_node->data_ptr = data_ptr;

  /* insert new node (empty structure) */
  if (structure->length == 0) {
    structure->head = new_node;
    if (structure->id & HEAD_TAIL_MASK) {
      structure->tail = new_node;
    }
    structure->length++;
    return 0;
  }

  /***** insert new node (non-empty structure) *****/
  /* get last node */
  Node* last_node = NULL;
  if (structure->id & HEAD_TAIL_MASK) {
    last_node = structure->tail;
  } else {
    last_node = structure->head;
    while (last_node->next != NULL) {
      last_node = last_node->next;
    }
  }

  /* set next of current tail */
  last_node->next = new_node; 

  /* if DL, set new node's prev to current tail */
  if (structure->id & DOUBLY_LINKED_MASK) {
    new_node->prev = last_node; 
  }

  /* set structure tail to new node */
  structure->tail = new_node;

  /* increase structure length */
  structure->length++;

  return 0;
}

