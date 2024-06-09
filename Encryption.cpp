#include "Encryption.h"
#include <iomanip>
#include <sstream>
#include <vector>

namespace crypt {
    std::string crypt::encrypt(const std::string& plaintext, const std::string& password, const std::vector<unsigned char>& salt) {
        const int keyLen = 32;  // Key length for AES-256
        std::vector<unsigned char> key(keyLen);
        std::vector<unsigned char> iv(EVP_MAX_IV_LENGTH);
        std::vector<unsigned char> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
        int outlen1, outlen2;

        // Derive the key using PBKDF2
        if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), salt.data(), salt.size(),
            10000, EVP_sha256(), keyLen, key.data())) {
            throw std::runtime_error("Key derivation failed.");
        }

        // Generate a random IV
        RAND_bytes(iv.data(), iv.size());

        // Initialize the context for encryption
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data());
        EVP_EncryptUpdate(ctx, ciphertext.data(), &outlen1, reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size());
        EVP_EncryptFinal_ex(ctx, ciphertext.data() + outlen1, &outlen2);
        EVP_CIPHER_CTX_free(ctx);

        // Adjust the size of the ciphertext
        ciphertext.resize(outlen1 + outlen2);
        // Append the IV to the beginning of the ciphertext for use in decryption
        ciphertext.insert(ciphertext.begin(), iv.begin(), iv.end());

        // Convert the ciphertext to a string before returning
        return std::string(ciphertext.begin(), ciphertext.end());
    }

    std::string crypt::decrypt(const std::string& ciphertext, const std::string& password, const std::vector<unsigned char>& salt) {
        if (ciphertext.size() < EVP_MAX_IV_LENGTH) {
            throw std::runtime_error("Ciphertext too short");
        }

        const int keyLen = 32;  // Key length for AES-256
        std::vector<unsigned char> key(keyLen);
        std::vector<unsigned char> iv(EVP_MAX_IV_LENGTH);
        std::vector<unsigned char> plaintext(ciphertext.size() - EVP_MAX_IV_LENGTH);
        int outlen1, outlen2;

        // Extract the IV from the beginning of the ciphertext
        std::copy_n(ciphertext.begin(), EVP_MAX_IV_LENGTH, iv.begin());

        // Derive the key using PBKDF2
        if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), salt.data(), salt.size(),
            10000, EVP_sha256(), keyLen, key.data())) {
            throw std::runtime_error("Key derivation failed.");
        }

        // Initialize the context for decryption
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data());
        EVP_DecryptUpdate(ctx, plaintext.data(), &outlen1, reinterpret_cast<const unsigned char*>(ciphertext.data()) + EVP_MAX_IV_LENGTH, ciphertext.size() - EVP_MAX_IV_LENGTH);
        if (EVP_DecryptFinal_ex(ctx, plaintext.data() + outlen1, &outlen2) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Decryption failed.");
        }
        EVP_CIPHER_CTX_free(ctx);

        // Adjust the size of the plaintext
        plaintext.resize(outlen1 + outlen2);

        // Convert the plaintext to a string before returning
        return std::string(plaintext.begin(), plaintext.end());
    }

	std::string crypt::hashPassword(const std::string& password) {
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int lengthOfHash = 0;

        EVP_MD_CTX* context = EVP_MD_CTX_new();
        if (context == nullptr) {
            // Handle error
            return "";
        }

        if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
            // Handle error
            EVP_MD_CTX_free(context);
            return "";
        }

        if (EVP_DigestUpdate(context, password.c_str(), password.size()) != 1) {
            // Handle error
            EVP_MD_CTX_free(context);
            return "";
        }

        if (EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1) {
            // Handle error
            EVP_MD_CTX_free(context);
            return "";
        }

        EVP_MD_CTX_free(context);

        std::stringstream ss;
        for (unsigned int i = 0; i < lengthOfHash; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        return ss.str();
	}

	std::vector<unsigned char> crypt::deriveKey(const std::string& password, const std::vector<unsigned char>& salt, int keyLength) {
		std::vector<unsigned char> key(keyLength, 0);
		const EVP_MD* md = EVP_sha256();
		
        if (!EVP_PBE_scrypt(password.c_str(), password.length(), salt.data(), salt.size(), 
            16384, 8, 1, 0, key.data(), key.size())) {
			throw std::runtime_error("Failed to derive key");
        }
		return key;
	}

    std::string crypt::base64Encode(const std::string& data) {
        BIO* bio, * b64;
        BUF_MEM* bufferPtr;

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new(BIO_s_mem());
        bio = BIO_push(b64, bio);

        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);  // Tell base64 BIO to NOT append newlines
        BIO_write(bio, data.c_str(), data.length());
        BIO_flush(bio);
        BIO_get_mem_ptr(bio, &bufferPtr);
        BIO_set_close(bio, BIO_NOCLOSE);
        BIO_free_all(bio);

        std::string result(bufferPtr->data, bufferPtr->length);
        BUF_MEM_free(bufferPtr);
        return result;
    }

    std::string crypt::base64Decode(const std::string& base64) {
        BIO* bio, * b64;
        int decodeLen = calcDecodeLength(base64);
        std::vector<unsigned char> buffer(decodeLen);

        bio = BIO_new_mem_buf(base64.data(), -1);
        b64 = BIO_new(BIO_f_base64());
        bio = BIO_push(b64, bio);

        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
        int length = BIO_read(bio, buffer.data(), base64.size());
        BIO_free_all(bio);

        return std::string(buffer.begin(), buffer.begin() + length);
    }

    int crypt::calcDecodeLength(const std::string& base64) {
        int len = base64.size();
        int padding = 0;

        if (base64[len - 1] == '=' && base64[len - 2] == '=') //last two chars are =
            padding = 2;
        else if (base64[len - 1] == '=') //last char is =
            padding = 1;

        return (len * 3) / 4 - padding;
    }
}

// Path: Encryption.cpp