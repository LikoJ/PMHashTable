#include <iostream>
#include <string>
#include "hashtable.h"
#define KEY_NUM 20
int main() {
    pmhashtable::Options opt;
    pmhashtable::HashTable *ht = new pmhashtable::HashTable(opt);
    std::string key, value;

    std::cout << "--------Insert--------" << std::endl;
    for (int i = 0; i < KEY_NUM; i++, i++) {
        key = "k";
        key += std::to_string(i);
        value = "v";
        value += std::to_string(i);
        ht->Write(key, value);
        std::cout << key << ": " << value << std::endl;
    }

    std::cout << "---------Read---------" << std::endl;
    for (int i = 0; i < KEY_NUM; i++, i++) {
        key = "k";
        key += std::to_string(i);
        if (ht->Read(key, &value)) {
            std::cout << key << ": " << value << std::endl;
        } else {
            std::cout << key << ": not found!" << std::endl;
        }
    }

    std::cout << "--------Insert--------" << std::endl;
    for (int i = 1; i < KEY_NUM; i++, i++) {
        key = "k";
        key += std::to_string(i);
        value = "v";
        value += std::to_string(i);
        ht->Write(key, value);
        std::cout << key << ": " << value << std::endl;
    }

    std::cout << "---------Read---------" << std::endl;
    for (int i = 0; i < KEY_NUM; i++) {
        key = "k";
        key += std::to_string(i);
        if (ht->Read(key, &value)) {
            std::cout << key << ": " << value << std::endl;
        } else {
            std::cout << key << ": not found!" << std::endl;
        }
    }

    // not found
    key = "k";
    if (ht->Read(key, &value)) {
        std::cout << key << ": " << value << std::endl;
    } else {
        std::cout << key << ": not found!" << std::endl;
    }

    std::cout << "--------Update--------" << std::endl;
    for (int i = 0; i < KEY_NUM; i += 3) {
        key = "k";
        key += std::to_string(i);
        value = "u";
        value += std::to_string(i);
        ht->Write(key, value);
        std::cout << key << ": " << value << std::endl;
    }
    
    std::cout << "---------Read---------" << std::endl;
    for (int i = 0; i < KEY_NUM; i++) {
        key = "k";
        key += std::to_string(i);
        if (ht->Read(key, &value)) {
            std::cout << key << ": " << value << std::endl;
        } else {
            std::cout << key << ": not found!" << std::endl;
        }
    }

    /*
    std::cout << "-Scan-from-k20-to-k50-" << std::endl;
    pmhashtable::Iterator *it = ht->NewIterator();
    key = "k";
    key += std::to_string(20);
    for (it->Seek(key); it->Valid(); it->Next()) {
        key = it->Key();
        value = it->Value();
        if (key > "k50") {
            break;
        }
        std::cout << key << ": " << value << std::endl;
    }

    delete it;*/

    std::cout << "-Delete-from-k0-to-k5-" << std::endl;
    for (int i = 0; i < 6; i++) {
        key = "k";
        key += std::to_string(i);
        ht->Delete(key);
        std::cout << key << ": " << "delete" << std::endl;
    }

    std::cout << "---------Read---------" << std::endl;
    for (int i = 0; i < KEY_NUM; i++) {
        key = "k";
        key += std::to_string(i);
        if (ht->Read(key, &value)) {
            std::cout << key << ": " << value << std::endl;
        } else {
            std::cout << key << ": not found!" << std::endl;
        }
    }

    std::cout << "--------Reopen--------" << std::endl;
    delete ht;
    ht = new pmhashtable::HashTable(opt);
    std::cout << "---------Read---------" << std::endl;
    for (int i = 0; i < KEY_NUM; i++) {
        key = "k";
        key += std::to_string(i);
        if (ht->Read(key, &value)) {
            std::cout << key << ": " << value << std::endl;
        } else {
            std::cout << key << ": not found!" << std::endl;
        }
    }
    delete ht;
    return 0;
}