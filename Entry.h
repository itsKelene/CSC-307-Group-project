#ifndef ENTRY_H
#define ENTRY_H

#include <string>

class Entry {
private:
    std::string username;
    std::string hashedPassword;

public:
    Entry() : username(""), hashedPassword("") {}

    Entry(const std::string &username, const std::string &hashedPassword)
        : username(username), hashedPassword(hashedPassword) {}

    std::string getUsername() const {
        return username;
    }

    std::string getHashedPassword() const {
        return hashedPassword;
    }

    void setHashedPassword(const std::string &newHash) {
        hashedPassword = newHash;
    }
};

#endif // ENTRY_H
