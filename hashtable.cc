#include "hashtable.h"

namespace pmhashtable {

HashTable::HashTable(Options &opt) : datapool_(opt),
                                     dataindex_(opt, &datapool_) {}

HashTable::~HashTable() {}

bool HashTable::Write(const std::string key, const std::string value) {
    return dataindex_.Write(key, value);
}

bool HashTable::Read(const std::string key, std::string *value) {
    return dataindex_.Read(key, value);
}

bool HashTable::Delete(const std::string key) {
    return dataindex_.Delete(key);
}

bool HashTable::Scan(const std::string key, const int n) {
    return dataindex_.Scan(key, n);
}

std::string HashTable::Key() {
    return dataindex_.Key();
}

std::string HashTable::Value() {
    return dataindex_.Value();
}

bool HashTable::Valid() {
    return dataindex_.Valid();
}

void HashTable::Next() {
    dataindex_.Next();
}

}   // pmhashtable