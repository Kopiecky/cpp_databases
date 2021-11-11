#include <iostream>
#include <cstring>
#include "mongoManager.hpp"
#include <signal.h>

static bool terminate = true;

void signal_callback_handler(int signum) 
{
   terminate = false;
}

int main()
{	
	signal(SIGINT, signal_callback_handler);

	MongoManager myMongo;
	myMongo.accessCollection();

	int number;
	while(terminate)
	{
		std::cout<<"--------Menu--------"<<std::endl
		<<"1.Insert data"<<std::endl
		<<"2.Display all data"<<std::endl
		<<"3.Display last data"<<std::endl
		<<"4.Delete all data"<<std::endl
		<<"ctrl-c - exit"<<std::endl;

		char temp = getchar();
		getchar();
		switch(temp)
		{
			case '1':
				std::cout << "Range: ";
				std::cin>>number;
				myMongo.insertData("Range", number);
				std::cout << "\n\nOK\n\n";
				break;
			case '2':
				myMongo.displayAllDocuments();
				std::cout << "\n\nOK\n\n";
				break;
			case '3':
				myMongo.displayLastDocument();
				std::cout << "\n\nOK\n\n";
				break;
			case '4':
				myMongo.deleteAllDocuments();
				std::cout << "\n\nOK\n\n";
				break;
			default:
				std::cout << "\x1B[2J\x1B[H";
				break;		
		}

	}

	std::cout<<"exiting...\n";

	return 0;
}
