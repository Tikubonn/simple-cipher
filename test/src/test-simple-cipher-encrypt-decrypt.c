
#include <stddef.h>
#include <stdint.h>
#include <simple-cipher/simple-cipher.h>
#include "test.h"
#include "test-simple-cipher-encrypt-decrypt.h"

static void testcase (){
  uint8_t plaintext[256];
  for (size_t index = 0; index < sizeof(plaintext); index++){
    plaintext[index] = 0;
  }
  simple_cipher cipher;
  simple_cipher_setup(0x123abc, &cipher);
  uint8_t encrypteddata[256];
  simple_cipher_encrypt_decrypt(plaintext, sizeof(plaintext), &cipher, encrypteddata);
  size_t samecount = 0;
  for (size_t index = 0; index < sizeof(encrypteddata); index++){
    samecount += encrypteddata[index] == plaintext[index];
  }
  TEST(samecount < 256, "samecount = %zu", samecount);
  simple_cipher cipher2;
  simple_cipher_setup(0x123abc, &cipher2);
  uint8_t decrypteddata[256];
  simple_cipher_encrypt_decrypt(encrypteddata, sizeof(encrypteddata), &cipher2, decrypteddata);
  for (size_t index = 0; index < sizeof(decrypteddata); index++){
    TEST(decrypteddata[index] == plaintext[index], "%u == %u", decrypteddata[index], plaintext[index]);
  }
}

static void testcase2 (){
  uint8_t plaintext[256];
  for (size_t index = 0; index < sizeof(plaintext); index++){
    plaintext[index] = index;
  }
  simple_cipher cipher;
  simple_cipher_setup(0x123abc, &cipher);
  uint8_t encrypteddata[256];
  simple_cipher_encrypt_decrypt(plaintext, sizeof(plaintext), &cipher, encrypteddata);
  size_t samecount = 0;
  for (size_t index = 0; index < sizeof(encrypteddata); index++){
    samecount += encrypteddata[index] == plaintext[index];
  }
  TEST(samecount < 256, "samecount = %zu", samecount);
  simple_cipher cipher2;
  simple_cipher_setup(0x123abc, &cipher2);
  uint8_t decrypteddata[256];
  simple_cipher_encrypt_decrypt(encrypteddata, sizeof(encrypteddata), &cipher2, decrypteddata);
  for (size_t index = 0; index < sizeof(decrypteddata); index++){
    TEST(decrypteddata[index] == plaintext[index], "%u == %u", decrypteddata[index], plaintext[index]);
  }
}

void test_simple_cipher_encrypt_decrypt (){
  testcase();
  testcase2();
}
