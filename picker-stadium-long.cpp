#include <QGraphicsItem>
#include <QPainter>
#include "picker-stadium-long.h"
#include "ui_picker-stadium-long.h"


ROIStadiumLong::ROIStadiumLong(QWidget *parent) :
   QMainWindow(parent),
   ui (new Ui::ROIStadiumLong)
{
	ui->setupUi (this);
	roigo = new ROIGOStadiumLong (ui->centralwidget->pixmap);
	ui->centralwidget->add_spin_box ("center x", 0, 1000, roigo, SLOT (setCenter_x (int)));
	ui->centralwidget->add_spin_box ("center y", 0, 1000, roigo, SLOT (setCenter_y (int)));
	ui->centralwidget->add_spin_box ("angle", 0, 360, roigo, SLOT (setAngle (int)));
	ui->centralwidget->add_spin_box ("width", 0, 1000, roigo, SLOT (setWidth (int)));
	ui->centralwidget->add_spin_box ("length", 0, 1000, roigo, SLOT (setLength (int)));
	ui->centralwidget->add_spin_box ("border 1 2", 0, 1000, roigo, SLOT (setBorder_1_2 (int)));
	ui->centralwidget->add_spin_box ("border 2 3", 0, 1000, roigo, SLOT (setBorder_2_3 (int)));
}

ROIStadiumLong::~ROIStadiumLong()
{
	delete ui;
}

