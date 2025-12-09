#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "collection.hpp"

namespace vectordb {
    class Database {
        public:
            static std::unique_ptr<Database> open(const std::string& path);

            std::shared_ptr<Collection> create_collection(const std::string& name, Dimension dim);

            std::shared_ptr<Collection> get_collection(const std::string& name)
        private:
            Database(std::string root_path);
            std::string root_path_;
            std::unordered_map<std::string, std::shared_ptr<Collection>> collections_;

            void load_manifest(); 

    };

}

