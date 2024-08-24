#pragma once
#include <string>

class Password {
    public:
        std::string username;
        std::string hashedPassword;
        std::string category;
        std::string description;

        Password(std::string u, std::string hp, std::string c, std::string d) : username(u), hashedPassword(hp), category(c), description(d) {}

        std::string getUsername() const { 
            return username; 
        }

        std::string getHashedPassword() const { 
            return hashedPassword; 
        }

        std::string getCategory() const { 
            return category; 
        }

        std::string getDescription() const { 
            return description; 
        }
};