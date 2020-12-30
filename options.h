#ifndef PMHASHTABLE_OPTIONS_H
#define PMHASHTABLE_OPTIONS_H
#include <string>

namespace pmhashtable {

class Options {
public:
    Options() {}
    ~Options() {}

    std::string pm_path = "/mnt/persist-memory/pmem_fs_lhd/";

    std::string index_name = "hashtable";

    size_t index_size = 8L * 1024 * 1024 * 1024; // data index size

    size_t pool_size = 72L * 1024 * 1024 * 1024; // data pool size
};

} // pmhashtable
#endif // PMHASHTABLE_OPTIONS_H