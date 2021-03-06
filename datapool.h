#ifndef PMHASHTABLE_DATAPOOL_H
#define PMHASHTABLE_DATAPOOL_H
#include "arena.h"
#include "options.h"
#include <string>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <assert.h>

namespace pmhashtable {

struct PoolNode {
    int64_t key;
    size_t key_len;
    int64_t value;
    size_t value_len;
};

class DataPool {
public:
    explicit DataPool(Options &opt);
    ~DataPool();

    int64_t NewNode(const std::string key, const std::string value);
    void* Translate(int64_t offset);

private:
    Arena arena_;
    std::string manifest_;
    
};

} // pmhashtable
#endif // PMHASHTABLE_DATAPOOL_H