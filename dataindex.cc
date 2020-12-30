#include "dataindex.h"

namespace pmhashtable {

uint64_t DataIndex::Hash(const std::string str) {
    uint64_t hashresult[2];
    MurmurHash3_x64_128(str.c_str(), str.length(), SEED, hashresult);
    return hashresult[0];
}

DataIndex::DataIndex(Options& opt, DataPool *dp) : arena_(opt.pm_path + opt.index_name + ".index", opt.index_size),
                                                   datapool_(dp) {}

DataIndex::~DataIndex() {}

bool DataIndex::Write(const std::string key, const std::string value) {
    uint64_t hashresult = Hash(key);
    IndexNode *in = (IndexNode*)arena_.Allocate(hashresult);
    int counter = 32;   // align with 32B

    while (in->is_valid) {
        PoolNode *pn = (PoolNode*)datapool_->Translate(in->poolnode);
        std::string k((char*)datapool_->Translate(pn->key), pn->key_len);
        if (k == key) {
            break;
        } else {
            in = (IndexNode*)arena_.Allocate(hashresult + counter);
            counter += 32;
        }
    }

    int64_t pos_in_pool = datapool_->NewNode(key, value);
    in->poolnode = pos_in_pool;
    in->is_valid = true;

    arena_.Sync(in, sizeof(IndexNode));
    return true;
}

bool DataIndex::Read(const std::string key, std::string* value) {
    uint64_t hashresult = Hash(key);
    IndexNode *in = (IndexNode*)arena_.Allocate(hashresult);
    int counter = 32;   // align with 32B

    while (in->is_valid) {
        PoolNode *pn = (PoolNode*)datapool_->Translate(in->poolnode);
        std::string k((char*)datapool_->Translate(pn->key), pn->key_len);
        if (k == key) {
            *value = std::string((char*)datapool_->Translate(pn->value), pn->value_len);
            return true;
        } else {
            in = (IndexNode*)arena_.Allocate(hashresult + counter);
            counter += 32;
        }
    }
    return false;
}

bool DataIndex::Delete(const std::string key) {
    uint64_t hashresult = Hash(key);
    IndexNode *in = (IndexNode*)arena_.Allocate(hashresult);
    int counter = 32;   // align with 32B

    while (in->is_valid) {
        PoolNode *pn = (PoolNode*)datapool_->Translate(in->poolnode);
        std::string k((char*)datapool_->Translate(pn->key), pn->key_len);
        if (k == key) {
            in->is_valid = false;
            return true;
        } else {
            in = (IndexNode*)arena_.Allocate(hashresult + counter);
            counter += 32;
        }
    }
    return false;
}
}   // pmhashtable