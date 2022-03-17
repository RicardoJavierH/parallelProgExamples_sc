cmake_minimum_required(VERSION 3.10)
project(SimpleMatrixBlockProduct)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

add_executable(SimpleMatrixBlockProduct main.cpp)

find_path(MKL_INCLUDE NAMES mkl.h PATHS ${SEARCH_DIRS} /opt/intel/mkl/include /softwares/intel/mkl/include)
		find_library(MKL_LIB_INTEL NAMES libmkl_intel_lp64.so libmkl_intel_lp64.dylib PATHS
				${SEARCH_DIRS} /opt/intel/mkl/lib /opt/intel/mkl/lib/intel64/ /softwares/intel/mkl/lib /softwares/intel/mkl/lib/intel64)
		find_library(MKL_LIB_CORE NAMES libmkl_core.so libmkl_core.dylib PATHS ${SEARCH_DIRS}
				/opt/intel/mkl/lib /opt/intel/mkl/lib/intel64/ /softwares/intel/mkl/lib /softwares/intel/mkl/lib/intel64/)
		find_library(MKL_LIB_THREAD NAMES libmkl_intel_thread.so libmkl_intel_thread.dylib PATHS
				${SEARCH_DIRS} /opt/intel/mkl/lib /opt/intel/mkl/lib/intel64/ /softwares/intel/mkl/lib /softwares/intel/mkl/lib/intel64/)
		find_library(COMPOSER_OMP NAMES libiomp5.so libiomp5.dylib PATHS ${SEARCH_DIRS}
				/opt/intel/composer_xe/compiler/lib
				/opt/intel/composerxe/lib/intel64
				/opt/intel/lib /softwares/intel/lib/intel64
                                /opt/intel/compilers_and_libraries/linux/lib/intel64_lin )

#find_package(MKL REQUIRED)

#if(MKL_FOUND)
#    include_directories(${MKL_INCLUDE_DIRS})
#    target_link_libraries(SimpleMatrixBlockProduct ${MKL_CORE_LIBRARY})
#else()
#   message(WARNING "MKL libs not found")
#endif()

target_link_libraries(SimpleMatrixBlockProduct ${MKL_LIB_INTEL} ${MKL_LIB_CORE} ${MKL_LIB_THREAD} ${COMPOSER_OMP})
target_include_directories(SimpleMatrixBlockProduct PUBLIC ${MKL_INCLUDE})
