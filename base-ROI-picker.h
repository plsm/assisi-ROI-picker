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
	void add_spin_box (const char *label, int min, int max, const QObject *object, const char *slot);
	void set_image (const std::string &image_filename);
public slots:
	void selectBackgroundImage ();
	void update_graphics (int);
private:
	Ui::BaseROIPicker *ui;
	QFileDialog *file_dialog;
};

#endif // BASEROIPICKER_H
