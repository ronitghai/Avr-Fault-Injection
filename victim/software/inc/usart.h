#include <avr/io.h>
#include <stdint.h>

void usart_init(unsigned int baud);

void usart_transmit_char(unsigned char data);

void usart_transmit_hex(uint8_t *data, uint8_t len);