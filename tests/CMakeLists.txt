cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test_parlay test_parlay.cpp)
add_executable(density_query density_query.cpp)
add_executable(density_query_brute density_query_brute.cpp)
add_executable(density_query_divcount density_query_divcount.cpp)
add_executable(dep_ptr_dyn dep_ptr_dyn.cpp)
add_executable(dep_ptr_brute dep_ptr_brute.cpp)
add_executable(dep_ptr_static_batch dep_ptr_static_batch.cpp)
add_executable(dep_ptr_static dep_ptr_static.cpp)
add_executable(dep_ptr_priority dep_ptr_priority.cpp)
add_executable(dep_ptr_par dep_ptr_par.cpp)
add_executable(dpc_divcount dpc_divcount.cpp)
add_executable(dpc_priority dpc_priority.cpp)
add_executable(dpc_alternate dpc_alternate.cpp)
add_executable(dpc_static dpc_static.cpp)
add_executable(dpc_fenwick dpc_fenwick.cpp)

add_executable(uniform_generator uniform_generator.cpp)
add_executable(seedspread_generator seedspread_generator.cpp)

target_link_libraries(test_parlay
  parDpc
  )

target_link_libraries(density_query 
  parDpc
  )

target_link_libraries(density_query_brute
  parDpc
  )

target_link_libraries(density_query_divcount 
  parDpc
  )

target_link_libraries(dep_ptr_brute
  parDpc
  )

target_link_libraries(dep_ptr_dyn
  parDpc
  )

target_link_libraries(dep_ptr_static_batch
  parDpc
  )

target_link_libraries(dep_ptr_static
  parDpc
  )

target_link_libraries(dep_ptr_par
  parDpc
  )
  
target_link_libraries(dep_ptr_priority
  parDpc
  )

target_link_libraries(dpc_divcount
  parDpc
  )

target_link_libraries(dpc_priority
  parDpc
  )

target_link_libraries(dpc_alternate
  parDpc
  )

target_link_libraries(dpc_static
  parDpc
  )

target_link_libraries(dpc_fenwick
  parDpc
  )

target_link_libraries(uniform_generator
  parDpc
  )

target_link_libraries(seedspread_generator
  datasetLib
  parDpc
  )




