#ifndef PMHASHTABLE_DATAINDEX_H
#define PMHASHTABLE_DATAINDEX_H
#include "arena.h"
#include "options.h"
#include "datapool.h"
#include "MurmurHash3.h"
#include <string>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>
#define SEED 0xdeadbeaf

namespace pmhashtable {

struct IndexNode {
    bool is_valid;
    int64_t poolnode;
};


class DataIndex {
public:
    explicit DataIndex(Options& opt, DataPool *dp);
    ~DataIndex();

    bool Write(const std::string key, const std::string value);
    bool Read(const std::string key, std::string* value);
    bool Delete(const std::string key);
    bool Scan(const std::string key, const int n);
    std::string Key();
    std::string Value();
    bool Valid();
    void Next();

private:
    uint64_t Hash(const std::string str);
    size_t index_size_;
    Arena arena_;
    DataPool *datapool_;

    int print_pos_;
    std::vector<std::string> key_in_scan_;
    std::vector<std::string> value_in_scan_;
};

} // pmhashtable
#endif // PMHASHTABLE_DATAINDEX_H