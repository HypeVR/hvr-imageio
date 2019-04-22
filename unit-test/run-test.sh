cdir=$(pwd)
REPO_NAME=$(grep -F project CMakeLists.txt | cut -f 2 -d '(' | cut -f 1 -d ' ')
echo $REPO_NAME

H_FILES=$(find modules -name "*.h" | cut -d"/" -f4-$6)
echo "${H_FILES}"
rm -rf build
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=install/ ..
make
libs=$(find modules -name *.so | xargs -n 1 basename | cut -f 1 -d '.'| cut -c 4-)
find ./unit-test/ -executable -type f -not -path "./unit-test/gtest-download/*" | xargs -n 1 cuda-memcheck --leak-check full --error-exitcode 1
find ./unit-test/ -executable -type f -not -path "./unit-test/gtest-download/*" -print0 | xargs -0 -I {} bash -c 'valgrind --tool=memcheck --leak-check=yes --show-reachable=no --undef-value-errors=no --track-origins=no --child-silent-after-fork=no --trace-children=no --gen-suppressions=no --show-possibly-lost=no --xml=yes --xml-file="unit-test/${1##*/}.%p.valgrind" "$1"' - {}
make install
mkdir installtest
cd installtest
touch main.cpp
for h_file in ${H_FILES}
do
    fstatus=$(find ../install -name  `basename ${h_file}`| wc -l)
    if [ $fstatus != 1 ]; then
        echo "Files not installed: ${h_file}"
    fi
done
mkdir build
echo 'cmake_minimum_required(VERSION 3.11)' >> CMakeLists.txt
echo 'project(Example)' >> CMakeLists.txt
echo 'set(PROJECT_SRCS ${PROJECT_SOURCE_DIR}/main.cpp)' >> CMakeLists.txt
echo "find_package(${REPO_NAME} REQUIRED)" >> CMakeLists.txt
echo 'add_executable(${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_INCS})' >> CMakeLists.txt
for LIB_NAME in ${libs}
do
    echo "target_link_libraries(\${PROJECT_NAME} hvr::${LIB_NAME})" >> CMakeLists.txt
done

cd build
cmake -DCMAKE_INSTALL_PREFIX=../../install/ ..
