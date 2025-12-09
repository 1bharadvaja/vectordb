#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "collection.hpp"

//consider making this abstracted, IDatabase, which a class LocalDatabase and a RemoteDatabase can inherit

namespace vectordb {
    class Database : public IDatabase{ //this can be the local one, can add the remote one whenever
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

