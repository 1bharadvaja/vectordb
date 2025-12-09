//add, delete, query vectors

class Collection {
    public:
        VectorID insert(const Entry& E);
        void remove(VectorId id);

        std::vector<std::pair<VectorId, float>> search(const std::vector<float>& query, std::size_t k);
    private:
        std::string name_;
        Dimension dim_;
        std::unique_ptr<Index> index_;
        std::shared_ptr<StorageEngine> storage_; 

}