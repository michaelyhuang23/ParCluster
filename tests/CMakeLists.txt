cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test_parlay test_parlay.cpp)
add_executable(density_query density_query.cpp)
add_executable(dep_ptr dep_ptr.cpp)
add_executable(dep_ptr_brute dep_ptr_brute.cpp)
add_executable(static_dep_ptr static_dep_ptr.cpp)

target_link_libraries(test_parlay
  parclusterLib
  )

target_link_libraries(density_query 
  parclusterLib
  )

target_link_libraries(dep_ptr_brute
  parclusterLib
  )

target_link_libraries(dep_ptr
  parclusterLib
  )

target_link_libraries(static_dep_ptr
  parclusterLib
  )
