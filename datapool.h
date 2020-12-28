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

private:
    Arena arena_;
    
};

} // pmhashtable
#endif // PMHASHTABLE_DATAPOOL_H