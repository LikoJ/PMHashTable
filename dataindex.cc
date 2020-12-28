#include "dataindex.h"

namespace pmhashtable {

uint64_t DataIndex::Hash(const std::string str) {
    uint64_t hashresult[2];
    MurmurHash3_x64_128(str.c_str(), str.length(), SEED, hashresult);
    return hashresult[0];
}

DataIndex::DataIndex(Options& opt) : arena_(opt.pm_path + opt.index_name + ".index", opt.index_size) {}

DataIndex::~DataIndex() {}
}   // pmhashtable