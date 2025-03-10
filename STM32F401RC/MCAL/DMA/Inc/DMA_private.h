/*
 *  DMA_private.h
 *
 *  Created on: Dec 8, 2024
 *  Author: Ahmed Ragab
 */

#ifndef DMA_PRIVATE_H_
#define DMA_PRIVATE_H_

#define MAX_NUMBER_DMA                   2

#define ENABLE_STREAM_MASK               1u
#define ENABLE_STREAM_PIN_ACCESS         0

#define CHANNEL_STREAM_MASK              0b111
#define CHANNEL_STREAM_PIN_ACCESS        25u

#define PRIORITY_STREAM_MASK             0b11
#define PRIORITY_STREAM_PIN_ACCESS       16u

#define DIRECTION_STREAM_MASK            0b11
#define DIRECTION_STREAM_PIN_ACCESS      6u

#define CIRCULAR_STREAM_MASK             1u
#define CIRCULAR_STREAM_PIN_ACCESS       8u

#define DIRECT_MODE_STREAM_MASK          1u
#define DIRECT_MODE_STREAM_PIN_ACCESS    2u

#define FIFO_THRESHOLD_STREAM_MASK       0b11
#define FIFO_THRESHOLD_STREAM_PIN_ACCESS 0

#define ISR_REG_SHIFTING                 4u
#define TIMEOUT                         0xffffffu
#define TIME_FINISHED                    0
#define ONE                              1u

#define TCIE_MASK                        1u
#define TCIE_PIN_ACCESS                  4u
#define TEIE_MASK                        1u
#define TEIE_PIN_ACCESS                  2u

#endif /* DMA_PRIVATE_H_ */
