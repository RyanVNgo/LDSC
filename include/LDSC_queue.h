#ifndef LDSC_QUEUE_H
#define LDSC_QUEUE_H

typedef struct LDSC_queue LDSC_queue;

/**
 * @brief Create a new queue
 * @return Pointer to a new queue
 */
LDSC_queue* LDSC_queue_init();

/**
 * @brief Return length of the queue
 * @param queueIn Pointer to LDSC_queue
 * @return Integer representing number of items in the queue
 */
int LDSC_queue_length(LDSC_queue* queueIn);

/**
 * @brief Enqueue item to queue
 * @param queueIn Pointer to LDSC_queue
 * @param dataPtr Pointer of data to store
 */
void LDSC_queue_enqueue(LDSC_queue* queueIn, void* dataPtr);

/**
 * @brief Dequeue item from queue
 * @param queueIn Pointer to LDSC_queue
 * @return Pointer to item at front of the queue
 */
void* LDSC_queue_dequeue(LDSC_queue* queueIn);

/**
 * @brief Get item at front of the queue
 * @param queueIn Pointer to LDSC_queue
 * @return Pointer to data stored at the front of the queue
 */
void* LDSC_queue_peek(LDSC_queue* queueIn);

#endif
