#include <string>
#include <chrono>
#include <thread>
#include "Logger.h"
#include "ApplicationBase.h"
#include "MainWindow.h"
#include "Storage.h"

std::string appName { "iotoys.gbaric.player" };

int main()
{
    auto homedir = StorageBase::InitStorage(appName);
  //  auto db = DBEngineBase(homedir + "/Data/db.db3");
   // db.CreateTable("Playlist", "ID INTEGER PRIMARY KEY AUTOINCREMENT,""Nazwa TEXT NOT NULL,""Plik TEXT NOT NULL");
	auto app = ApplicationBase::create(appName);

	return app->run(0, nullptr);
}