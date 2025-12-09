

class IDatabase {
public:
    virtual ~IDatabase() = default;

    virtual std::shared_ptr<Collection> create_collection(
        const std::string& name, Dim dim) = 0;

    virtual std::shared_ptr<Collection> get_collection(
        const std::string& name) = 0;
};
