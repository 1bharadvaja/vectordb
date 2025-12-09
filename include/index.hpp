class Index {
    public:
        virtual ~Index() = default;
        virtual void add(VectorId id, const std::vector<float>& v) = 0;
        virtual void remove(VectorId id) = 0;
        virtual std::vector<std::pair<VectorId, float>> search(const Vector& query, std::size_t k) const = 0;

};

