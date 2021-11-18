#include "client/client.hpp"

int main(int argc, const char** argv)
{
    Client client(argc, argv);
    client.startClient();
    return 0;
}
