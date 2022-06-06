cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test_parlay test_parlay.cpp)
add_executable(density_query density_query.cpp)
add_executable(dep_ptr_dyn dep_ptr_dyn.cpp)
add_executable(dep_ptr_brute dep_ptr_brute.cpp)
add_executable(dep_ptr_static_batch dep_ptr_static_batch.cpp)
add_executable(dep_ptr_static dep_ptr_static.cpp)
add_executable(dep_ptr_par dep_ptr_par.cpp)
add_executable(uniform_generator uniform_generator.cpp)
add_executable(seedspread_generator seedspread_generator.cpp)

target_link_libraries(test_parlay
  parclusterLib
  )

target_link_libraries(density_query 
  parclusterLib
  )

target_link_libraries(dep_ptr_brute
  parclusterLib
  )

target_link_libraries(dep_ptr_dyn
  parclusterLib
  )

target_link_libraries(dep_ptr_static_batch
  parclusterLib
  )

target_link_libraries(dep_ptr_static
  parclusterLib
  )

target_link_libraries(dep_ptr_par
  parclusterLib
  )


target_link_libraries(uniform_generator
  parclusterLib
  )

target_link_libraries(seedspread_generator
  datasetLib
  parclusterLib
  )




