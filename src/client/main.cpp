#include "maindialog.h"
#include <QtGui/QApplication>

int main(int argc, char **argv)
{
	QApplication a(argc, argv);

	MainDialog dlg;
	dlg.show();

	return a.exec();
}
