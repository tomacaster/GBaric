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
	//auto main = MainWindow();
    logger->info("fdsfds");
	logger->flush();
	app->make_window_and_run<MainWindow>(0, nullptr);
	
	std::cout << "End of App" << std::endl;
	    for(;;){
            std::chrono::milliseconds timespan(6000);
    std::this_thread::sleep_for(timespan);
    }

	return 0;
}