#include <string>
#include <chrono>
#include <thread>
#include "Logger.h"
#include "ApplicationBase.h"
#include "MainWindow.h"
#include "DBEngine.h"
#include "Storage.h"

std::string appName { "iotoys.gbaric.player" };

int main()
{
    auto homedir = StorageBase::InitStorage(appName);
    auto db = DBEngine(homedir + "/Data/db.db3");
	auto app = ApplicationBase::create(appName);

	return app->run(0, nullptr);
}