cmake_minimum_required(VERSION 3.15)

project(scHiCEigen)

add_definitions(-DHAVE_CBLAS=1)
find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(xtensor-blas REQUIRED)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
if (OPENMP_FOUND)
    message(OPENMP FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
add_executable(scHiCEigen embedding/reproducibility.cpp embedding/reproducibility.h load/ContactMaps.cpp load/ContactMaps.h load/load_hic_file.cpp load/load_hic_file.h test/test_reproducibility.cpp load/processing_utils.h load/processing_utils.cpp)
if (MSVC)
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif ()
target_link_libraries(scHiCEigen OpenMP::OpenMP_CXX xtensor xtensor::optimize -march=native xtensor-blas Eigen3::Eigen)

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
message(STATUS "BLAS VENDOR:    " ${BLA_VENDOR})
message(STATUS "BLAS LIBRARIES: " ${BLAS_LIBRARIES})

target_link_libraries(scHiCEigen ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})
target_include_directories(scHiCEigen PRIVATE ${xtensor_blas_INCLUDE_DIRS})
