
/**
 * @file 
 * @brief Xorlshift とバーナム暗号を組み合わせた暗号機能を提供するライブラリです。
 */

#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct simple_cipher_random {
  uint64_t seed;
} simple_cipher_random;

typedef struct simple_cipher_random8 {
  simple_cipher_random random;
  uint64_t value;
  uint_fast8_t seek;
} simple_cipher_random8;

/**
 * @brief simple-cipher の暗号機能を提供するために用いられる構造体です。
 * @note この構造体は simple_cipher_setup() 関数を用いて初期化されることが推奨されます。
 * @warning この構造体は simple_cipher_encrypt_decrypt() 関数が実行されるたびに内部の状態が変化します。そのため、暗号化の後に復号したい場合には同じ鍵を指定したインスタンスをもう一つ用意する必要があります。
 */

typedef struct simple_cipher {
  simple_cipher_random8 random8;
} simple_cipher;


/**
 * @brief simple_cipher 構造体を初期化します。
 * @param key 暗号化・復号で用いられる共通鍵です。
 * @param cipher 初期化する simple_cipher 構造体のポインタです。
 * @note この関数は必ず成功します。
 */

extern void __stdcall simple_cipher_setup (uint64_t key, simple_cipher *cipher);

/**
 * @brief 初期化済みの simple_cipher 構造体を使ってデータを暗号化・復号します。
 * @param data 暗号化・復号をするデータのポインタです。
 * @param datasize data 暗号化・復号するデータの大きさです。
 * @param cipher 初期化済みの simple_cipher 構造体のポインタです。
 * @param processeddata 暗号化・復号されたデータが書き込まれる領域のポインタです。
 * @warning processeddata が示す領域は最低でも datasize 以上の大きさでなければなりません。
 * @note 暗号化されたデータをこの関数で処理すると、復号された平文が processeddata に書き込まれます。
 * @note この関数は必ず成功します。
 */

extern void __stdcall simple_cipher_encrypt_decrypt (const void *data, size_t datasize, simple_cipher *cipher, void *processeddata);
