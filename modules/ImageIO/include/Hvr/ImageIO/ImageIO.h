// Copyright 2015 Jason Juang

#ifndef MODULES_IMAGEIO_INCLUDE_HVR_IMAGEIO_IMAGEIO_H_
#define MODULES_IMAGEIO_INCLUDE_HVR_IMAGEIO_IMAGEIO_H_

#include <string>

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "opencv2/opencv.hpp"
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
/**
 * @brief      Image IO class
 *
 * @ingroup    ImageIO
 * @author     Jason Juang
 * @attention  This is for internal use only, DO NOT distribute the code
 */
class ImageIO
{
 public:
  ImageIO();
  ~ImageIO();
};

}  // namespace hvr

#endif  // MODULES_IMAGEIO_INCLUDE_HVR_IMAGEIO_IMAGEIO_H_
