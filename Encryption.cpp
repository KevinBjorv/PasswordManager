#include "Encryption.h"
#include <openssl/evp.h>

#include <iomanip>
#include <sstream>

std::string hashPassword(const std::string& password) {
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
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}