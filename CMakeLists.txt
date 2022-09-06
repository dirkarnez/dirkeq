cmake_minimum_required(VERSION 3.14)

project(fftw3-boilerplate)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fftw3 REQUIRED PATHS "${FFTW3_ROOT}")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

include_directories(${FFTW3_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} FFTW3::fftw3)