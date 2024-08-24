#pragma once
#include <string>

bool login(const std::string& storedLoginPassword);
bool validateMasterPassword(const std::string& inputPassword, const std::string& storedHashedMasterPassword);
