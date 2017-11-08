#ifndef ROIGOSTADIUMLONG_H
#define ROIGOSTADIUMLONG_H

#include <QGraphicsObject>
#include "abstract-roi.hpp"

class ROIGOStadiumLong:
      public QGraphicsObject,
      public AbstractROI
{
	Q_OBJECT
public:
	int center_x;
	int center_y;
	double angle;
	int width;
	int length;
	int border_1_2;
	int border_2_3;
	ROIGOStadiumLong (QGraphicsItem *parent = 0);
	virtual ~ROIGOStadiumLong ();
	void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
	virtual QRectF boundingRect () const;
	virtual void save_masks (const std::string &folder, int width, int height) const;
	virtual void save_properties (const std::string &folder) const;
public slots:
	void setCenter_x (int value);
	void setCenter_y (int value);
	void setAngle (int value);
	void setWidth (int value);
	void setLength (int value);
	void setBorder_1_2 (int value);
	void setBorder_2_3 (int value);
};

#endif // ROIGOSTADIUMLONG_H
