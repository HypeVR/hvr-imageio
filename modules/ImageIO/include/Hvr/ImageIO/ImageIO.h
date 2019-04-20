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
HVR_IMAGEIO_DLL cv::Mat ReadImageExiv(
    const std::string &inp_file,
    const int &imread_flag,
    std::map<std::string, std::string> exiv_data);

HVR_IMAGEIO_DLL bool WriteImageExiv(
    const std::string &out_file,
    const cv::Mat &img,
    std::map<std::string, std::string> exiv_data);

}  // namespace ImageIO

}  // namespace hvr

#endif  // MODULES_IMAGEIO_INCLUDE_HVR_IMAGEIO_IMAGEIO_H_
