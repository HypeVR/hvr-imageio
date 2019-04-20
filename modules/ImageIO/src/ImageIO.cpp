// Copyright 2019 Achal Shah

#include "Hvr/ImageIO/ImageIO.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "exiv2/exiv2.hpp"
#include "opencv2/opencv.hpp"
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
cv::Mat ReadImageExiv(const std::string &inp_file,
                      const int &imread_flag,
                      std::map<std::string, std::string> exiv_data)
{
  cv::Mat img = cv::imread(inp_file, imread_flag);

  // Read exiv metadata
  Exiv2::Image::UniquePtr exiv_img = Exiv2::ImageFactory::open(inp_file);
  exiv_img->readMetadata();
  Exiv2::XmpData &xmpData = exiv_img->xmpData();

  for (Exiv2::XmpMetadata::const_iterator it = xmpData.begin();
       it != xmpData.end();
       ++it)
  {
    exiv_data.insert(
        std::pair<std::string, std::string>(it->key(), it->value().toString()));
  }

  return img;
}

bool WriteImageExiv(const std::string &out_file,
                    const cv::Mat &img,
                    std::map<std::string, std::string> exiv_data)
{
  // This will get the file extension from the out file
  std::string file_ext = out_file.substr(out_file.find('.'), out_file.size());
  Exiv2::XmpData xmpData;

  // map to XMPData
  for (auto &it : exiv_data)
  {
    xmpData[it.first] = it.second;
  }

  std::vector<uchar> cvbuff;
  cv::imencode(file_ext, img, cvbuff, std::vector<int>());

  Exiv2::Image::UniquePtr exiv_img =
      Exiv2::ImageFactory::open(&cvbuff[0], static_cast<int>(cvbuff.size()));

  if (exiv_img.get() != nullptr)
  {
    exiv_img->setXmpData(xmpData);
    exiv_img->writeMetadata();

    // copy the library buffer to buff
    const auto buffersize = static_cast<int>(exiv_img->io().size());

    exiv_img->io().seek(0, Exiv2::BasicIo::beg);

    Exiv2::DataBuf buff = exiv_img->io().read(buffersize);

    std::ofstream file_wrt(
        out_file.c_str(),
        std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

    auto conv_buff = reinterpret_cast<char *>(buff.pData_);

    file_wrt.write(conv_buff, buffersize);
  }
  else
  {
    return false;
  }

  return true;
}

}  // namespace hvr
