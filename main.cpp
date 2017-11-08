#include <QApplication>
#include "picker-stadium-long.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ROIStadiumLong w;
	w.show();

	return a.exec();
}
