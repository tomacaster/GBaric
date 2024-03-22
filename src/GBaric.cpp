#include <iostream>
#include "ApplicationBase.h"
#include "MainWindow.h"
int main()
{
	auto app = ApplicationBase::create("iotoys.gbaric.player");
	auto main = MainWindow();

	app->make_window_and_run<MainWindow>(0, nullptr);
	
	std::cout << "End of App" << std::endl;
	
	return 0;
}