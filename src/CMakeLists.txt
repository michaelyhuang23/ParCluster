
add_subdirectory(dataset)

add_executable(dpc_sddp dpc_sddp.cpp)

target_link_libraries(dpc_sddp
  parDpc
  )
