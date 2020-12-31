#include "dataindex.h"

namespace pmhashtable {

uint64_t DataIndex::Hash(const std::string str) {
    uint64_t hashresult[2];
    MurmurHash3_x64_128(str.c_str(), str.length(), SEED, hashresult);
    return hashresult[0];
}

DataIndex::DataIndex(Options& opt, DataPool *dp) : arena_(opt.pm_path + opt.index_name + ".index", opt.index_size),
                                                   datapool_(dp),
                                                   index_size_(opt.index_size) {}

DataIndex::~DataIndex() {}

bool DataIndex::Write(const std::string key, const std::string value) {
    uint64_t hashresult = Hash(key);
    IndexNode *in = (IndexNode*)arena_.Allocate(hashresult);
    int counter = 16;   // align with 16B

    while (in->is_valid) {
        PoolNode *pn = (PoolNode*)datapool_->Translate(in->poolnode);
        std::string k((char*)datapool_->Translate(pn->key), pn->key_len);
        if (k == key) {
            break;
        } else {
            // linear probe
            in = (IndexNode*)arena_.Allocate(hashresult + counter);
            counter += 16;
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
    int counter = 16;   // align with 16B

    while (in->is_valid) {
        PoolNode *pn = (PoolNode*)datapool_->Translate(in->poolnode);
        std::string k((char*)datapool_->Translate(pn->key), pn->key_len);
        if (k == key) {
            *value = std::string((char*)datapool_->Translate(pn->value), pn->value_len);
            return true;
        } else {
            // linear probe
            in = (IndexNode*)arena_.Allocate(hashresult + counter);
            counter += 16;
        }
    }
    return false;
}

bool DataIndex::Delete(const std::string key) {
    uint64_t hashresult = Hash(key);
    IndexNode *in = (IndexNode*)arena_.Allocate(hashresult);
    int counter = 16;   // align with 16B

    while (in->is_valid) {
        PoolNode *pn = (PoolNode*)datapool_->Translate(in->poolnode);
        std::string k((char*)datapool_->Translate(pn->key), pn->key_len);
        if (k == key) {
            in->is_valid = false;
            arena_.Sync(in, sizeof(IndexNode));
            return true;
        } else {
            in = (IndexNode*)arena_.Allocate(hashresult + counter);
            counter += 16;
        }
    }
    return false;
}

bool DataIndex::Scan(const std::string key, const int n) {
    print_pos_ = 0;
    key_in_scan_.clear();
    value_in_scan_.clear();

    uint64_t pos = 0;

    while (pos < index_size_) {
        IndexNode *in = (IndexNode*)arena_.Allocate(pos);
        if (in->is_valid) {
            PoolNode *pn = (PoolNode*)datapool_->Translate(in->poolnode);
            std::string k((char*)datapool_->Translate(pn->key), pn->key_len);

            if (k >= key) {
                int insert_pos = std::upper_bound(key_in_scan_.begin(), key_in_scan_.end(), k) - key_in_scan_.begin();
                if (insert_pos < n) {
                    key_in_scan_.insert(key_in_scan_.begin() + insert_pos, k);
                    std::string v((char*)datapool_->Translate(pn->value), pn->value_len);
                    value_in_scan_.insert(value_in_scan_.begin() + insert_pos, v);
                    if (key_in_scan_.size() > n) {
                        key_in_scan_.pop_back();
                        value_in_scan_.pop_back();
                    }
                }
            }
        }
        pos += 16;
    }

    if (key_in_scan_.size() == 0) {
        return false;
    } else {
        return true;
    }
}

std::string DataIndex::Key() {
    assert(Valid());
    return key_in_scan_[print_pos_];
}

std::string DataIndex::Value() {
    assert(Valid());
    return value_in_scan_[print_pos_];
}

bool DataIndex::Valid() {
    return print_pos_ < key_in_scan_.size();
}

void DataIndex::Next() {
    assert(Valid());
    print_pos_++;
}

}   // pmhashtable