#include "UserInterface.h"

UserInterface::UserInterface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

UserInterface::~UserInterface()
{
}