#include <algorithm>
#include <math.h>
#include <QPainter>
#include <opencv2/core/core.hpp>

#include "roigo-stadium-long.h"

void ROIGOStadiumLong::setCenter_x(int value)
{
	center_x = value;
	update ();
}

void ROIGOStadiumLong::setCenter_y(int value)
{
	center_y = value;
	update ();
}

void ROIGOStadiumLong::setAngle(int value)
{
	angle = value;
	update ();
}

void ROIGOStadiumLong::setWidth(int value)
{
	if (value > 10) {
		width = value;
		update ();
	}
}

void ROIGOStadiumLong::setLength(int value)
{
	if (value > 10 && value > border_2_3 + 3) {
		length = value;
		update ();
	}
}

void ROIGOStadiumLong::setBorder_1_2(int value)
{
	if (value > 3 && value < border_2_3) {
		border_1_2 = value;
		update ();
	}
}

void ROIGOStadiumLong::setBorder_2_3(int value)
{
	if (value > border_1_2 && value < length - 3) {
		border_2_3 = value;
		update ();
	}
}

ROIGOStadiumLong::ROIGOStadiumLong (QGraphicsItem *parent):
   QGraphicsObject (parent),
   center_x (100),
   center_y (100),
   angle (0),
   width (50),
   length (200),
   border_1_2 (66),
   border_2_3 (132)
{

}

ROIGOStadiumLong::~ROIGOStadiumLong ()
{

}


void ROIGOStadiumLong::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setPen (Qt::black);
//	painter->translate (-this->center_x, -this->center_y);
	painter->rotate (this->angle);
	painter->drawRoundedRect (
	         this->center_x - this->length / 2, this->center_y - this->width / 2,
	         this->length, this->width,
	         this->width / 2, this->width / 2
	         );
	painter->drawLine (
	         this->center_x - this->length / 2 + this->border_1_2, this->center_y - this->width / 2,
	         this->center_x - this->length / 2 + this->border_1_2, this->center_y + this->width / 2
	         );
	painter->drawLine (
	         this->center_x - this->length / 2 + this->border_2_3, this->center_y - this->width / 2,
	         this->center_x - this->length / 2 + this->border_2_3, this->center_y + this->width / 2
	         );
//	painter->translate (this->center_x, this->center_y);
}

QRectF ROIGOStadiumLong::boundingRect () const
{
	int extend = std::max (this->length, this->width);
	return QRectF (this->center_x - extend / 2, this->center_y - extend / 2,
	               extend , extend);
}
/*
void ROIGOStadiumLong::save_masks (const std::string &folder, int width, int height) const
{
	cv::Mat mask;
	mask = cv::Mat::zeros (height, width, CV_8UC1);

}*/
