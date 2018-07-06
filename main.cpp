#include <QApplication>
#include <boost/program_options.hpp>
#include "picker-stadium-long.h"
#include "picker-stadium-standard.h"

using namespace std;
namespace po = boost::program_options;

#define PO_IMAGE "image"
#define PO_MASK_PREFIX "mask-prefix"
#define PO_MASK_SUFFIX "mask-suffix"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ROIStadiumStandard w;
	w.show();

	return a.exec();
}

po::options_description program_options ()
{
	po::options_description result ("Create masks to do image processing.");
	result.add_options ()
	      (
	         PO_IMAGE",i",
	         po::value<string> ()
	         ->default_value ("")
	         ->value_name ("FILENAME"),
	         "image to load"
	         )
	      (
	         PO_MASK_PREFIX",p",
	         po::value<string> ()
	         ->default_value ("")
	         ->value_name ("LABEL"),
	         "prefix to add to the mask filename"
	         )
	      (
	         PO_MASK_SUFFIX",p",
	         po::value<string> ()
	         ->default_value ("")
	         ->value_name ("LABEL"),
	         "suffix to add to the mask filename"
	         );
	return result;
}
