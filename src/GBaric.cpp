#include <iostream>
#include <chrono>
#include <thread>
#include "Logger.h"
#include "ApplicationBase.h"
#include "MainWindow.h"


int main()
{
    Logger::InitLogger();
    auto logger = Logger::GetLogger();
	auto app = ApplicationBase::create("iotoys.gbaric.player");

    logger->info("fdsfds");
	logger->flush();

	return app->run(0, nullptr);
}