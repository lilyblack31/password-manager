#include <iostream>
#include <string.h>
#include "PasswordManager.h"
#include "PasswordGenerator.h"
#include "UserAuth.h"
#include "utils.h"

using namespace std;

int main() {

    string storedLoginPassword = hashPassword("myLoginPassword");
    string storedMasterPassword = hashPassword("myMasterPassword");

    if (!login(storedLoginPassword)) {
        return 1;
    }

    string masterKey;
    cout << "Enter your master key: ";
    cin >> masterKey;

    if (!validateMasterPassword(masterKey, storedMasterPassword)) {
        cout << "Invalid master key." << endl;
        return 1;
    }

    PasswordManager manager(masterKey);
    manager.loadPasswordsFromFile();

    PasswordGenerator generator;

    while (true) {
        cout << "1. Add Password\n2. View Passwords\n3. Update Password\n4. Delete Password\n5. Generate Password\n6. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string username, password, category, description;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter description: ";
            cin >> description;

            manager.addPassword(Password(username, hashPassword(password), category, description));
        } else if (choice == 2) {
            string username;
            cout << "Enter username: ";
            cin >> username;
            cout << "Password: " << manager.viewPassword(username) << endl;
        } else if (choice == 3) {
            string username, newPassword;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter new password: ";
            cin >> newPassword;

            manager.updatePassword(username, newPassword);
        } else if (choice == 4) {
            string username;
            cout << "Enter username: ";
            cin >> username;

            manager.deletePassword(username);
        } else if (choice == 5) {
            int length;
            cout << "Enter password length: ";
            cin >> length;
            cout << "Generated Password: " << generator.generatePassword(length) << endl;
        } else if (choice == 6) {
            break;
        }
    }

    return 0;
}