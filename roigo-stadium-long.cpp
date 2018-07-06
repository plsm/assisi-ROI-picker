#include <iostream>
#include <fstream>
#include <algorithm>
#include <QPainter>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include "roigo-stadium-long.h"
#include "trigonometry.h"

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
	painter->save ();
	painter->setPen (Qt::black);
	painter->translate (this->center_x, this->center_y);
	painter->rotate (this->angle);
	painter->translate (-this->center_x, -this->center_y);
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
	painter->restore ();
}

QRectF ROIGOStadiumLong::boundingRect () const
{
	int extend = std::max (this->length, this->width);
	return QRectF (this->center_x - extend / 2, this->center_y - extend / 2,
	               extend , extend);
}

void ROIGOStadiumLong::save_masks (const std::string &folder, int width, int height, const std::vector<std::string> names) const
{
	cv::Mat mask;
	std::string filename;
	std::cout << "Saving masks to folder [" << folder << "]\n";
	// first mask
	mask = cv::Mat::zeros (height, width, CV_8UC1);
	cv::ellipse (
	         mask,
	         cv::Point2i (
	            this->center_x + (this->length / 2 - this->width / 2) * cosd (this->angle + 180),
	            this->center_y + (this->length / 2 - this->width / 2) * sind (this->angle + 180)
	            ),
	         cvSize (this->width / 2, this->width / 2),
	         0,
	         this->angle + 90,
	         this->angle + 270,
	         cv::Scalar (255, 0, 0, 0),
	         -1);
	const cv::Point points_1 [] = {
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->width / 2) * cosd (this->angle + 180)
	      + this->width / 2 * cosd (this->angle + 270),
	      this->center_y
	      + (this->length / 2 - this->width / 2) * sind (this->angle + 180)
	      + this->width / 2 * sind (this->angle + 270)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->width / 2) * cosd (this->angle + 180)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (this->length / 2 - this->width / 2) * sind (this->angle + 180)
	      + this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->border_1_2) * cosd (this->angle + 180)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (this->length / 2 - this->border_1_2) * sind (this->angle + 180)
	      + this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->border_1_2) * cosd (this->angle + 180)
	      + this->width / 2 * cosd (this->angle + 270),
	      this->center_y
	      + (this->length / 2 - this->border_1_2) * sind (this->angle + 180)
	      + this->width / 2 * sind (this->angle + 270)
	      )
	};
	cv::fillConvexPoly (
	         mask,
	         points_1,
	         4,
	         cv::Scalar (255, 0, 0, 0),
	         0);
	filename = this->mask_filename (folder, "Mask-1.png", names, 0);
	if (!cv::imwrite (filename, mask)) {
		std::cerr << "Problems writing file\n" << filename << "\n";
	}
	else {
		std::cout << "  saved first mask\n";
	}
	// second mask
	mask = cv::Mat::zeros (height, width, CV_8UC1);
	const cv::Point points_2 [] = {
	   cv::Point2i (
	      this->center_x
	      + (-this->length / 2 + this->border_1_2) * cosd (this->angle)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-this->length / 2 + this->border_1_2) * sind (this->angle)
	      + this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (-this->length / 2 + this->border_1_2) * cosd (this->angle)
	      - this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-this->length / 2 + this->border_1_2) * sind (this->angle)
	      - this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (-this->length / 2 + this->border_2_3) * cosd (this->angle)
	      - this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-this->length / 2 + this->border_2_3) * sind (this->angle)
	      - this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (-this->length / 2 + this->border_2_3) * cosd (this->angle)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-this->length / 2 + this->border_2_3) * sind (this->angle)
	      + this->width / 2 * sind (this->angle + 90)
	      )
	};
	cv::fillConvexPoly (
	         mask,
	         points_2,
	         4,
	         cv::Scalar (255, 0, 0, 0),
	         0);
	filename = this->mask_filename (folder, "Mask-2.png", names, 1);
	if (!cv::imwrite (filename, mask)) {
		std::cerr << "Problems writing file\n" << filename << "\n";
	}
	else {
		std::cout << "  saved second mask\n";
	}
	// third mask
	mask = cv::Mat::zeros (height, width, CV_8UC1);
	cv::ellipse (
	         mask,
	         cv::Point2i (
	            this->center_x + (this->length / 2 - this->width / 2) * cosd (this->angle),
	            this->center_y + (this->length / 2 - this->width / 2) * sind (this->angle)
	            ),
	         cvSize (this->width / 2, this->width / 2),
	         0,
	         this->angle - 90,
	         this->angle + 90,
	         cv::Scalar (255, 0, 0, 0),
	         -1);
	const cv::Point points_3 [] = {
	   cv::Point2i (
	      this->center_x
	      + (-this->length / 2 + this->border_2_3) * cosd (this->angle)
	      - this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-this->length / 2 + this->border_2_3) * sind (this->angle)
	      - this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (-this->length / 2 + this->border_2_3) * cosd (this->angle)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-this->length / 2 + this->border_2_3) * sind (this->angle)
	      + this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->width / 2) * cosd (this->angle)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (this->length / 2 - this->width / 2) * sind (this->angle)
	      + this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->width / 2) * cosd (this->angle)
	      - this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (this->length / 2 - this->width / 2) * sind (this->angle)
	      - this->width / 2 * sind (this->angle + 90)
	      )
	};
	cv::fillConvexPoly (
	         mask,
	         points_3,
	         4,
	         cv::Scalar (255, 0, 0, 0),
	         0);
	filename = this->mask_filename (folder, "Mask-3.png", names, 2);
	if (!cv::imwrite (filename, mask)) {
		std::cerr << "Problems writing file\n" << filename << "\n";
	}
	else {
		std::cout << "  saved third mask\n";
	}
}

void ROIGOStadiumLong::save_properties (const std::string &folder) const
{
	std::cout << "Saving properties to folder [" << folder << "]\n";
	std::string filename = folder + "/" + AbstractROI::ROI_PROPERTIES_FILENAME;
	std::ofstream ofs (filename);
	ofs << "center_x:" << this->center_x << '\n'
	    << "center_x:" << this->center_x << '\n'
	    << "angle:" << this->angle << '\n'
	    << "width:" << this->width << '\n'
	    << "length:" << this->length << '\n'
	    << "border_1_2:" << this->border_1_2 << '\n'
	    << "border_2_3:" << this->border_2_3 << '\n';
	ofs.close ();
}
