#ifndef LDSC_QUEUE_H
#define LDSC_QUEUE_H

typedef struct LDSC_queue LDSC_queue;
typedef struct privateData privateData;

struct LDSC_queue {
  /**
   * @brief Check is queue is empty.
   * @param self Queue pointer.
   * @return Integer where 1 = empty and 0 = not empty.
   */
  int (*empty)(LDSC_queue* self);

  /**
   * @brief Get length of the queue.
   * @param self Queue pointer.
   * @return Length of the stack as integer type.
   */
  int (*length)(LDSC_queue* self);

  /**
   * @brief Add item to end of the queue.
   * @param self Queue pointer.
   * @param dataPtr Pointer to data.
   * @details
   * Keep note that enqueue performs a shallow copy of the data.
   */
  void (*enqueue)(LDSC_queue* self, void* dataPtr);

  /**
   * @brief Remove item from fron of the queue.
   * @param self Queue pointer.
   * @return Pointer to data at the front of the queue.
   */
  void* (*dequeue)(LDSC_queue* self);

  /**
   * @brief Peek item at the front of the queue.
   * @param self Queue pointer.
   * @return Pointer to data at the front of the queue.
   */
  void* (*peek)(LDSC_queue* self);

  /**
   * @brief Delete the queue.
   * @param self Queue pointer.
   */
  void (*delete)(LDSC_queue* self);

  /**
   * @brief Opaque container for private data.
   */
  privateData* pd;
} ;

/**
 * @brief Create a new queue.
 * @return Pointer to a LDSC_queue.
 */
LDSC_queue* LDSC_queue_init();

#endif
