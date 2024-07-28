#ifndef LDSC_QUEUE_H
#define LDSC_QUEUE_H

#include <LDSC_errors.h>

typedef struct LDSC_queue LDSC_queue;
typedef struct privateData privateData;

struct LDSC_queue {
  /**
   * @brief Check is queue is empty.
   * @param self Queue pointer.
   * @param status Error pointer.
   * @return Integer where 1 = empty and 0 = not empty.
   */
  int (*empty)(LDSC_queue* self, LDSC_error* status);

  /**
   * @brief Get length of the queue.
   * @param self Queue pointer.
   * @param status Error pointer.
   * @return Length of the stack as integer type.
   */
  int (*length)(LDSC_queue* self, LDSC_error* status);

  /**
   * @brief Add item to end of the queue.
   * @param self Queue pointer.
   * @param dataPtr Pointer to data.
   * @param status Error pointer.
   * @details
   * Keep note that enqueue performs a shallow copy of the data.
   */
  void (*enqueue)(LDSC_queue* self, void* dataPtr, LDSC_error* status);

  /**
   * @brief Remove item from fron of the queue.
   * @param self Queue pointer.
   * @param status Error pointer.
   * @return Pointer to data at the front of the queue.
   */
  void* (*dequeue)(LDSC_queue* self, LDSC_error* status);

  /**
   * @brief Peek item at the front of the queue.
   * @param self Queue pointer.
   * @param status Error pointer.
   * @return Pointer to data at the front of the queue.
   */
  void* (*peek)(LDSC_queue* self, LDSC_error* status);

  /**
   * @brief Delete the queue.
   * @param self Queue pointer.
   * @param status Error pointer.
   */
  void (*delete)(LDSC_queue* self, LDSC_error* status);

  /**
   * @brief Opaque container for private data.
   */
  privateData* pd;
} ;

/**
 * @brief Create a new queue.
 * @param status Error pointer.
 * @return Pointer to a LDSC_queue.
 */
LDSC_queue* LDSC_queue_init(LDSC_error* status);

#endif
