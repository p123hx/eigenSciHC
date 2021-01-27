cmake_minimum_required(VERSION 3.15)
project(scHiCEigen)
add_definitions(-DHAVE_CBLAS=1)
find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(xtensor-blas REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_executable(scHiCEigen embedding/reproducibility.cpp embedding/reproducibility.h load/ContactMaps.cpp load/ContactMaps.h load/load_hic_file.cpp load/load_hic_file.h embedding/embedding.cpp embedding/embedding.h test/test_reproducibility.cpp load/processing_utils.h load/processing_utils.cpp test/test_all.cpp)
if (MSVC)
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif ()
target_link_libraries(scHiCEigen xtensor xtensor::optimize -march=native xtensor-blas Eigen3::Eigen)



