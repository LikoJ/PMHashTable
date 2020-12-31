#include <iostream>
#include <string>
#include "hashtable.h"
#define KEY_NUM 50
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

    
    std::cout << "-Scan-from-k1-total-10-" << std::endl;
    key = "k";
    key += std::to_string(1);
    ht->Scan(key, 10);
    while (ht->Valid()){
        key = ht->Key();
        value = ht->Value();
        std::cout << key << ": " << value << std::endl;
        ht->Next();
    }

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