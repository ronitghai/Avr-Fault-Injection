#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

// Define FPGA GPIO registers and addresses
#define GPIO_BASE_ADDR 0x1000
#define GPIO_DATA_IN_REG_OFFSET 0x00
#define GPIO_DATA_OUT_REG_OFFSET 0x04
#define GPIO_DIRECTION_REG_OFFSET 0x08
#define GPIO_INTERRUPT_REG_OFFSET 0x0C

// Define clock prescaler value
#define PRESCALER_VALUE 256

// Define GPIO pin numbers
#define INPUT_PIN 1
#define OUTPUT_PIN 2

// Function prototypes
void setup_gpio_input_falling_edge_interrupt();
void setup_victim_clock();
void setup_gpio_output_for_victim();
void power_down();
void delay_ms(uint32_t ms);
void power_up();

int main() {
    // Set up GPIO input falling edge interrupt
    setup_gpio_input_falling_edge_interrupt();
    
    // Set up victim clock
    setup_victim_clock();
    
    // Set up GPIO output for powering the victim
    setup_gpio_output_for_victim();
    
    // Main loop
    while (1) {
        if (some_condition_is_met()) {
            // Perform some action when the condition is met
            // For demonstration, let's just print a message
            printf("Condition met, triggering glitch!\n");
            
            // Simulate a glitch by manually triggering the ISR
            gpio_input_falling_edge_isr();
            
            // Optionally add a delay here to prevent rapid triggering
            // delay_ms(1000); // Delay for 1 second
        }

        // Read the current state of GPIO 1
        bool currentInputState = GPIO_DATA_REG & (1 << 1);

        // Check for falling edge manually
        if (previousInputState && !currentInputState) {
            printf("Falling edge detected! Executing glitch attack...\n");
            GPIO_FallingEdgeInterruptHandler(); // Perform the glitch attack
        }

        // Update the previous state
        previousInputState = currentInputState;

        // Small delay to debounce and prevent too frequent polling (simulate delay)
        for (volatile int i = 0; i < 1000000; i++) {} // Simple software delay loop
    }
        
        // Sleep for a short period to avoid consuming too much CPU
        usleep(10000);
    
    return 0;
}

void setup_gpio_input_falling_edge_interrupt() {
    // Configure GPIO pin as input
    *(volatile uint32_t*)(GPIO_BASE_ADDR + GPIO_DIRECTION_REG_OFFSET) &= ~(1 << INPUT_PIN);
    
    // Configure falling edge interrupt for the input pin
    *(volatile uint32_t*)(GPIO_BASE_ADDR + GPIO_INTERRUPT_REG_OFFSET) |= (1 << INPUT_PIN);
}

void setup_victim_clock() {
    // Configure victim clock with prescaler
    // Define the base address of the clock control registers
    volatile uint32_t* clock_base = (volatile uint32_t*)0x2000; // Example address, replace with actual base address

    // Configure clock prescaler value
    clock_base[CLOCK_PRESCALER_REG_OFFSET / sizeof(uint32_t)] = PRESCALER_VALUE;
    
    // Enable clock with prescaler
    clock_base[CLOCK_CTRL_REG_OFFSET / sizeof(uint32_t)] |= 0x01; // Set bit 0 to enable the clock
}

void setup_gpio_output_for_victim() {
    // Configure GPIO pin as output
    *(volatile uint32_t*)(GPIO_BASE_ADDR + GPIO_DIRECTION_REG_OFFSET) |= (1 << OUTPUT_PIN);
}

// Interrupt service routine for GPIO input falling edge
void __attribute__((interrupt)) gpio_input_falling_edge_isr() {
    // Power down
    power_down();
    
    // Delay for a while
    delay_ms(1000);
    
    // Power up
    power_up();
}

// Function to power down the victim
void power_down() {
    // Clear the GPIO output pin to power down the victim
    *(volatile uint32_t*)(GPIO_BASE_ADDR + GPIO_DATA_OUT_REG_OFFSET) &= ~(1 << OUTPUT_PIN);
}

// Function to delay for a given number of milliseconds
void delay_ms(uint32_t ms) {
    usleep(ms * 1000); // usleep takes microseconds
}

// Function to power up the victim
void power_up() {
    // Set the GPIO output pin to power up the victim
    *(volatile uint32_t*)(GPIO_BASE_ADDR + GPIO_DATA_OUT_REG_OFFSET) |= (1 << OUTPUT_PIN);
}