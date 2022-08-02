#define TEST_MODULE test_bulk

#include "gtest/gtest.h"

#include "bulk_handler.h"
#include "logger.h"


TEST(bulk_test_case, bulk_handler_test) {
    BulkHandler bulk(2);
    auto ssLogger = std::make_shared<StrStreamLogger>();
    bulk.addLogger(ssLogger);

    // Проверяем статические блоки
    for (const std::string& line : { "cmd1", "cmd2", "cmd3"})
    {
        bulk.addCommand(line);
    }
    bulk.endCommand();
    // Блок завершён – выводим блок
    // Конец ввода – принудительно завершаем блок.
    EXPECT_EQ(ssLogger->getString(), "bulk: cmd1, cmd2\nbulk: cmd3\n");

    // Проверяем динамические блоки
    ssLogger->clear();
    for (const std::string& line : { "cmd1", "{", "cmd2", "{", "cmd3", "}", "cmd4", "}" })
    {
        bulk.addCommand(line);
    }
    bulk.endCommand();
    // Начало динамического блока – выводим предыдущий статический досрочно.
    // Конец динамического блока – выводим. Игнорируем вложенные команды.
    EXPECT_EQ(ssLogger->getString(), "bulk: cmd1\nbulk: cmd2, cmd3, cmd4\n");


    ssLogger->clear();
    for (const std::string& line : { "{", "cmd1", "cmd2", "{", "cmd3", "}", "cmd4" })
    {
        bulk.addCommand(line);
    }
    bulk.endCommand();
    // Конец ввода – динамический блок игнорируется, не выводим.
    EXPECT_EQ(ssLogger->getString(), "");
}
