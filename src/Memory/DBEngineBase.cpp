#include "Memory/DBEngineBase.h"
#include <fmt/core.h>

using namespace Memory;

std::shared_ptr<spdlog::logger> DBEngineBase::_logger {nullptr};

DBEngineBase::DBEngineBase(const std::string& dbPath) : _db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    _logger = Logger::GetClassLogger("DBEngine");
}

bool DBEngineBase::CreateDatabase(const std::string &dbName)
{
    return true;
}

bool DBEngineBase::CreateTable(const std::string& tableName, const std::string& columns)
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


bool DBEngineBase::InsertData(const std::string &tableName, const std::string &columns, const std::string &data)
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

bool DBEngineBase::SelectData(const std::string &tableName, const std::string &condition)
{
    return true;
}

bool DBEngineBase::UpdateData(const std::string &tableName, const std::string &newData, const std::string &condition)
{
    return true;
}

bool DBEngineBase::DeleteData(const std::string &tableName, const std::string &condition)
{
    return true;
}

bool DBEngineBase::DropTable(const std::string &tableName)
{
    return true;
}

bool DBEngineBase::BeginTransaction()
{
    return true;
}

bool DBEngineBase::CommitTransaction()
{
    return true;
}

bool DBEngineBase::RollbackTransaction()
{
    return true;
}

bool DBEngineBase::CreateIndex(const std::string &indexName, const std::string &tableName, const std::string &columns)
{
    return true;
}

bool DBEngineBase::OptimizeQuery(const std::string &query)
{
    return true;
}

bool DBEngineBase::ConnectToDatabase(const std::string &dbName)
{
    return true;
}

bool DBEngineBase::DisconnectFromDatabase()
{
    return true;
}

bool DBEngineBase::HandleError(const std::string &errorMessage)
{
    return true;
}
