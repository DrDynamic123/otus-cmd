#ifndef BULK_HANDLER_H
#define BULK_HANDLER_H

#include "logger.h"

#include <iostream>
#include <string_view>
#include <vector>
#include <ctime>
#include <memory>


class BulkHandler
{
public:
    explicit BulkHandler(int N);

    void addCommand(std::string_view command);

    void endCommand();
    
    void startModule();
    void endModule();

    void addLogger(std::shared_ptr<ILogger> logger);
    void writeLog(std::string_view bulk);

private:
    int m_bulkSize;
    std::time_t m_startTime;
    std::vector<std::string> m_commands;
    bool m_dynamicFlag = false;
    int openedBracket = 0;
    std::vector<std::shared_ptr<ILogger>> m_loggers;

    std::string toString();
};

#endif // BULK_HANDLER_H
