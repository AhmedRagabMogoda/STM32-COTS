/**
 * @file  : linkerscript.ld
 * @author: Ahmed Ragab Mogoda
 * @date  : 2025-01-05
 * @brief : Linker script for STM32 microcontroller defining memory layout and sections.
 *
 * This linker script specifies the memory regions (FLASH and SRAM) and organizes 
 * the placement of code and data sections into these regions. It ensures that 
 * interrupt vectors, text, data, and uninitialized sections are properly allocated 
 * within the microcontroller's memory map.
 */

ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rx): ORIGIN = 0x08000000 , LENGTH = 512K
	SRAM(rwx): ORIGIN = 0x20000000 , LENGTH = 128K
}

SECTIONS
{
	.text :
	{
		*(.isr_vector)
		*(.text)
	}>FLASH

	.rodata :
	{
		*(.rodata)
		. = ALIGN(4);
		_erodata = . ;
	}>FLASH

	.data :
	{
		_sdata = . ;
		*(.data)
		. = ALIGN(4);
		_edata = . ;
	}>SRAM AT> FLASH

	.bss :
	{
		_sbss = . ;
		*(.bss)
		. = ALIGN(4);
		_ebss = . ;
	}>SRAM
}