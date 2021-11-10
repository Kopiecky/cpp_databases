#include <iostream>
#include "mongoManager.hpp"

int main()
{
	std::cout<<"MongoDB to szmelc!!!!\n";
	
	MongoManager myMongo;

	myMongo.accessCollection();
	myMongo.insertData("Range", 125);
	myMongo.displayAllDocuments();

	return 0;
}
