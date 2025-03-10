/*
 *  SCB_interface.h
 *
 *  Created on: Nov 30, 2024
 *  Author: Ahmed Ragab
 */

#ifndef SCB_INTERFACE_H_
#define SCB_INTERFACE_H_


typedef enum{
	 Group8_Sub2=4,
	 Group4_Sub4,
	 Group2_Sub8,
	 NoneGroup_Sub16,
}PriorityGroup_t;


/*================================================================================================*/

/**
 * @brief   Sets the priority grouping configuration for the Cortex-M processor.
 *          The priority grouping determines the number of priority bits allocated
 *          to the preemption priority and the number of bits allocated to the
 *          sub-priority in the interrupt system.
 *
 *          The priority grouping is configured via the **AIRCR** register of the
 *          **System Control Block (SCB)**. The function uses the **PriorityGroup_t**
 *          enum to specify the priority grouping configuration. This function
 *          enables adjusting how interrupts are prioritized.
 *
 * @param   PriorityGroup    The priority grouping configuration.
 *          This value is an enumeration defined by the user to select the
 *          appropriate priority group configuration. The valid values for
 *          this parameter are:
 *              - PriorityGroup_0: All bits for preemption priority.
 *              - PriorityGroup_1: 1 bit for sub-priority and the rest for preemption priority.
 *              - PriorityGroup_2: 2 bits for sub-priority and the rest for preemption priority.
 *              - PriorityGroup_3: 3 bits for sub-priority and the rest for preemption priority.
 *              - PriorityGroup_4: 4 bits for sub-priority and the rest for preemption priority.
 *              - etc. (depending on the implementation)
 *
 * @return  None
 **/
void SCB_SetPriorityGroup(PriorityGroup_t PriorityGroup);

/* Function: EnableMemoryManagementFault
 * Description: Enables the Memory Management Fault by setting the MEMFAULTENA bit in the SCB->SHCSR register.
 * Parameters: None
 * Return: None
 */
void SCB_EnableMemoryManagementFault(void);

/* Function: EnableBusFault
 * Description: Enables the Bus Fault by setting the BUSFAULTENA bit in the SCB->SHCSR register.
 * Parameters: None
 * Return: None
 */
void SCB_EnableBusFault(void);

/* Function: EnableUsageFault
 * Description: Enables the Usage Fault by setting the USGFAULTENA bit in the SCB->SHCSR register.
 * Parameters: None
 * Return: None
 */
void SCB_EnableUsageFault(void);

#endif /* SCB_INTERFACE_H_ */
