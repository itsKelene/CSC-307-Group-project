#include "PasswordHashTable.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace {
    bool isPrime(int n) {
        if (n < 2) return false;
        for (int i = 2; static_cast<long long>(i) * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int next_prime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }
}

PasswordHashTable::PasswordHashTable(int size) {
    num_items = 0;
    num_slots = (size > 0) ? size : 1;
    table = new std::vector<Entry>[num_slots];
}

PasswordHashTable::~PasswordHashTable() {
    delete[] table;
}

int PasswordHashTable::ascii_sum(const std::string &key) const {
    int sum = 0;
    for (size_t i = 0; i < key.size(); i++) {
        sum += static_cast<int>(static_cast<unsigned char>(key[i]));
    }
    return sum;
}

int PasswordHashTable::hash(const std::string &key) const {
    int string_sum = ascii_sum(key);
    return string_sum % num_slots;
}

std::string PasswordHashTable::hashPassword(const std::string &password) const {
    unsigned long h = 5381;
    for (unsigned char c : password) {
        h = ((h << 5) + h) + c;
    }

    std::stringstream ss;
    ss << std::hex << h;
    return ss.str();
}

void PasswordHashTable::grow_table() {
    std::vector<Entry>* old_table = table;
    int old_size = num_slots;

    num_items = 0;
    num_slots = next_prime(2 * old_size);
    table = new std::vector<Entry>[num_slots];

    for (int i = 0; i < old_size; i++) {
        for (size_t j = 0; j < old_table[i].size(); j++) {
            int index = hash(old_table[i][j].getUsername());
            table[index].push_back(old_table[i][j]);
            num_items++;
        }
    }

    delete[] old_table;
}

void PasswordHashTable::insert(const std::string &username, const std::string &password) {
    if ((num_items * 1.0) / num_slots >= 0.75) {
        grow_table();
    }

    std::string hashedPassword = hashPassword(password);
    int index = hash(username);
    table[index].push_back(Entry(username, hashedPassword));
    num_items++;
}

bool PasswordHashTable::search(const std::string &username) const {
    int index = hash(username);
    for (size_t i = 0; i < table[index].size(); i++) {
        if (table[index][i].getUsername() == username) {
            return true;
        }
    }
    return false;
}

bool PasswordHashTable::update(const std::string &username, const std::string &newPassword) {
    int index = hash(username);
    for (size_t i = 0; i < table[index].size(); i++) {
        if (table[index][i].getUsername() == username) {
            table[index][i].setHashedPassword(hashPassword(newPassword));
            return true;
        }
    }
    return false;
}

bool PasswordHashTable::remove(const std::string &username) {
    int index = hash(username);
    for (size_t i = 0; i < table[index].size(); i++) {
        if (table[index][i].getUsername() == username) {
            table[index].erase(table[index].begin() + i);
            num_items--;
            return true;
        }
    }
    return false;
}

bool PasswordHashTable::verifyPassword(const std::string &username, const std::string &password) const {
    int index = hash(username);
    for (size_t i = 0; i < table[index].size(); i++) {
        if (table[index][i].getUsername() == username) {
            return table[index][i].getHashedPassword() == hashPassword(password);
        }
    }
    return false;
}

void PasswordHashTable::saveToCSV(const std::string &filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Error: could not open file \"" << filename << "\" for writing.\n";
        return;
    }

    for (int index = 0; index < num_slots; index++) {
        for (size_t j = 0; j < table[index].size(); j++) {
            outFile << table[index][j].getUsername() << ","
                    << table[index][j].getHashedPassword() << "\n";
        }
    }

    outFile.close();
    std::cout << "Data saved to \"" << filename << "\".\n";
}

void PasswordHashTable::loadFromCSV(const std::string &filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cout << "Error: could not open file \"" << filename << "\" for reading.\n";
        return;
    }

    std::string line;
    int loadedCount = 0;

    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            continue;
        }

        std::string username = line.substr(0, commaPos);
        std::string hashedPassword = line.substr(commaPos + 1);

        if (username.empty()) {
            continue;
        }

        if ((num_items * 1.0) / num_slots >= 0.75) {
            grow_table();
        }

        int index = hash(username);
        table[index].push_back(Entry(username, hashedPassword));
        num_items++;
        loadedCount++;
    }

    inFile.close();
    std::cout << loadedCount << " entry(ies) loaded from \"" << filename << "\".\n";
}
