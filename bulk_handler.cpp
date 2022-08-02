#include "bulk_handler.h"

#include <fstream>
#include <string>

/**
 * @brief Construct a new Bulk Handler:: Bulk Handler object
 * 
 * @param N - количество команд в блоке
 */
BulkHandler::BulkHandler(int N) : m_bulkSize{N}
{
    m_commands.reserve(N);
}

/**
 * @brief Добавляет команды в блок
 * 
 * @param command 
 */
void BulkHandler::addCommand(std::string_view command)
{
    if (m_commands.empty())
        m_startTime = std::time(nullptr);
    m_commands.emplace_back(command);
    if (m_commands.size() == static_cast<std::size_t>(m_bulkSize) && !m_dynamicFlag)
        endCommand();
}

/**
 * @brief Обработка завершения блока или ввода
 * 
 */
void BulkHandler::endCommand()
{
    if (openedBracket != 0 || m_commands.empty())
        return;

    std::string bulk = toString();
    writeLog(bulk);
    m_commands.clear();
    m_dynamicFlag = false;
}

/**
 * @brief Начало динамического блока
 * 
 */
void BulkHandler::startModule()
{
    if (!m_dynamicFlag)
        endCommand();
    m_dynamicFlag = true;
    ++openedBracket;
}

/**
 * @brief Завершение динамического блока
 * 
 */
void BulkHandler::endModule()
{
    --openedBracket;
    if (openedBracket == 0)
        endCommand();
}

/**
 * @brief Добавляет логгер для записи блоков команд
 * 
 * @param logger 
 */
void BulkHandler::addLogger(std::shared_ptr<ILogger> logger)
{
    m_loggers.push_back(logger);
}

/**
 * @brief Записывает блок команд в логгер
 * 
 * @param bulk 
 */
void BulkHandler::writeLog(std::string_view bulk)
{
    for (const auto& logger : m_loggers)
    {
        logger->setStartTime(m_startTime);
        logger->write(bulk);
    }
}

/**
 * @brief Приводит блок команд к строковому виду
 * 
 * @return std::string 
 */
std::string BulkHandler::toString()
{
    std::string bulk = "bulk: ";
    for (const auto& command : m_commands)
    {
        if (&command != &m_commands.at(0))
            bulk += ", ";
        bulk += command;
    }
    bulk += '\n';
    return bulk;
}
