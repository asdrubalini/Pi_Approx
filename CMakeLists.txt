cmake_minimum_required(VERSION 3.0.0)
project(Pi_Approx VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Pi_Approx main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
