
add_subdirectory(dataset)

add_library(dpc_sddp_cc STATIC dpc_sddp.cpp)
target_link_libraries(dpc_sddp_cc
  parDpc
  )

add_executable(dpc_sddp dpc_sddp_main.cpp)

target_link_libraries(dpc_sddp
  parDpc dpc_sddp_cc
  )
