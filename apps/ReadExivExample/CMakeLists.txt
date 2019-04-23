cmake_minimum_required(VERSION 3.11)

project(ReadExivExample)

set(PROJECT_SRCS ${PROJECT_SOURCE_DIR}/src/ReadExivExample.cpp)

source_group("src" FILES ${PROJECT_SRCS})

find_package(hvr-xml REQUIRED)
find_package(MPI REQUIRED)
find_package(glog REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_SRCS})

target_link_libraries(${PROJECT_NAME}
                      hvr_imageio
                      hvr::hvr_xml
                      MPI::MPI_CXX
                      glog::glog)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${CMAKE_PROJECT_NAME}/apps)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        DESTINATION bin
        COMPONENT install-app)
