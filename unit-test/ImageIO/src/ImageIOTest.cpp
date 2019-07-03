// Copyright 2019 HypeVR

#include "ImageIOTest.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "glog/logging.h"
#include "opencv2/opencv.hpp"
HVR_WINDOWS_ENABLE_ALL_WARNING

#include "Hvr/ImageIO/ImageIO.h"

extern std::string exe_path;

ImageIOTest::ImageIOTest() = default;

ImageIOTest::~ImageIOTest() = default;

void ImageIOTest::SetUp()
{
}

void ImageIOTest::TearDown()
{
}

TEST_F(ImageIOTest, ExivImgReadTest)
{
  std::map<std::string, std::string> exiv_data;
  cv::Mat img = hvr::ImageIO::ReadImageExiv(
      exe_path + "/data/ImageIO/face_viewlbl_exiv.tif", 1, exiv_data);

  for (auto &it : exiv_data)
  {
    if (it.first == "Xmp.hvr.frame_num")
    {
      ASSERT_EQ(it.second, "1");
    }
    else if (it.first == "Xmp.hvr.frontface_pod_num")
    {
      ASSERT_EQ(it.second, "POD02");
    }
  }
}

TEST_F(ImageIOTest, ExivReadWriteTest)
{
  cv::Mat img = cv::imread(exe_path + "/data/ImageIO/random_img.tif");

  std::map<std::string, std::string> exiv_data;
  exiv_data.insert(
      std::pair<std::string, std::string>("Xmp.hvr.key1", "value1"));
  exiv_data.insert(
      std::pair<std::string, std::string>("Xmp.hvr.key2", "value2"));

  hvr::ImageIO::WriteImageExiv("temp_out.tiff", img, exiv_data);

  // Reading file
  std::map<std::string, std::string> out_exiv_data;

  cv::Mat temp_out =
      hvr::ImageIO::ReadImageExiv("temp_out.tiff", 1, out_exiv_data);

  for (auto &it : out_exiv_data)
  {
    if (it.first == "Xmp.hvr.key1")
    {
      ASSERT_EQ(it.second, "value1");
    }
    else if (it.first == "Xmp.hvr.key2")
    {
      ASSERT_EQ(it.second, "value2");
    }
  }
}

TEST_F(ImageIOTest, ExivReadTest)
{
  std::map<std::string, std::string> exiv_data;
  bool status = hvr::ImageIO::ReadExiv(
      exe_path + "/data/ImageIO/face_viewlbl_exiv.tif", exiv_data);

  ASSERT_EQ(status, true);

  for (auto &it : exiv_data)
  {
    if (it.first == "Xmp.hvr.frame_num")
    {
      ASSERT_EQ(it.second, "1");
    }
    else if (it.first == "Xmp.hvr.frontface_pod_num")
    {
      ASSERT_EQ(it.second, "POD02");
    }
  }
}
