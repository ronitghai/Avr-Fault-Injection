#include "aes-128.h"
#include <stdio.h>

const char lookup[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

int main(int argc, char* argv[])
{
    const uint8_t cipherKey[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    aes_key_t keyChain;

    init_aes_key(&keyChain, cipherKey);

    for(uint8_t j=0; j<AES_ROUNDS+1; ++j){
        printf("Round %u: ", j);
        for(uint8_t i=0; i<AES_KEYSIZE; ++i){
            printf("%c%c", lookup[keyChain.roundKeys[j][i]>>4], lookup[keyChain.roundKeys[j][i] & 0x0F]);
        }
        printf("\n");
    }

    uint8_t sample[] = { 0x2, 0xa0, 0x94, 0xc3, 0x26, 0x72, 0x51, 0xdb, 0x74, 0xe0, 0x4, 0x55, 0x5a, 0xbe, 0x93, 0x6b };
    encrypt(sample, &keyChain);
    for(uint8_t j=0; j<AES_BLOCKSIZE; ++j){
        printf("%c%c", lookup[sample[j]>>4], lookup[sample[j] & 0x0F]);
    }
    printf("\n");

    return 0;
}