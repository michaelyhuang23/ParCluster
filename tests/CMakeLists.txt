cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Test_parlay test_parlay.cpp)
add_executable(Test_kdtree density_query.cpp)

target_link_libraries(Test_parlay
  parclusterLib
  )

target_link_libraries(Test_kdtree 
  parclusterLib
  )