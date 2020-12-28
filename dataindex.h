#ifndef PMHASHTABLE_DATAINDEX_H
#define PMHASHTABLE_DATAINDEX_H
#include "arena.h"
#include "options.h"
#include "MurmurHash3.h"
#include <string>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#define SEED 0xdeadbeaf

namespace pmhashtable {

struct IndexNode {
    bool is_valid;
    int64_t realnode;
};


class DataIndex {
public:
    explicit DataIndex(Options& opt);
    ~DataIndex();

    bool Write(const std::string key, const std::string value);
    bool Read(const std::string key, std::string* value);
    bool Delete(const std::string key);

private:
    uint64_t Hash(const std::string str);
    Arena arena_;
    std::string indexinfo_;
    
};

} // pmhashtable
#endif // PMHASHTABLE_DATAINDEX_H