#include "index.hpp"

//super basic, just keep all stuff in memory
//

class BruteForceIndex : public Index {
    public:
        BruteForceIndex(Dimension dim, DistanceMetric metric): dim_(dim), metric_(metric) {}
        //want to be able to add, delete (maybe), and search
         int add(VectorID id, const std::vector<float>& v) {

        }


    private:
        Dimension dim_;
        DistanceMetric metric_;
        std::unordered_map<VectorID, std::vector<float>> data_; //we store here

        float distance(const std::vector<float>& a, const std::vector<float>& b) const {
            switch (metric_) {
            case DistanceMetric::L2:     return l2_distance(a, b);
            case DistanceMetric::Cosine: return cosine_distance(a, b);
            default:
                throw std::runtime_error("unknown metric");
            }
        }

        static float l2_distance(const std::vector<float>& a,
                             const std::vector<float>& b)
        {
            float sum = 0.0f;
            for (std::size_t i = 0; i < a.size(); ++i) {
                float d = a[i] - b[i];
                sum += d * d;
            }
            return std::sqrt(sum);
        }

    static float cosine_distance(const std::vector<float>& a,
                                 const std::vector<float>& b)
    {
        float dot = 0.0f, na = 0.0f, nb = 0.0f;
        for (std::size_t i = 0; i < a.size(); ++i) {
            dot += a[i] * b[i];
            na  += a[i] * a[i];
            nb  += b[i] * b[i];
        }
        float denom = std::sqrt(na) * std::sqrt(nb);
        if (denom == 0.0f) return 1.0f; // arbitrary
        float cosine = dot / denom;
        return 1.0f - cosine; // smaller = more similar
    }
};


}