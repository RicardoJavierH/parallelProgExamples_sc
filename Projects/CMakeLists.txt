cmake_minimum_required(VERSION 3.10)
project(ParalelizationProjects)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(atomicVariableTest)

add_subdirectory(mulMKL)
add_subdirectory(mulMKL_Threads)
add_subdirectory(MultWithBlocks)
add_subdirectory(simpleMultDGEMM)
add_subdirectory(MatrixProductThreads)
add_subdirectory(SimpleMatrixBlockProduct)
add_subdirectory(MatrixBlockProductMultithread)

add_subdirectory(TBBsimpleSeriesSum)
add_subdirectory(TBBLeibnizSeriesSum)
add_subdirectory(TBBexperiments1)
add_subdirectory(TBBexperiments2)
add_subdirectory(TBBexperiments3)
add_subdirectory(TBBexperiments4A)
add_subdirectory(TBBexperiments4B)
add_subdirectory(TBB_task_group)
add_subdirectory(TBB_parallel_invoke)
add_subdirectory(TBB_parallel_for1)
add_subdirectory(MatrixBlockProductMultithread_TBB_MKL)

add_subdirectory(ompintro1)
add_subdirectory(ompintro2)
add_subdirectory(ompintro3)
add_subdirectory(ompintro4)
add_subdirectory(ompintro5)















