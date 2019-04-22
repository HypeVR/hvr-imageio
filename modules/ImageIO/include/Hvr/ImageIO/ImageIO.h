// Copyright 2019 Achal Shah

#ifndef MODULES_IMAGEIO_INCLUDE_HVR_IMAGEIO_IMAGEIO_H_
#define MODULES_IMAGEIO_INCLUDE_HVR_IMAGEIO_IMAGEIO_H_

#include <map>
#include <string>

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "opencv2/opencv.hpp"
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
namespace ImageIO
{
/**
 * @brief      Reads an exiv data without reading image.
 *
 * @param[in]  inp_file   The inp file
 * @param      exiv_data  The exiv data
 *
 * @return     { returns the status of read op, true if success, false
 * otherwise}
 */
HVR_IMAGEIO_DLL bool ReadExiv(const std::string &inp_file,
                              std::map<std::string, std::string> &exiv_data);

/**
 * @brief      Reads an image exiv.
 *
 * @param[in]  inp_file     The inp file
 * @param[in]  imread_flag  The opencv imread flag
 * @param      exiv_data    The exiv data
 *
 * @return     { return image in opencv Mat format }
 */
HVR_IMAGEIO_DLL cv::Mat ReadImageExiv(
    const std::string &inp_file,
    const int &imread_flag,
    std::map<std::string, std::string> &exiv_data);

/**
 * @brief      Writes an image exiv.
 *
 * @param[in]  out_file   The out file
 * @param[in]  img        The image
 * @param[in]  exiv_data  The exiv data(Key should start with Xmp.hvr as we are
 * registering namespace hvr)
 *
 * @return     { returns the status of write op, true if success, false
 * otherwise }
 */
HVR_IMAGEIO_DLL bool WriteImageExiv(
    const std::string &out_file,
    const cv::Mat &img,
    const std::map<std::string, std::string> &exiv_data);

}  // namespace ImageIO

}  // namespace hvr

#endif  // MODULES_IMAGEIO_INCLUDE_HVR_IMAGEIO_IMAGEIO_H_
