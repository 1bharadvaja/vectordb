#include <iostream>
#include <vector>

struct VectorLocation {
    std::uint32_t segment_id;
    std::uint64_t offset_bytes;

};

class StorageEngine {
    public:

        StorageEngine(const std::string& path);
        VectorLocation append_vector(std::vector<float>& vec);
        std::vector<float> read_vector(const VectorLocation& loc) const;

        void flush();
    private:

        std::list<VectorLocation> buf_cache; //may want to keep a buffer cache to coalesce writes, not urgent to implement
        std::unordered_map<VectorID, std::vector<float>> mapping;
}


//disk stuff
//allocate new segment when current is full
//append new vectors to segfile
//read back to memory when needed
//wanna map VectorID -> (segment_id, offset)