#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace vectordb {
    using VectorID = std::uint64_t;
    using Dimension = std::uint32_t;

    struct Entry {
        VectorID id;
        std::vector<float> vector;
        std::unordered_map<std::string, std::string> columns;
    };

    enum class DistanceMetric {
        L2, 
        Cosine
    };


}

