#ifndef PMHASHTABLE_HASHTABLE_H
#define PMHASHTABLE_HASHTABLE_H
#include "dataindex.h"
#include "datapool.h"
#include "options.h"
#include <string>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <assert.h>

namespace pmhashtable {

class HashTable {
public:
    explicit HashTable(Options& opt);
    ~HashTable();

    bool Write(const std::string key, const std::string value);
    bool Read(const std::string key, std::string* value);
    bool Delete(const std::string key);
    bool Scan(const std::string key, const int n);
    std::string Key();
    std::string Value();
    bool Valid();
    void Next();

private:
    DataPool datapool_;
    DataIndex dataindex_;

};

} // pmhashtable
#endif // PMHASHTABLE_HASHTABLE_H