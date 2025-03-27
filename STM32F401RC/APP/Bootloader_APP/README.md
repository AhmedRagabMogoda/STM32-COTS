# STM32 Bootloader for Secure Firmware Updates

This project implements a robust **bootloader** for STM32 microcontrollers, enabling secure firmware updates via UART communication. The bootloader provides a structured command interface to facilitate remote firmware updates while ensuring data integrity using **CRC verification**.

## Features

- **UART-Based Command Handling** – Receives and processes commands from a host device.
- **Secure CRC Validation** – Ensures data integrity with Cyclic Redundancy Check (CRC).
- **Firmware Update Management** – Supports flashing new firmware, erasing memory, and executing the application firmware.
- **Read/Write Memory Protection** – Enables/disables memory protection to prevent unauthorized modifications.
- **Device Information Retrieval** – Provides commands to read the bootloader version, chip ID, and protection status.
- **Address Validation & Execution** – Ensures a valid memory address before jumping to the application firmware.
- **Vector Table Relocation** – Configures the vector table to switch between bootloader and application firmware.

## Implemented Commands

1. `BL_GET_VERSION` – Retrieve the bootloader version.
2. `BL_GET_HELP` – List supported commands.
3. `BL_GET_CID` – Get the chip identification number.
4. `BL_GET_RDP_STATUS` – Check the Read Protection status.
5. `BL_GO_TO_ADDRESS` – Jump to a specified application address.
6. `BL_FLASH_ERASE` – Erase specific flash memory sectors.
7. `BL_MEMORY_WRITE` – Write data to flash memory.
8. `BL_MEMORY_READ` – Read data from memory.
9. `BL_EM_RW_PROTECT` – Enable read/write protection.
10. `BL_DISABLE_RW_PROTECT` – Disable read/write protection.
11. `BL_Read_Sector_Status` – Reads the protection status of Flash memory sectors.

## How It Works

1. The bootloader listens for commands via **UART6**.
2. Incoming data is parsed and **CRC verification** is performed.
3. The respective command handler executes the request.
4. If a new firmware image is received, it is written to flash memory.
5. Upon completion, the bootloader can transfer control to the application firmware.

## Usage

1. Connect the STM32 board to a host via UART.
2. Use a serial terminal or custom host software to send bootloader commands.
3. Monitor responses to verify successful execution.
4. Flash new firmware and jump to the application when ready.

This bootloader enhances **security**, **reliability**, and **upgradability** for STM32-based embedded systems, making it ideal for applications requiring remote firmware updates.

