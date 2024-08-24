#include <iostream>
#include "PasswordGenerator.h"

using namespace std;

string PasswordGenerator::generatePassword(int length) {
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    string password;

    for (int i = 0; i < length; ++i) {
        password += characters[rand() % characters.length()];
    }

    return password;
}