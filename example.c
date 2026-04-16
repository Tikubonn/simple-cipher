
#include <stdio.h>
#include <simple-cipher/simple-cipher.h>

#define PLAINTEXT "Hello!"

int main (){

  char encrypted[sizeof(PLAINTEXT)] = {0};
  simple_cipher cipher;
  simple_cipher_setup(0x123, &cipher);
  simple_cipher_encrypt_decrypt(PLAINTEXT, sizeof(PLAINTEXT) -1, &cipher, encrypted);
  printf("encrypted=%s\n", encrypted);
  
  char decrypted[sizeof(PLAINTEXT)] = {0};
  simple_cipher cipher2;
  simple_cipher_setup(0x123, &cipher2);
  simple_cipher_encrypt_decrypt(encrypted, sizeof(encrypted) -1, &cipher2, decrypted);
  printf("decrypted=%s\n", decrypted); 
  
  return 0;

}
