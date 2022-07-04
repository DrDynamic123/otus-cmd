#include "bulk_handler.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

int getN(int argc, char *argv[])
{
    if (argc == 1)
        return 0;
    return std::atoi(argv[1]);
}

/**
 * @brief main
 * 
 * @return int 
 */
int main(int argc, char *argv[])
{
    try
    {
        int n = getN(argc, argv);
        if (n <= 0)
        {
            std::cerr << "Wrong number of command in bulk\n";
            return EXIT_FAILURE;
        }

        BulkHandler bulk(n);
        for (std::string line; std::getline(std::cin, line);)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (line == "{")
                bulk.startModule();
            else if (line == "}")
                bulk.endModule();
            else
                bulk.addCommand(line);
        }
        bulk.endCommand();
        


    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
