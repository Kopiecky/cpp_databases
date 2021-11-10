#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <string>

class MongoManager
{

    /*----------private data types------------*/
    private:
    mongocxx::instance instance{};
    mongocxx::client *client;
    mongocxx::database dataBase;
    mongocxx::collection collection; 

    char* nameDb;

    /*----------public data types------------*/
    public:
    

    /*----------public methods-------------*/
    public:
    MongoManager(const char* myUri, const char* myDb, size_t len);
    MongoManager(const char* myDb = "PBD", size_t len = 3);
    ~MongoManager();
    
    void accessCollection(char* myCollection);
    void accessCollection(void);
    void displayAllDocuments(void);
    void insertData(std::string name, int value);

    private:
    bsoncxx::document::value createDocument(std::string name, int value);
};