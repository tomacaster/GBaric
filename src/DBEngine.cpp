#include "DBEngine.h"
#include <fmt/core.h>

std::shared_ptr<spdlog::logger> DBEngine::_logger {nullptr};

DBEngine::DBEngine(const std::string& dbPath) : _db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    _logger = Logger::GetClassLogger("DBEngine");
}

bool DBEngine::CreateDatabase(const std::string &dbName)
{
    return true;
}

bool DBEngine::CreateTable(const std::string& tableName, const std::string& columns)
{
    try 
    {
        //"CREATE TABLE IF NOT EXISTS Playlista (""ID INTEGER PRIMARY KEY AUTOINCREMENT,""Nazwa TEXT NOT NULL,""Plik TEXT NOT NULL)")
        _db.exec("DROP TABLE IF EXISTS test");
        _db.exec("CREATE TABLE IF NOT EXISTS " + tableName + " (" + columns + ")");

        return true;
    } catch (std::exception& e) 
    {
        std::cerr << "Error creating table: " << e.what() << std::endl;

        return false;
    }
}


bool DBEngine::InsertData(const std::string &tableName, const std::string &columns, const std::string &data)
{
    try
    {
        auto str = fmt::format("INSERT INTO {} ({}) VALUES ({})", tableName, columns, data);
        SQLite::Statement query(_db, str);
        query.exec();
        //_db.exec("INSERT INTO " + tableName + std::string(fmt::format("({}) ", data) + "VALUES " ));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return true;
}

bool DBEngine::SelectData(const std::string &tableName, const std::string &condition)
{
    return true;
}

bool DBEngine::UpdateData(const std::string &tableName, const std::string &newData, const std::string &condition)
{
    return true;
}

bool DBEngine::DeleteData(const std::string &tableName, const std::string &condition)
{
    return true;
}

bool DBEngine::DropTable(const std::string &tableName)
{
    return true;
}

bool DBEngine::BeginTransaction()
{
    return true;
}

bool DBEngine::CommitTransaction()
{
    return true;
}

bool DBEngine::RollbackTransaction()
{
    return true;
}

bool DBEngine::CreateIndex(const std::string &indexName, const std::string &tableName, const std::string &columns)
{
    return true;
}

bool DBEngine::OptimizeQuery(const std::string &query)
{
    return true;
}

bool DBEngine::ConnectToDatabase(const std::string &dbName)
{
    return true;
}

bool DBEngine::DisconnectFromDatabase()
{
    return true;
}

bool DBEngine::HandleError(const std::string &errorMessage)
{
    return true;
}
