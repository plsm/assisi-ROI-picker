#ifndef BASEROIPICKER_H
#define BASEROIPICKER_H

#include <string>
#include <map>
#include <opencv2/core/core.hpp>

#include <QWidget>
#include <QGraphicsScene>
#include <QSpinBox>
#include <QGraphicsPixmapItem>
#include <QFileDialog>

#include "abstract-roi.hpp"

namespace Ui {
class BaseROIPicker;
}

class BaseROIPicker : public QWidget
{
	Q_OBJECT

public:
	QGraphicsScene *scene;
	QGraphicsPixmapItem *pixmap;
	cv::Mat image;
	explicit BaseROIPicker (QWidget *parent = NULL);
	std::map<std::string, QSpinBox *> spin_boxes;
	~BaseROIPicker();
	void set_roigo (AbstractROI *roigo);
	void add_spin_box (const char *label, int value, int min, int max, const QObject *object, const char *slot);
	void set_image (const std::string &image_filename);
public slots:
	void selectImage ();
	void createROIMasks ();
	void update_graphics (int);
private:
	std::string folder;
	Ui::BaseROIPicker *ui;
	AbstractROI *roigo;
};

#endif // BASEROIPICKER_H
