#include <iostream>
#include "Matrix.h"
#include "UserInterface.h"


int main(int argc, char* argv[])
{
	QApplication app(argc,argv);
	UserInterface ui;
	ui.show();
	try
	{
		
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return app.exec();
}