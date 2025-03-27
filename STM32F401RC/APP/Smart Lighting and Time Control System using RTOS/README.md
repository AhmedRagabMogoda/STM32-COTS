# Smart Lighting and Time Control System using RTOS

## Project Description
This project is an **RTOS-based embedded system** developed on the **STM32F401RC** microcontroller. It provides a **menu-driven interface via UART communication**, allowing users to control **LED effects** and configure **Real-Time Clock (RTC) settings**. The system is implemented using **FreeRTOS tasks, queues, and timers** for efficient task management and real-time operation.

## 1. Key Features
### 🟢 Task Management using FreeRTOS
The system uses multiple tasks, each responsible for a specific function:
- **MenuTask**: Displays the user menu and handles main options.
- **CMDTask**: Processes user commands received over UART.
- **LedTask**: Manages LED effects and executes different patterns.
- **RTCTask**: Configures and displays real-time clock settings.
- **PrintTask**: Handles UART message transmission.

### 🔵 LED Control Using FreeRTOS Software Timers
- The project supports **4 LED effects**, controlled using FreeRTOS timers.
- The user can select different LED effects via UART:
  - **Effect 1**: Toggles all LEDs ON/OFF.
  - **Effect 2**: Alternates between even and odd LEDs.
  - **Effect 3**: Left shift LED pattern.
  - **Effect 4**: Right shift LED pattern.

### ⏰ RTC Configuration and Display
- Allows the user to set and retrieve time and date.
- Uses HAL RTC APIs to read/write time.
- Implements validity checks for user input.
- Supports **12-hour format** with AM/PM detection.

### 📡 UART Communication for User Interaction
- Uses **UART6** for user input and system response.
- Commands are queued using **FreeRTOS queues** to avoid data loss.
- The system continuously listens for user input using **interrupt-driven UART reception**.

## 2. Communication Mechanisms
### Queues:
- **Q_Print**: Used to send messages from tasks to the **Print Task** for UART transmission.
- **Q_Data**: Used to store user input received via UART.

### Task Notifications:
- Tasks use **notifications** to signal each other (e.g., **Menu Task** notifies **LED Task** or **RTC Task** based on user input).

### Timers:
- **FreeRTOS timers** are used to control LED effects (e.g., toggling LEDs at regular intervals).

## 3. User Interaction
Users interact with the system via a **terminal connected to the UART interface**.

The system provides a **menu-driven interface**:
- **LED Effects**: Users can select from four LED effects or stop the current effect.
- **RTC Configuration**: Users can configure the time and date of the RTC.
- **Reporting**: Users can enable or disable RTC time/date reporting.

## 4. Hardware Setup
### Microcontroller:
- **STM32F401RC** (or similar).

### Peripherals:
- **GPIO**: Connected to four LEDs for effects.
- **UART**: Used for communication with the user.
- **RTC**: Used for time and date management.

## 5. Key Functions
### LED Control:
- `LedEffectStart()`: Starts a specific LED effect.
- `LedEffectStop()`: Stops all LED effects.
- `LedEffectCallBackFun()`: Timer callback function for LED effects.

### RTC Control:
- `RTC_voidShowTimeDate()`: Displays the current time and date via UART.
- `RTC_ConfigTime()`: Configures the RTC time.
- `RTC_ConfigData()`: Configures the RTC date.

### UART Communication:
- `HAL_UART_RxCpltCallback()`: Handles UART receive interrupts and processes user input.

### Task Handlers:
- `MenuTask()`, `CMDTask()`, `LedTask()`, `RTCTask()`, `PrintTask()`: Implement the functionality of each task.

## 6. How to Use
1. **Flash the firmware** onto the STM32F401RC microcontroller.
2. **Connect a UART terminal (e.g., PuTTY, Tera Term)** to communicate with the system.
3. **Navigate the menu** to:
   - Control LED effects.
   - Configure and display RTC settings.
4. **Use the menu options** to send commands via UART and interact with the system.
