#include "argparser.hpp"

#include <iostream>


Argparser::Argparser() : necessary_size(0)
{
    Args help("-h", getHelp(), false);
    arguments.push_back(help);
}

Argparser::~Argparser() {}

bool Argparser::parse(int argc, const char** argv)
{
    size_t counter = 0;
    if (arguments[1].getFlag().compare(argv[1]))
    {
        std::cout << getHelp();
        counter = necessary_size;
    }
    else
    {
        for (size_t i = 0; i < arguments.size(); ++i)
        {
            if (arguments[i].isNecessary())
            {
                for (size_t j = 1; j < argc; j += 2)
                {
                    if (!arguments[i].getFlag().compare(argv[j]))
                    {
                        if (argv[j + 1] != NULL)
                        {
                            if (argv[j + 1][0] != '\0')
                            {
                                parsed.push_back(argv[j + 1]);
                                counter++;
                            }
                        }
                    }
                }
            }
        }
    }
    error = (necessary_size == counter) ? 0 : -1;
    if (error)
    {
        showError();
    }
    return error;
}

void Argparser::add(std::string flag, std::string description, bool necessary)
{
    Args argument(flag, description, necessary);
    arguments.push_back(argument);
    necessary_size += necessary ? 1 : 0;
}

std::vector<std::string> Argparser::getArguments()
{
    return parsed;
}

void Argparser::showError()
{
    std::cout << "Wrong input arguments. For help see -h (--help)" << std::endl;
}

std::string Argparser::getHelp()
{
    std::string header = "usage: [argument] [value] \n\nArguments:\n";
    std::string temp;

    for (size_t i = 1; i < arguments.size(); ++i)
    {
        std::string argument = arguments[i].getFlag();
        std::string description = arguments[i].getDescription();
        std::string necessary = arguments[i].isNecessary() ? "yes" : "no";
        temp.append(argument + "\t" + description + "\tNecessary: " + necessary + "\n"); 
    }
    return header + temp;
}