#ifndef PASSWORD_HASH_TABLE_H
#define PASSWORD_HASH_TABLE_H

#include <string>
#include <vector>
#include "Entry.h"

class PasswordHashTable {
private:
    std::vector<Entry>* table;
    int num_items;
    int num_slots;

    int ascii_sum(const std::string &key) const;
    int hash(const std::string &key) const;
    void grow_table();
    std::string hashPassword(const std::string &password) const;

public:
    explicit PasswordHashTable(int size = 211);
    ~PasswordHashTable();

    PasswordHashTable(const PasswordHashTable&) = delete;
    PasswordHashTable& operator=(const PasswordHashTable&) = delete;

    void insert(const std::string &username, const std::string &password);
    bool search(const std::string &username) const;
    bool update(const std::string &username, const std::string &newPassword);
    bool remove(const std::string &username);
    bool verifyPassword(const std::string &username, const std::string &password) const;
    void saveToCSV(const std::string &filename) const;
    void loadFromCSV(const std::string &filename);
};

#endif // PASSWORD_HASH_TABLE_H
