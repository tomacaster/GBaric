#pragma once

#include <iostream>
#include <string>

#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/Database.h>
#include "Logger.h"

class DBEngine 
{
    public:
        DBEngine(const std::string& dbPath);
        // Creating a database
        bool CreateDatabase(const std::string& dbName);

        // Creating tables
        bool CreateTable(const std::string& tableName, const std::string& columns);

        // Inserting data
        bool InsertData(const std::string& tableName, const std::string &columns, const std::string& data);

        // Selecting data
        bool SelectData(const std::string& tableName, const std::string& condition);

        // Updating data
        bool UpdateData(const std::string& tableName, const std::string& newData, const std::string& condition);

        // Deleting data
        bool DeleteData(const std::string& tableName, const std::string& condition);

        // Dropping tables
        bool DropTable(const std::string& tableName);

        // Transactions
        bool BeginTransaction();
        bool CommitTransaction();
        bool RollbackTransaction();

        // Indexing
        bool CreateIndex(const std::string& indexName, const std::string& tableName, const std::string& columns);

        // Query optimization
        bool OptimizeQuery(const std::string& query);

        // Connection management
        bool ConnectToDatabase(const std::string& dbName);
        bool DisconnectFromDatabase();

        // Error handling
        bool HandleError(const std::string& errorMessage);

    private:
        SQLite::Database _db;
        static std::shared_ptr<spdlog::logger> _logger;
};