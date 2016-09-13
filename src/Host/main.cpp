#include "host.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Host w;
	w.show();
	return a.exec();
}
