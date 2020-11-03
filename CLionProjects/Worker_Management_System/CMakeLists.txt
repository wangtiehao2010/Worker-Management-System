cmake_minimum_required(VERSION 3.17)
project(WorkerManager)

set(CMAKE_CXX_STANDARD 14)

add_executable(WorkerManager workerManager.cpp workerManager.h workerManagementSystem.cpp worker.h employee.cpp employee.h manager.cpp manager.h boss.cpp boss.h)