#include <QApplication>

#include "wizard.h"

int
main(int argc, char *argv[])
{
	QApplication app(argc, argv);  

	SetupWizard *wiz = new SetupWizard;
	wiz->show();

	return (app.exec());
}

