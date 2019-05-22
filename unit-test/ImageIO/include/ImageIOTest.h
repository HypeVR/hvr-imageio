// Copyright 2019 HypeVR

#ifndef UNIT_TEST_IMAGEIO_INCLUDE_IMAGEIOTEST_H_
#define UNIT_TEST_IMAGEIO_INCLUDE_IMAGEIOTEST_H_

#include <string>

#include "gtest/gtest.h"

class ImageIOTest : public ::testing::Test
{
 protected:
  ImageIOTest();
  ~ImageIOTest() override;

  void SetUp() override;
  void TearDown() override;
};

#endif  // UNIT_TEST_IMAGEIO_INCLUDE_IMAGEIOTEST_H_
