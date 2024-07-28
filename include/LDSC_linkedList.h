#ifndef LDSC_LINKEDLIST_H
#define LDSC_LINKEDLIST_H

#include <LDSC_errors.h>

typedef struct LDSC_linkedList LDSC_linkedList;
typedef struct privateData privateData;

struct LDSC_linkedList {
  /**
   * @brief Get length of the linked list.
   * @param self LDSC_linkedList pointer.
   * @param status Error pointer.
   * @return Length of the linked list as integer type.
   */
  int (*length)(LDSC_linkedList* self, LDSC_error* status);

  /**
   * @brief Check if linked list is empty.
   * @param self LDSC_linkedList pointer.
   * @param status Error pointer.
   * @return Integer where 1 = empty and 0 = not empty.
   */
  int (*empty)(LDSC_linkedList* self, LDSC_error* status);

  /**
   * @brief Add item at the end of the linked list.
   * @param self LDSC_linkedList pointer.
   * @param dataPtr Pointer to data.
   * @param status Error pointer.
   * @details
   * Keep note that append performs a shallow copy of the data.
   */
  void (*append)(LDSC_linkedList* self, void* dataPtr, LDSC_error* status);

  /**
   * @brief Add item at the front of the linked list.
   * @param self LDSC_linkedList pointer.
   * @param dataPtr Pointer to data.
   * @param status Error pointer.
   * @details
   * Keep note that prepend performs a shallow copy of the data.
   */
  void (*prepend)(LDSC_linkedList* self, void* dataPtr, LDSC_error* status);

  /**
   * @brief Add item at index of the linked list.
   * @param self LDSC_linkedList pointer.
   * @param dataPtr Pointer to data.
   * @param index Index to add item at.
   * @param status Error pointer.
   * @details
   * Keep note that add performs a shallow copy of the data.
   */
  void (*add)(LDSC_linkedList* self, void* dataPtr, int index, LDSC_error* status);

  /**
   * @brief Get item at index.
   * @param self LDSC_linkedList pointer.
   * @param index Index of item to get.
   * @param status Error pointer.
   * @return Data pointer of item at index.
   */
  void* (*at)(LDSC_linkedList* self, int index, LDSC_error* status);

  /**
   * @brief Replace item at index.
   * @param self LDSC_linkedList pointer.
   * @param dataPtr Pointer to data.
   * @param index Index of item to replace with dataPtr.
   * @param status Error pointer.
   * @return Data pointer of item that was replaced.
   * @details
   * Keep note that replace performs a shallow copy of the data.
   */
  void* (*replace)(LDSC_linkedList* self, void* dataPtr, int index, LDSC_error* status);

  /**
   * @brief Remove item at the front of the list.
   * @param self LDSC_linkedList pointer.
   * @param status Error pointer.
   * @return Data pointer of item that was removed.
   */
  void* (*pop)(LDSC_linkedList* self, LDSC_error* status);

  /**
   * @brief Remove item at the end of the list.
   * @param self LDSC_linkedList pointer.
   * @param status Error pointer.
   * @return Data pointer of item that was removed.
   */
  void* (*pull)(LDSC_linkedList* self, LDSC_error* status);

  /**
   * @brief Remove item at index.
   * @param self LDSC_linkedList pointer.
   * @param index Index of item to remove.
   * @param status Error pointer.
   * @return Data pointer of item that was removed.
   */
  void* (*remove)(LDSC_linkedList* self, int index, LDSC_error* status);

  /**
   * @brief Remove all items in the list.
   * @param self LDSC_linkedList pointer.
   * @param status Error pointer.
   */
  void (*clear)(LDSC_linkedList* self, LDSC_error* status);

  /**
   * @brief Delete the linked list
   * @param self LDSC_ilnkedList pionter.
   * @param status Error pointer.
   */
  void (*delete)(LDSC_linkedList* self, LDSC_error* status);

  /**
   * @brief Opaque container for private data.
   */
  privateData* pd;
};

/**
 * @brief Create a new linked list.
 * @param status Error pointer.
 * @return Pointer to a LDSC_linkedList.
 */
LDSC_linkedList* LDSC_linkedList_init(LDSC_error* status);

#endif
