#include <iostream>
#include <vector>

struct VectorLocation {
    std::uint32_t segment_id;
    std::uint64_t offset_bytes;

};



//disk stuff
//allocate new segment when current is full
//append new vectors to segfile
//read back to memory when needed
//wanna map VectorID -> (segment_id, offset)