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

MongoManager::MongoManager(const char* myUri, const char* myDb, size_t len) //Brzydkie przesylanie argumentu przez wskaznik
{
    nameDb = new char[len + 1];
    memcpy(nameDb, myDb, len + 1);
    printf("MongoManager spec Uri:%s\n", nameDb);

    bsoncxx::string::view_or_value dbName = nameDb;

    mongocxx::uri uri(myUri);
    client = new mongocxx::client(uri);
    dataBase = client->database(dbName); 
}

MongoManager::MongoManager(const char* myDb, size_t len)
{
    nameDb = new char[len + 1];
    memcpy(nameDb, myDb, len + 1);
     printf("MongoManager default Uri:%s\n", nameDb);

    bsoncxx::string::view_or_value dbName = nameDb;

    mongocxx::uri uri("mongodb://localhost:27017");
    client = new mongocxx::client(uri);
    dataBase = client->database(dbName);
}

MongoManager::~MongoManager()
{
    std::cout<<"MongoManager bye\n";

    delete client;
    delete nameDb;
}



 /*----------private methods-------------*/

bsoncxx::document::value MongoManager::createDocument(std::string name, int value)
{
    bsoncxx::builder::basic::document builder;
    builder.append(bsoncxx::builder::basic::kvp(name, value));
    bsoncxx::document::value obj = builder.extract();
    
    return obj;
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

 void MongoManager::insertData(std::string name, int value)
 {
    auto document = createDocument(name, value);
    std::cout<<"HERE\n";
    collection.insert_one(document.view());
    std::cout<<"HERE HERE\n";
 }


void MongoManager::displayAllDocuments()
{
    mongocxx::cursor cursor = collection.find({});
    for(auto doc : cursor) 
    {
        std::cout << bsoncxx::to_json(doc) << "\n";
    }
}