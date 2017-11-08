#ifndef ABSTRACTROI_H
#define ABSTRACTROI_H

#include <string>

class AbstractROI
{
public:
	AbstractROI ();
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
};

#endif // ABSTRACTROI_H
