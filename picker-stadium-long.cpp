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
	ui->centralwidget->set_roigo (roigo);
	ui->centralwidget->add_spin_box ("center x", roigo->center_x, 0, 1000, roigo, SLOT (setCenter_x (int)));
	ui->centralwidget->add_spin_box ("center y", roigo->center_y, 0, 1000, roigo, SLOT (setCenter_y (int)));
	ui->centralwidget->add_spin_box ("angle", roigo->angle, 0, 360, roigo, SLOT (setAngle (int)));
	ui->centralwidget->add_spin_box ("width", roigo->width, 0, 1000, roigo, SLOT (setWidth (int)));
	ui->centralwidget->add_spin_box ("length", roigo->length, 0, 1000, roigo, SLOT (setLength (int)));
	ui->centralwidget->add_spin_box ("border 1 2", roigo->border_1_2, 0, 1000, roigo, SLOT (setBorder_1_2 (int)));
	ui->centralwidget->add_spin_box ("border 2 3", roigo->border_2_3, 0, 1000, roigo, SLOT (setBorder_2_3 (int)));
	ui->centralwidget->add_textbox_mask_name ("Mask-1.png");
	ui->centralwidget->add_textbox_mask_name ("Mask-2.png");
	ui->centralwidget->add_textbox_mask_name ("Mask-3.png");
}

ROIStadiumLong::~ROIStadiumLong()
{
	delete ui;
}

