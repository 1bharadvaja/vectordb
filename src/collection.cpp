//add, delete, query vectors
#include "index/brute_force_index.cpp"

class Collection {
    public:
        Collection(std::string name, Dim dim, std::unique_ptr<Index>& index, std::shared_ptr<StorageEngine>& storage) :
        name_(std::move(name)),
          dim_(dim),
          index_(std::move(index)),
          storage_(std::move(storage)) {} 

        VectorID insert(const Entry& E) {
            VectorID id = storage_->append_entry(e);
            index_->add(id, e.vector);
            return id;
        }
        void remove(VectorId id) {
            VectorID id = storage_->mark_deleted(id);
            index_->remove(id);
        }

        std::vector<std::pair<VectorId, float>> search(const std::vector<float>& query, std::size_t k) {
            return index_->search(query, k);
        }
    private:
        std::string name_;
        Dimension dim_;
        std::unique_ptr<Index> index_;
        std::shared_ptr<StorageEngine> storage_; 

}