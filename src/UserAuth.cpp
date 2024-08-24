#include <iostream>
#include "utils.h"
#include "UserAuth.h"

using namespace std;

bool login(const string& storedLoginPassword) {
    string inputPassword;
    cout << "Enter your login password: ";
    cin >> inputPassword;

    if (hashPassword(inputPassword) == storedLoginPassword) {
        return true;
    } else {
        cout << "Incorrect password" << endl;
        return false;
    }
}

bool validateMasterPassword(const string& inputPassword, const string& storedHashedMasterPassword) {
    return hashPassword(inputPassword) == storedHashedMasterPassword;
}