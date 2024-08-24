#pragma once 
#include <string>

std::string encrypt(const std::string& plainText, const std::string& key);
std::string decrypt(const std::string& cipherText, const std::string& key);