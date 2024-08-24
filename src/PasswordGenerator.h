#pragma once
#include <string>
#include <cstdlib>
#include <ctime>

class PasswordGenerator {
    public:
        PasswordGenerator() { srand(time(0)); }

        std::string generatePassword(int length);
};