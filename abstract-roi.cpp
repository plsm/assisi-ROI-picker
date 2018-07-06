#include "abstract-roi.hpp"

const std::string AbstractROI::ROI_PROPERTIES_FILENAME = "roi.properties";

AbstractROI::AbstractROI()
{

}

std::string AbstractROI::mask_filename (const std::string &folder, const std::string &default_name, const std::vector<std::string> names, int index)
{
	if (names.size () > 0)
		return folder + "/" + names [index];
	else
		return folder + "/" + default_name;
}
