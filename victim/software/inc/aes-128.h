#ifndef AES_128_H
#define AES_128_H

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

#define AES_KEYSIZE   16
#define AES_KEYWORDS   4
#define AES_ROUNDS    10
#define AES_BLOCKSIZE 16
#define AES_BLOCKDIM   4

// Round constants per (https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197-upd1.pdf pp.17)
extern const uint8_t RCON[10];

//=================================================================================================
// TYPE: aes_block_t
//   Representation for an aes-128 block. Allows for bytewise or matrix indexing.
//=================================================================================================
typedef union aes_block_t {
    uint8_t byte_vector[AES_BLOCKSIZE];                 // For byte   ops (SUB_BYTES, ADD_KEY)
    uint8_t byte_matrix[AES_BLOCKDIM][AES_BLOCKDIM];    // For matrix ops (MIX_COLS, SHIFT_ROWS)
} aes_block_t;

//=================================================================================================
// TYPE: aes_key_t
//   Representation for an aes-128 key. Note that initial round key is the given cipherkey.
//=================================================================================================
typedef struct aes_key_t {
    uint8_t roundKeys[AES_ROUNDS+1][AES_KEYSIZE];
} aes_key_t;

//=================================================================================================
// Standardized per FIPS 197 (https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197-upd1.pdf pp.14)
//=================================================================================================
extern const uint8_t SBOX[256];

//=================================================================================================
// Standardized per FIPS 197 (https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197-upd1.pdf pp.23)
//=================================================================================================
extern const uint8_t INVERSE_SBOX[256];

//=================================================================================================
// HELPER FUNCTIONS
//=================================================================================================

void xor_word(uint8_t *result, uint8_t *word1, uint8_t *word2);

void sub_word(uint8_t *word);

void rot_word(uint8_t *word);
 
void generate_round_keys(aes_key_t *cipherKey);

uint8_t galois_multiply(uint8_t operand1, uint8_t operand2);

void signal_attacker(void);

//=================================================================================================
// INTERNAL FUNCTIONS
//=================================================================================================

void sub_bytes(aes_block_t *block);

void shift_rows(aes_block_t *block);

void mix_columns(aes_block_t *block, uint8_t round);

void add_round_key(aes_block_t *block, uint8_t *roundKey);

//=================================================================================================
// EXTERNAL FUNCTIONS
//=================================================================================================

void init_aes_key(aes_key_t *aes_key, const uint8_t *key);

uint8_t* encrypt(uint8_t *plainText, aes_key_t *cipherKey);

void decrypt(uint8_t *cipherText, aes_key_t *cipherKey);

#endif 