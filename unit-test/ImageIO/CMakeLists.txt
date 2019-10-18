cmake_minimum_required(VERSION 3.11)

project(ImageIOTest)

set(IMAGEIOTEST_INCS ${PROJECT_SOURCE_DIR}/include/ImageIOTest.h)

set(IMAGEIOTEST_SRCS ${PROJECT_SOURCE_DIR}/src/ImageIOTest.cpp
                     ${PROJECT_SOURCE_DIR}/src/main.cpp)

find_package(GTest CONFIG REQUIRED)
find_package(glog REQUIRED)

add_executable(ImageIOTest ${IMAGEIOTEST_INCS} ${IMAGEIOTEST_SRCS})

target_include_directories(
  ImageIOTest PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

target_link_libraries(ImageIOTest hvr_imageio GTest::gtest_main glog::glog)

set_property(TARGET ImageIOTest PROPERTY FOLDER ${CMAKE_PROJECT_NAME}/unit-test)

if(MSVC)
  add_custom_command(
    TARGET ImageIOTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/data/ImageIO
            ${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>/data/ImageIO)

elseif((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR CMAKE_COMPILER_IS_GNUCC
       OR CMAKE_COMPILER_IS_GNUCXX)

  file(GLOB IMAGEIOTEST_DATA ${PROJECT_SOURCE_DIR}/data/ImageIO/*)

  file(
    WRITE ${CMAKE_CURRENT_BINARY_DIR}/imageiodata.cmake
    "file(COPY ${IMAGEIOTEST_DATA} DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}/data/ImageIO
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_WRITE GROUP_READ WORLD_READ)")

  add_custom_command(
    TARGET ImageIOTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/imageiodata.cmake)
endif()
