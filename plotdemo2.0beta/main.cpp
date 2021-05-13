#include "stdafx.h"
#include "plotdemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	plotdemo w;
	w.show();

	return a.exec();
}
