#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "PasswordManager.h"
#include "utils.h"

using namespace std;

void PasswordManager::addPassword(const Password& p) {
    passwords.push_back(p);
    savePasswordsToFile();
}

string PasswordManager::viewPassword(const string& username) {
    for (const auto& p : passwords) {
        if (p.username == username) {
            return p.getHashedPassword();
        }
    }
    return "Password not found";
}

void PasswordManager::updatePassword(const string& username, const string& newPassword) {
    for (auto& p : passwords) {
        if (p.username == username) {
            p.hashedPassword = hashPassword(newPassword);
            savePasswordsToFile();
            return;
        }
    }
    cout << "Password not found" << endl;
}

void PasswordManager::deletePassword(const string& username) {
    auto newEnd = remove_if(passwords.begin(), passwords.end(),
                                 [&](const Password& p) { return p.getUsername() == username; });
    
    if (newEnd != passwords.end()) {
        passwords.erase(newEnd, passwords.end());
        savePasswordsToFile();
    } else {
        cout << "Password not found." << endl;
    }
}

void PasswordManager::loadPasswordsFromFile() {
    ifstream file(encryptedFilePath, ios::binary);
    if (!file.is_open()) return;

    string encryptedData((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    string decryptedData = decrypt(encryptedData, masterKey);

    file.close();
}

void PasswordManager::savePasswordsToFile(){
    ofstream file(encryptedFilePath, ios::binary);
    if (!file.is_open()) return;

    string serializedData;
    for (const auto& p : passwords) {
        serializedData += p.getUsername() + "|" + p.getHashedPassword() + "|" + p.getCategory() + "|" + p.getDescription() + "\n";
    }

    string encryptedData = encrypt(serializedData, masterKey);
    file.write(encryptedData.c_str(), encryptedData.size());
    
    file.close();
}