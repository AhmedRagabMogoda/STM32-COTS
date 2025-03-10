/*
 *  RCC_private.h
 *
 *  Created on: Nov 23, 2024
 *  Author: Ahmed Ragab
 */

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_


/********************** RCC clock control register **********************/
typedef enum{
	HSION,HSIRDY,HSEON=16,HSERDY,HSEBYP,CSSON,PLLON=24,PLLRDY
}CR_t;

/***************** RCC Peripheral Definitions ***************************/

#define TIMEOUT 2000UL

#define TIME_FINISHED      0

#define CR_MASK            1u

#define SW_MASK            0b11
#define SW_PIN_ACCESS      0
#define SWS_MASK           ((RCC->CFGR)>>2)

#define PLLSRC_PIN_ACCESS  22u
#define PLLSRC_MASK        1u

#define PLLM_MASK          0b111111
#define PLLM_PIN_ACCESS    0
#define PLLN_MASK          0b111111111
#define PLLN_PIN_ACCESS    6
#define PLLP_MASK          0b11
#define PLLP_PIN_ACCESS    16

#define AHB1ENR_MASK       1u

#define APB1ENR_MASK       1u

#define APB2ENR_MASK       1u

/************************************************************************/

#endif /* MCAL_RCC_RCC_PRIVATE_H_ */
