#ifndef SRC_ARGPARSER
#define SRC_ARGPARSER

#include <string>
#include <vector>

class Args
{
private:
    std::string flag;
    std::string description;
    bool necessary;

public:
    Args() : flag(0), necessary(false) {};
    Args(std::string flag, std::string description, bool necessary) :
        flag(flag), description(description), necessary(necessary) {};
    ~Args() {};
    bool isNecessary() { return necessary; };
    const std::string& getFlag() { return flag; };
    const std::string& getDescription() { return description; };
};

class Argparser
{
private:
    std::vector<Args> arguments;
    std::vector<std::string> parsed;
    size_t necessary_size;
    bool error;

private:
    std::string getHelp();
    void showError();

public:
    Argparser();
    ~Argparser();
    bool parse(int argc, const char** argv);
    void add(std::string flag, std::string description = " ", bool necessary = true);
    std::vector<std::string> getArguments();
};

#endif