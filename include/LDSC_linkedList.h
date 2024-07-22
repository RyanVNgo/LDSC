#ifndef LDSC_LINKEDLIST_H
#define LDSC_LINKEDLIST_H

typedef struct LDSC_linkedList LDSC_linkedList;

/**
 * @brief Create a new linked list
 * @return Pointer to a new linked list
 */
LDSC_linkedList* LDSC_linkedList_init();

/**
 * @brief Return length of the list
 * @param LLin Pointer to LDSC_linkedList
 * @return Integer representing numbe of items in the list
 */
int LDSC_linkedList_length(LDSC_linkedList* LLin);

/**
 * @brief Get data at head
 * @param LLin Pointer to LDSC_linkedList
 * @return Pointer to data stored at head
 */
void* LDSC_linkedList_head(LDSC_linkedList* LLin);

/**
 * @brief Get data at tail
 * @param LLin Pointer to LDSC_linkedList
 * @return Pointer to data stored at tail
 */
void* LDSC_linkedList_tail(LDSC_linkedList* LLin);

/**
 * @brief Append item to list
 * @param LLin Pointer to LDSC_linkedList
 * @param dataPtr Pointer of data to store
 */
void LDSC_linkedList_append(LDSC_linkedList* LLin, void* dataPtr);

/**
 * @brief Prepend item to list
 * @param LLin Pointer to LDSC_linkedList
 * @param dataPtr Pointer of data to store
 */
void LDSC_linkedList_prepend(LDSC_linkedList* LLin, void* dataPtr);

/**
 * @brief Return data at index
 * @param LLin Pointer to LDSC_linkedList
 * @param index Index of node to return data from 
 * @return Pointer to data stored as index
 */
void* LDSC_linkedList_get(LDSC_linkedList* LLin, int index);

/**
 * @brief Insert data at index
 * @param LLin Pointer to LDSC_linkedList
 * @param index Index to inset at
 */
void LDSC_linkedList_insert(LDSC_linkedList*, void* LLin, int index);

/**
 * @brief Remove first item of the list
 * @param LLin Pointer to LDSC_linkedList
 */
void* LDSC_linkedList_removeFirst(LDSC_linkedList* LLin);

/**
 * @brief Remove last item of the lst
 * @param LLin Pointer to LDSC_linkedlist
 */
void* LDSC_linkedList_removeLast(LDSC_linkedList* LLin);

/**
 * @brief Remove data at index
 * @param LLin Pointer to LDSC_linkedList
 * @param index Index of data to remove
 */
void* LDSC_linkedList_remove(LDSC_linkedList* LLin, int index);

#endif
