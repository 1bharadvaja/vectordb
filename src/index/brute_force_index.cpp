#include "index.hpp"
#include <queue>

//super basic, just keep all stuff in memory
//



class BruteForceIndex : public Index {
    public:
        BruteForceIndex(Dimension dim, DistanceMetric metric): dim_(dim), metric_(metric) {}
        //want to be able to add, delete (maybe), and search
         void add(VectorID id, const std::vector<float>& v) override {
            if (v.size() != dim_) {
                throw std::runtime_error("dim mistmatch")
            }
            data_[id] = v;
         }

         void remove(VectorID id) override {
            data_.erase(id)
         }

         std::vector<std::pair<VectorID, float>> search(const std::vector<float>& query_vector, std::size_t k) const override {
            //call distance on each vector in data against the query vector
            //
            std::priority_queue<std::pair<VectorId, float>, std::vector<std::pair<VectorId, float>>, DistCompare> dists; //minheap implicitly of size k

            if (query_vector.size() != dim) {
                throw std::runtime_error("dim mismatch while calling search");
            }

            //std::vector<std::pair<VectorID, float>> dists;
            //dists.reserve(data_.size()); 

            for (const auto& [id, vec] : data_) {
                float dist = distance(vec, query_vector);
                if (dists.size() >= k) {
                    if (dist <= dists.top().second) {
                        dists.pop();
                        dists.emplace(id, dist);
                    }
                } else if (dist < dists.top().second) {
                    dists.pop();
                    dists.emplace(id, dist);
                }


                //dists.push_back(id, dist)
            }
            //now we have the top k, jusrt need to return contents now
            std::vector<std::pair<VecId, float>> res;
            res.reservse(dists.size());
            while (!dists.empty()) {
                res.push_back(dists.top()); 
                dists.pop();
            }
            std::reverse(results.begin(), results.end());

            return res;

         }

    private:
        Dimension dim_;
        DistanceMetric metric_;
        std::unordered_map<VectorID, std::vector<float>> data_; //we store here

        struct DistCompare {
            bool operator()(const std::pair<VectorId, float>& a, const std::pair<VectorId, float>& b) {
                return a.second > b.second;
            }
        }

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