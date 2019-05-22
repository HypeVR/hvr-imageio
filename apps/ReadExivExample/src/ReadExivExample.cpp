// Copyright 2019 HypeVR

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <mpi.h>
HVR_WINDOWS_ENABLE_ALL_WARNING

#include <array>
#include <string>

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "glog/logging.h"
#include "opencv2/opencv.hpp"
HVR_WINDOWS_ENABLE_ALL_WARNING

#include "Hvr/ImageIO/ImageIO.h"
#include "Hvr/XML/XMLParser.h"

template <class... Int>
std::string ParsePath(const std::string &path, const Int... index)
{
  if (path.find('%') != std::string::npos)
  {
    char buffer[4096];
    return std::string(
        buffer, std::snprintf(buffer, sizeof(buffer), path.c_str(), index...));
  }

  return path;
}

int main(int argc, char **argv)
{
  google::InitGoogleLogging(argv[0]);
  FLAGS_log_prefix = false;

#ifndef NDEBUG
  google::SetStderrLogging(google::GLOG_INFO);
  FLAGS_log_prefix = true;
#endif

  if (argc != 2 && argc != 4)
  {
    LOG(ERROR) << "Please input something like:";
    LOG(ERROR) << "/path/to/exiv_image.tif";
    return -1;
  }

  const std::string inp_file = argv[1];

  std::map<std::string, std::string> exiv_data;
  cv::Mat img = hvr::ImageIO::ReadImageExiv(inp_file, 1, exiv_data);

  for (auto &it : exiv_data)
  {
    LOG(INFO) << it.first << " : " << it.second << std::endl;
  }

  return 0;
}
