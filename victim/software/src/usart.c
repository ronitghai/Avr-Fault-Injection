#include "usart.h"

// See datasheet pp.149
void usart_init(unsigned int baud)
{
    // Set the baud rate
    uint16_t UBRRn = F_CPU/16/baud - 1;
    UBRR0L = (uint8_t)(UBRRn & 0xFF);
    UBRR0H = (uint8_t)(UBRRn >> 8);

    // Enable TX and RX
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

    // Use default frame format: 8 data, 0 parity, 1 stop
}

// See datasheet pp.150
void usart_transmit_char(unsigned char data)
{
    // Wair for the transfer buffer to empty
    while (!(UCSR0A & (1<<UDRE0)));

    // Put the data into the buffer
    UDR0 = data;
}

void usart_transmit_hex(uint8_t *data, uint8_t len)
{
    for(uint8_t i=0; i<len; ++i){
        // Mask out the individual nibbles
        uint8_t high = (data[i] & 0xF0) >> 4;
        uint8_t low  = (data[i] & 0x0F);

        // Convert to char
        high += (high > 9) ? 'A'-10 : '0';
        low  += (low  > 9) ? 'A'-10 : '0';

        // Send the data
        usart_transmit_char(high);
        usart_transmit_char(low);
    }
}