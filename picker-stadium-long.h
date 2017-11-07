#ifndef ROISTADIUMLONG_H
#define ROISTADIUMLONG_H

#include <QMainWindow>

#include "roigo-stadium-long.h"

namespace Ui {
class ROIStadiumLong;
}

class ROIStadiumLong : public QMainWindow
{
	Q_OBJECT

public:
	explicit ROIStadiumLong(QWidget *parent = 0);
	~ROIStadiumLong();

private:
	Ui::ROIStadiumLong *ui;
	ROIGOStadiumLong *roigo;
};

#endif // ROISTADIUMLONG_H
