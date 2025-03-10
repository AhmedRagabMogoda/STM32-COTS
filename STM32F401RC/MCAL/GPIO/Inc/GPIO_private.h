/*
 *  GPIO_private.h
 *
 *  Created on: Nov 25, 2024
 *  Author: Ahmed Ragab
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#define RESERVED                   (void*)0
#define GPIO_PERIPHERAL_NUM        8u   // Total GPIO peripherals
#define MODER_MASK                 0b11 // Mask for MODER bits
#define MODER_PIN_ACCESS           2u   // Bit width for MODER access

#define PUPDR_MASK                 0b11 // Mask for PUPDR bits
#define PUPDR_PIN_ACCESS           2u   // Bit width for PUPDR access

#define OTYPER_MASK                1u   // Mask for OTYPER bits

#define OSPEEDR_MASK               0b11 // Mask for OSPEEDR bits
#define OSPEEDR_PIN_ACCESS         2u   // Bit width for OSPEEDR access

#define AFR_MASK                   0b1111 // Mask for Alternate Function bits
#define AFR_PIN_ACCESS             4u     // Bit width for AFR access
#define AFR_PIN_SHIFTING           8u     // Number of pins per AFR register

#define IDR_MASK                   1u // Mask for IDR bit
#define ODR_MASK                   1u // Mask for ODR bit
#define BSRR_MASK                  1u // Mask for BSRR bit
#define BSRR_PIN_ACCESS            16u // Offset for clearing bits in BSRR


#endif /* GPIO_PRIVATE_H_ */
