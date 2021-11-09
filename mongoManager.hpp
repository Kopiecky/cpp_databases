#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>

class MongoManager
{

    /*----------private data types------------*/
    private:
    mongocxx::instance instance{};
    mongocxx::client *client;
    mongocxx::database dataBase;
    mongocxx::collection collection; 

    char* nameDb; //Tutaj zmienic

    /*----------public data types------------*/
    public:
    

    /*----------public methods-------------*/
    public:
    MongoManager(const char* myUri, const char* myDb, size_t len);
    MongoManager(const char* myDb = "PBD", size_t len = 3);
    ~MongoManager();
    
    void accessCollection(char* myCollection);
    void accessCollection(void);

    private:
    bsoncxx::document::value createDocument(void);
};