#ifndef ABSTRACTROI_H
#define ABSTRACTROI_H

#include <string>

class AbstractROI
{
protected:
	AbstractROI ();
public:
	static const std::string ROI_PROPERTIES_FILENAME;
	/**
	 * @brief save_masks Creates png files that represent the regions of interest
	 * that the user selected. These png files are masks that are used to select
	 * pixels that belong to a particular region of interest. dsad
	 *
	 * @param folder Folder where the ROI files are created
	 * @param width Width in pixels of the image
	 * @param height Height in pixels of the image
	 */
	virtual void save_masks (const std::string &folder, int width, int height) const = 0;
	/**
	 * @brief save_properties Saves the properties of the regions of interest that
	 * the user selected to a file name roi.properties.
	 *
	 * @param folder The folder where the file named roi.properties is saved.
	 */
	virtual void save_properties (const std::string &folder) const = 0;
};

#endif // ABSTRACTROI_H
