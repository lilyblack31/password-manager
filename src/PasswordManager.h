#pragma once
#include <vector>
#include <string>
#include "Password.h"
#include "Encryption.h"

class PasswordManager {
    
    private:
        std::vector<Password> passwords;
        std::string encryptedFilePath = "passwords.dat";
        std::string masterKey;
    
    public: 
        PasswordManager(const std::string& mk) : masterKey(mk) {}

        void addPassword(const Password& p);
        std::string viewPassword(const std::string& username);
        void updatePassword(const std::string& username, const std::string& newPassword);
        void deletePassword(const std::string& username);

        void loadPasswordsFromFile();
        void savePasswordsToFile();

};