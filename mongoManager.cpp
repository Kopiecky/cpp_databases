#include "mongoManager.hpp"

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/stdx.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <mongocxx/uri.hpp>
#include <cstring>


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;




 /*----------constructor and destructor-------------*/

MongoManager::MongoManager(const char* myUri, const char* myDb, size_t len)  //Brzydkie przesylanie argumentu przez wskaznik
{
    nameDb = new char[len]; //Tutaj zmienic
    
    memcpy(nameDb, myDb, len); //Tutaj zmienic

    printf("MongoManager here Uri:%s\n", myUri);

    mongocxx::uri uri(myUri);
    client = new mongocxx::client(uri);
    dataBase = client[nameDb]; //Tutaj zmienic
}

MongoManager::MongoManager(const char* myDb, size_t len)
{
    std::cout<<"MongoManager here default URI\n";

    mongocxx::uri uri("mongodb://localhost:27017");
    client = new mongocxx::client(uri);
    dataBase = client[myDb];
}

MongoManager::~MongoManager()
{
    std::cout<<"MongoManager bye\n";

    delete client;
    delete nameDb; //Tutaj zmienic
}



 /*----------private methods-------------*/

bsoncxx::document::value MongoManager::createDocument()
{
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
    << "name" << "MongoDB"
    << "type" << "database"
    << "count" << 1
    << "info" << bsoncxx::builder::stream::open_document
        << "x" << 203
        << "y" << 102
    << bsoncxx::builder::stream::close_document
    << bsoncxx::builder::stream::finalize;

    return doc_value;
}


 /*----------public API-------------*/

void MongoManager::accessCollection(char* myCollection)
{
    collection = dataBase[myCollection];

}

void MongoManager::accessCollection()
{
    collection = dataBase["user"];
}
