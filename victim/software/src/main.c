#include "aes-128.h"
#include "usart.h"

int main(int argc, char* argv[])
{
    const uint8_t cipherKey[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    aes_key_t keyChain;
    init_aes_key(&keyChain, cipherKey);
    
    usart_init(1800);
    DDRD |= (1<<PD2);
    
    uint8_t trace[AES_BLOCKSIZE] = { 0 };
    encrypt(trace, &keyChain);

    usart_transmit_hex(trace, AES_BLOCKSIZE);
    usart_transmit_char('\r');
    usart_transmit_char('\n');

    return 0;
}