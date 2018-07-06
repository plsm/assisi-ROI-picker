#include <QGraphicsItem>
#include <QPainter>
#include "picker-stadium-standard.h"
#include "ui_picker-stadium-standard.h"


ROIStadiumStandard::ROIStadiumStandard(QWidget *parent) :
   QMainWindow(parent),
   ui (new Ui::ROIStadiumStandard)
{
	ui->setupUi (this);
	roigo = new ROIGOStadiumStandard (ui->centralwidget->pixmap);
	ui->centralwidget->set_roigo (roigo);
	ui->centralwidget->add_spin_box ("center x", roigo->center_x, 0, 1000, roigo, SLOT (setCenter_x (int)));
	ui->centralwidget->add_spin_box ("center y", roigo->center_y, 0, 1000, roigo, SLOT (setCenter_y (int)));
	ui->centralwidget->add_spin_box ("angle", roigo->angle, 0, 360, roigo, SLOT (setAngle (int)));
	ui->centralwidget->add_spin_box ("width", roigo->width, 0, 1000, roigo, SLOT (setWidth (int)));
	ui->centralwidget->add_spin_box ("length", roigo->length, 0, 1000, roigo, SLOT (setLength (int)));
	ui->centralwidget->add_spin_box ("border", roigo->border, 0, 1000, roigo, SLOT (setBorder (int)));
}

ROIStadiumStandard::~ROIStadiumStandard()
{
	delete ui;
}

