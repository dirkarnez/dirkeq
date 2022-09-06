cmake_minimum_required(VERSION 3.14)

project(dirkeq)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fftw3 REQUIRED PATHS "${FFTW3_ROOT}")



add_library(wavefile_lib STATIC IMPORTED)

set_property(
  TARGET wavefile_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE
)

set_target_properties(wavefile_lib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${WAVEFILE_LIB_ROOT}/lib/libwavefile_lib.a"
)
  
set_target_properties(wavefile_lib PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
)

target_include_directories(wavefile_lib INTERFACE "${WAVEFILE_LIB_ROOT}/include")


SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(${PROJECT_NAME}
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} FFTW3::fftw3 wavefile_lib)