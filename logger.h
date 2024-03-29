#ifndef LOGGER_H
#define LOGGER_H

#include <string_view>
#include <sstream>


class ILogger
{
public:
    explicit ILogger() = default;
    virtual ~ILogger() = default;

    virtual void write(std::string_view text) = 0;
    virtual void setStartTime(const time_t& time) = 0;
};

class FileLogger : public ILogger
{
public:
    FileLogger() = default;

    void write(std::string_view text) override;
    void setStartTime(const time_t& time) override;

private:
    std::string m_fileName;
};

class ConsoleLogger : public ILogger
{
public:
    ConsoleLogger() = default;
    void write(std::string_view text) override;
    void setStartTime(const time_t&) override;
};

class StrStreamLogger : public ILogger
{
public:
    StrStreamLogger() = default;
    void write(std::string_view text) override;
    void setStartTime(const time_t&) override;

    void clear();
    std::string getString();

private:
    std::stringstream m_sout;
};

#endif // LOGGER_H
