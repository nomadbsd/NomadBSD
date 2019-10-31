#include <QApplication>
#include <QTranslator>

#include "wizard.h"

int
main(int argc, char *argv[])
{
	QApplication app(argc, argv);  
	QTranslator translator;

	if (translator.load(QLocale(), QLatin1String(PROGRAM),
	    QLatin1String("_"), QLatin1String(":/locale")))
		qApp->installTranslator(&translator);
	Wizard *wiz = new Wizard;
	wiz->show();

	return (app.exec());
}

