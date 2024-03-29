#include "logger.h"

#include <iostream>
#include <fstream>
#include <string>


void FileLogger::write(std::string_view text)
{
    std::fstream fout(m_fileName, std::ofstream::out);
    fout << text;
}

void FileLogger::setStartTime(const time_t& time)
{
    m_fileName = "bulk" + std::to_string(time) + ".log";
}

void ConsoleLogger::write(std::string_view text)
{
    std::cout << text;
}

void ConsoleLogger::setStartTime(const time_t&)
{}

void StrStreamLogger::write(std::string_view text)
{
    m_sout << text;
}

void StrStreamLogger::setStartTime(const time_t&)
{}

void StrStreamLogger::clear()
{
    m_sout.str("");
}

std::string StrStreamLogger::getString()
{
    return m_sout.str();
}
