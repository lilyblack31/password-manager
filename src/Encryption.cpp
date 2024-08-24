#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include "Encryption.h"

using namespace std;

const int AES_KEY_LENGTH = 256;
const int AES_BLOCK_SIZE = 128;

string encrypt(const string& plainText, const string& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    unsigned char iv[AES_BLOCK_SIZE / 8];
    unsigned char keyData[AES_KEY_LENGTH / 8];

    if (!RAND_bytes(iv, sizeof(iv))) {
        cerr << "Error generating IV" << endl;
        return "";
    }

    if (!PKCS5_PBKDF2_HMAC_SHA1(key.c_str(), key.length(), iv, sizeof(iv), 10000, AES_KEY_LENGTH / 8, keyData)) {
        cerr << "Error deriving key" << endl;
        return "";
    }

    vector<unsigned char> cipherText(plainText.size() + AES_BLOCK_SIZE);

    int len;
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, keyData, iv)) {
        cerr << "Error initializing encryption" << endl;
        return "";
    }

    if (1 != EVP_EncryptUpdate(ctx, cipherText.data(), &len, (unsigned char*)plainText.c_str(), plainText.size())) {
        cerr << "Error during encryption" << endl;
        return "";
    }

    int cipherTextLen = len;

    if (1 != EVP_EncryptFinal_ex(ctx, cipherText.data() + len, &len)) {
        cerr << "Error during final encryption step" << endl;
        return "";
    }

    cipherTextLen += len;
    cipherText.resize(cipherTextLen);

    string result(reinterpret_cast<const char*>(cipherText.data()), cipherText.size());
    result.insert(0, string(reinterpret_cast<const char*>(iv), sizeof(iv))); 

    EVP_CIPHER_CTX_free(ctx);

    return result;
}

string decrypt(const string& cipherText, const string& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    unsigned char iv[AES_BLOCK_SIZE / 8];
    unsigned char keyData[AES_KEY_LENGTH / 8];

    memcpy(iv, cipherText.c_str(), sizeof(iv));

    if (!PKCS5_PBKDF2_HMAC_SHA1(key.c_str(), key.length(), iv, sizeof(iv), 10000, AES_KEY_LENGTH / 8, keyData)) {
        cerr << "Error deriving key" << endl;
        return "";
    }

    vector<unsigned char> plainText(cipherText.size());

    int len;
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, keyData, iv)) {
        cerr << "Error initializing decryption" << endl;
        return "";
    }

    if (1 != EVP_DecryptUpdate(ctx, plainText.data(), &len, (unsigned char*)cipherText.c_str() + sizeof(iv), cipherText.size() - sizeof(iv))) {
        cerr << "Error during decryption" << endl;
        return "";
    }

    int plainTextLen = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plainText.data() + len, &len)) {
        cerr << "Error during final decryption step" << endl;
        return "";
    }

    plainTextLen += len;
    plainText.resize(plainTextLen);

    string result(reinterpret_cast<const char*>(plainText.data()), plainText.size());

    EVP_CIPHER_CTX_free(ctx);

    return result;
}