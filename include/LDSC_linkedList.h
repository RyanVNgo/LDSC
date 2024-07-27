#ifndef LDSC_LINKEDLIST_H
#define LDSC_LINKEDLIST_H

typedef struct LDSC_linkedList LDSC_linkedList;
typedef struct privateData privateData;

struct LDSC_linkedList {
  /**
   * @brief Get length of the linked list.
   * @param self LDSC_linkedList pointer.
   * @return Length of the linked list as integer type.
   */
  int (*length)(LDSC_linkedList* self);

  /**
   * @brief Check if linked list is empty.
   * @param self LDSC_linkedList pointer.
   * @return Integer where 1 = empty and 0 = not empty.
   */
  int (*empty)(LDSC_linkedList* self);

  /**
   * @brief Add item at the end of the linked list.
   * @param self LDSC_linkedList pointer.
   * @param dataPtr Pointer to data.
   * @return Integer where 1 = success and 0 = failure.
   * @details
   * Keep note that append performs a shallow copy of the data.
   */
  int (*append)(LDSC_linkedList* self, void* dataPtr);

  /**
   * @brief Add item at the front of the linked list.
   * @param self LDSC_linkedList pointer.
   * @param dataPtr Pointer to data.
   * @return Integer where 1 = success and 0 = failure.
   * @details
   * Keep note that prepend performs a shallow copy of the data.
   */
  int (*prepend)(LDSC_linkedList* self, void* dataPtr);

  /**
   * @brief Add item at index of the linked list.
   * @param self LDSC_linkedList pointer.
   * @param dataPtr Pointer to data.
   * @param index Index to add item at.
   * @return Integer where 1 = success and 0 = failure.
   * @details
   * Keep note that add performs a shallow copy of the data.
   */
  int (*add)(LDSC_linkedList* self, void* dataPtr, int index);

  /**
   * @brief Get item at index.
   * @param self LDSC_linkedList pointer.
   * @param index Index of item to get.
   * @return Data pointer of item at index.
   */
  void* (*at)(LDSC_linkedList* self, int index);

  /**
   * @brief Replace item at index.
   * @param self LDSC_linkedList pointer.
   * @param dataPtr Pointer to data.
   * @param index Index of item to replace with dataPtr.
   * @return Data pointer of item that was replaced.
   * @details
   * Keep note that replace performs a shallow copy of the data.
   */
  void* (*replace)(LDSC_linkedList* self, void* dataPtr, int index);

  /**
   * @brief Remove item at the front of the list.
   * @param self LDSC_linkedList pointer.
   * @return Data pointer of item that was removed.
   */
  void* (*pop)(LDSC_linkedList* self);

  /**
   * @brief Remove item at the end of the list.
   * @param self LDSC_linkedList pointer.
   * @return Data pointer of item that was removed.
   */
  void* (*pull)(LDSC_linkedList* self);

  /**
   * @brief Remove item at index.
   * @param self LDSC_linkedList pointer.
   * @param index Index of item to remove.
   * @return Data pointer of item that was removed.
   */
  void* (*remove)(LDSC_linkedList* self, int index);

  /**
   * @brief Remove all items in the list.
   * @param self LDSC_linkedList pointer.
   */
  void (*clear)(LDSC_linkedList* self);

  /**
   * @brief Delete the linked list
   * @param self LDSC_ilnkedList pionter.
   */
  void (*delete)(LDSC_linkedList* self);

  /**
   * @brief Opaque container for private data.
   */
  privateData* pd;

};

/**
 * @brief Create a new linked list.
 * @return Pointer to a LDSC_linkedList.
 */
LDSC_linkedList* LDSC_linkedList_init();

#endif
