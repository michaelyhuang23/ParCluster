cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test_parlay test_parlay.cpp)
add_executable(density_query density_query.cpp)
add_executable(dependent_point_search dependent_point_search.cpp)

target_link_libraries(test_parlay
  parclusterLib
  )

target_link_libraries(density_query 
  parclusterLib
  )

target_link_libraries(dependent_point_search
  parclusterLib
  )