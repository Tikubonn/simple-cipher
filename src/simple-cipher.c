
#include <stddef.h>
#include <stdint.h>
#include "simple-cipher.h"

static inline void simple_cipher_random_setup (uint64_t seed, simple_cipher_random *random){
  random->seed = seed;
}

static inline uint64_t simple_cipher_random_next (simple_cipher_random *random){
  uint64_t n = random->seed;
  n ^= n << 13;
  n ^= n >> 7;
  n ^= n << 17;
  random->seed = n;
  return n;
}

static inline void simple_cipher_random8_setup (uint64_t seed, simple_cipher_random8 *random){
  simple_cipher_random_setup(seed, &(random->random));
  random->value = 0;
  random->seek = 64;
}

static inline uint8_t simple_cipher_random8_next (simple_cipher_random8 *random){
  if (56 < random->seek){
    random->value = simple_cipher_random_next(&(random->random));
    random->seek = 0;
  }
  uint8_t n = (random->value >> random->seek) & 0xff;
  random->seek += 8;
  return n;
}

static inline void simple_cipher_random8_next_seed (simple_cipher_random8 *random){
  simple_cipher_random_next(&(random->random));
  random->value = 0;
  random->seek = 64;
}

#define SHUFFLE_COUNT 11

void __stdcall simple_cipher_setup (uint64_t key, simple_cipher *cipher){
  simple_cipher_random8_setup(key, &(cipher->random8));
  for (size_t i = 0; i < SHUFFLE_COUNT; i++){
    simple_cipher_random8_next_seed(&(cipher->random8));
  }
}

void __stdcall simple_cipher_encrypt_decrypt (const void *data, size_t datasize, simple_cipher *cipher, void *processeddata){
  for (size_t i = 0; i < datasize; i++){
    ((uint8_t*)processeddata)[i] = ((uint8_t*)data)[i] ^ simple_cipher_random8_next(&(cipher->random8));
  }
}
