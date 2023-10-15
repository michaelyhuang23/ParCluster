
add_subdirectory(dataset)

add_library(dpc_sddp_cc STATIC dpc_sddp.cpp)
target_link_libraries(dpc_sddp_cc
  parDpc
  )



# ----------------- Nanobind to create python bindings -------------------------


find_package(Python 3 COMPONENTS Interpreter Development.Module REQUIRED)

# Configure CMake to perform an optimized release build by default unless 
# another build type is specified. Without this addition, binding code may 
# run slowly and produce large binaries.
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Detect the installed nanobind package and import it into CMake
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(
  par_dpc_ext
  python_bindings.cpp
)

target_link_libraries(par_dpc_ext PUBLIC dpc_sddp_cc)

# Ignore nanobind warnings (temporary)
get_property(
    nanobind_includes TARGET nanobind-static
    PROPERTY INTERFACE_INCLUDE_DIRECTORIES
)
set_target_properties(
    nanobind-static PROPERTIES
    FOLDER nanobind-static
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${nanobind_includes}"
)


# -------------------- Build package / exe ----------------------------------


if (NOT SKBUILD)

add_executable(dpc_sddp dpc_sddp_main.cpp)

target_link_libraries(dpc_sddp
  parDpc dpc_sddp_cc
)

else()

# Install python package using scikit-build
install(TARGETS par_dpc_ext LIBRARY DESTINATION par_dpc)

endif()