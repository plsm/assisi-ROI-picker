#ifndef ROISTADIUMSTANDARD_H
#define ROISTADIUMSTANDARD_H

#include <QMainWindow>

#include "roigo-stadium-standard.h"

namespace Ui {
class ROIStadiumStandard;
}

class ROIStadiumStandard : public QMainWindow
{
	Q_OBJECT

public:
	explicit ROIStadiumStandard(QWidget *parent = 0);
	~ROIStadiumStandard();

private:
	Ui::ROIStadiumStandard *ui;
	ROIGOStadiumStandard *roigo;
};

#endif // ROISTADIUMLONG_H
