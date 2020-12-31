#include "datapool.h"

namespace pmhashtable {

DataPool::DataPool(Options &opt) : arena_(opt.pm_path + opt.index_name + ".pool", opt.pool_size),
                                   manifest_(opt.pm_path + opt.index_name + ".fest") {
    std::ifstream ifs(manifest_);
    if (!ifs.is_open()) {
        // do nothing
    } else {
        // Recover
        arena_.Recover(ifs);
        ifs.close();
    }
}

DataPool::~DataPool() {
    std::ofstream ofs(manifest_);
    arena_.Save(ofs);
}

int64_t DataPool::NewNode(const std::string key, const std::string value) {
    int64_t n_offset, k_offset, v_offset;

    PoolNode *n = (PoolNode*)arena_.Allocate(sizeof(PoolNode), n_offset);
    n->key_len = key.length();
    n->value_len = value.length();

    char *k = (char*)arena_.Allocate(n->key_len, k_offset);
    char *v = (char*)arena_.Allocate(n->value_len, v_offset);

    memcpy(k, key.data(), n->key_len);
    memcpy(v, value.data(), n->value_len);

    n->key = k_offset;
    n->value = v_offset;

    arena_.Sync(k, n->key_len);
    arena_.Sync(v, n->value_len);
    arena_.Sync(n, sizeof(PoolNode));
    return n_offset;
}

void* DataPool::Translate(int64_t offset) {
    return arena_.Translate(offset);
}
}   // pmhashtable