#ifndef BULK_HANDLER_H
#define BULK_HANDLER_H

#include <iostream>
#include <string_view>
#include <vector>
#include <ctime>


class BulkHandler
{
public:
    explicit BulkHandler(int N);

    void addCommand(std::string_view command);

    void endCommand();
    
    void startModule();
    void endModule();

    void print(std::string_view bulk, std::ostream& out = std::cout);
    void saveToFile(std::string_view bulk);

private:
    int m_bulkSize;
    std::time_t m_startTime;
    std::vector<std::string> m_commands;
    bool m_dynamicFlag = false;
    int openedBracket = 0;

    std::string toString();
};

#endif // BULK_HANDLER_H
