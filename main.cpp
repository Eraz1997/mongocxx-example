#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;
using bsoncxx::type;

int main()
{ 
  try {
    mongocxx::instance inst{};
    const auto uri = mongocxx::uri{"mongodb://localhost:27017"};
    mongocxx::options::client client_options;
    const auto api = mongocxx::options::server_api{ mongocxx::options::server_api::version::k_version_1 };
    client_options.server_api_opts(api);
  
    mongocxx::client client{ uri, client_options };
    auto db = client["test_db"];
    auto collection = db["test_collection"];

    // Insert
    auto insert_result = collection.insert_one(make_document(
        kvp("name", "enri"),
        kvp("age", 123),
        kvp("hobbies", make_array(
            "sport", "jumping at home", "flipping tables"
        )),
        kvp("appearance", make_document(
            kvp("hair", "nice"),
            kvp("eyes", "nicer")
        ))
    ));
    std::cout << insert_result->result().inserted_count() << std::endl;

    // Find
    auto cursor_all = collection.find({});
    for (auto doc : cursor_all) {
        std::cout << (doc["_id"].type() == type::k_oid) << std::endl;
        std::cout << doc["name"].get_string().value << std::endl;
    }

    // JSON
    std::cout << "Collection: " << collection.name() << " contains" << std::endl;
    cursor_all = collection.find({});
    for (auto doc : cursor_all) {
        std::cout << bsoncxx::to_json(doc, bsoncxx::ExtendedJsonMode::k_relaxed) << std::endl;
    }
  } catch (const std::exception& e) {
    std::cout<< "Exception: " << e.what() << std::endl;
  }

  return 0;
}
