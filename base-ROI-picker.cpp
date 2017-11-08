#include <libgen.h>
#include <QLabel>
#include <QFormLayout>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "base-ROI-picker.h"
#include "ui_base-ROI-picker.h"

QImage Mat2QImage (const cv::Mat &image);

BaseROIPicker::BaseROIPicker (QWidget *parent):
   QWidget(parent),
   scene (new QGraphicsScene ()),
   pixmap (new QGraphicsPixmapItem ()),
   folder ("./"),
   ui (new Ui::BaseROIPicker),
   roigo (NULL)
{
	ui->setupUi(this);
	ui->graphicsView->setScene (scene);
	scene->addItem (this->pixmap);
}

BaseROIPicker::~BaseROIPicker()
{
	delete ui;
}

void BaseROIPicker::set_image (const std::string &image_filename)
{
	this->image = cv::imread (image_filename, CV_LOAD_IMAGE_GRAYSCALE);
	this->pixmap->setPixmap (QPixmap::fromImage (Mat2QImage (this->image)));
	this->ui->graphicsView->update ();
}

void BaseROIPicker::add_spin_box (const char *text, int value, int min, int max, const QObject *object, const char *slot)
{
	QLabel *label = new QLabel (this->ui->propertiesWidget);
	label->setText (text);
	label->setObjectName (text);
	QSpinBox *spin_box = new QSpinBox (this->ui->propertiesWidget);
	spin_box->setObjectName (text);
	spin_box->setValue (value);
	spin_box->setMinimum (min);
	spin_box->setMaximum (max);
	this->ui->formLayout->insertRow (this->ui->formLayout->rowCount () - 1, label, spin_box);
	QObject::connect (spin_box, SIGNAL (valueChanged(int)), object, slot);
	QObject::connect (spin_box, SIGNAL (valueChanged(int)), this, SLOT (update_graphics(int)));
	this->spin_boxes [text] = spin_box;
}

void BaseROIPicker::set_roigo (AbstractROI *roigo)
{
	if (this->roigo == NULL) {
		this->roigo = roigo;
	}
	else {
		fprintf (stderr, "ROI picker already has a region of interest graphical object\n");
	}
}

void BaseROIPicker::update_graphics (int)
{
	this->ui->graphicsView->update ();
}

//void DialogRunParameters::selectVideoWithBackgroundImage ()
//{
//	this->file_dialog->setViewMode (QFileDialog::List);
//	this->file_dialog->setOption (QFileDialog::ShowDirsOnly, false);
//	this->file_dialog->setFileMode (QFileDialog::ExistingFiles);
//	int return_code = this->file_dialog->exec ();
//	if (return_code == QDialog::Accepted) {
//		QStringList strings = this->file_dialog->selectedFiles ();
//		this->ui->backgroundImageLineEdit->setText (strings.at (0));
//	}
//}

void BaseROIPicker::selectImage ()
{
	QFileDialog *file_dialog = new QFileDialog ();
	file_dialog->setDirectory (this->folder.c_str ());
	file_dialog->setViewMode (QFileDialog::List);
	file_dialog->setOption (QFileDialog::ShowDirsOnly, false);
	file_dialog->setFileMode (QFileDialog::ExistingFiles);
	int return_code = file_dialog->exec ();
	if (return_code == QDialog::Accepted) {
		QStringList strings = file_dialog->selectedFiles ();
		std::string filename = strings.at (0).toStdString ();
		this->set_image (filename);
		char *copy = new char [filename.size ()];
		strcpy (copy, filename.c_str ());
		this->folder = dirname (copy);
		delete copy;
	}
}

void BaseROIPicker::createROIMasks ()
{
	std::cout << "void BaseROIPicker::createROIMasks ()\n";
	std::cout << "[" << folder << "]\n";
	this->roigo->save_masks (folder, this->image.size ().width, this->image.size ().height);
	this->roigo->save_properties (folder);
}

QImage Mat2QImage (const cv::Mat &image)
{
	QImage dest (image.cols, image.rows, QImage::Format_ARGB32);
	for (int y = 0; y < image.rows; ++y) {
		for (int x = 0; x < image.cols; ++x) {
			unsigned int color = image.at<unsigned char> (y, x);
			dest.setPixel (x, y, qRgba (color, color, color, 255));
		}
	}
	return dest;
}


QImage Mat2QImage (const cv::Mat &image, const cv::Mat &mask)
{
	QImage dest (image.cols, image.rows, QImage::Format_ARGB32);
	for (int y = 0; y < image.rows; ++y) {
		for (int x = 0; x < image.cols; ++x) {
			unsigned char visible = mask.at<unsigned char> (y, x);
			if (visible != 0) {
				unsigned int color = image.at<unsigned char> (y, x);
				dest.setPixel (x, y, qRgba (color, color, color, 255));
			}
			else {
				dest.setPixel (x, y, qRgba (0, 192, 0, 255));
			}
		}
	}
	return dest;
}
