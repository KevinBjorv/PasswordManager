#pragma once

#include <string>
#include <vector>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/kdf.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>


namespace crypt {
	std::string encrypt(const std::string& plaintext, const std::string& password, const std::vector<unsigned char>& salt); // Hashes the password

	std::string decrypt(const std::string& ciphertext, const std::string& password, const std::vector<unsigned char>& salt); // Decrypts the password

	std::string hashPassword(const std::string& password); // Hashes the password

	std::vector<unsigned char> deriveKey(const std::string& password, const std::vector<unsigned char> & salt, int keyLength = 32); // Derives a key from a password

	std::string base64Encode(const std::string& data);
	std::string base64Decode(const std::string& base64Data);

	int calcDecodeLength(const std::string& base64);
};

// Path: Encryption.h