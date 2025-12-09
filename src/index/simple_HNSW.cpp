#include "index.hpp"

class SimpleHNSW : public Index {
    public:
        SimpleHNSW(Dimension dim, DistanceMetric metric): dim_(dim), metric_(metric) {}
        


    private:
        Dimension dim_;
        DistanceMetric metric_;

        //want to build graph over here essentially

}