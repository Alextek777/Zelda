cmake_minimum_required(VERSION 3.16)
project(Zelda)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the output directory for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set the output directory for archives (static libraries)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(src/libs)
include_directories(src/resources)

# Define sources and headers
# file(GLOB Sources src/*.cpp)
# file(GLOB Headers src/*.h)

# Define sources
set(Sources 
    src/main.cpp
    src/resources/menu/menu.cpp
)

# Define headers
set(Headers 
    src/libs/olcPixelGameEngine.h
    src/resources/menu/menu.h
)

add_executable(Zelda ${Sources} ${Headers})

target_link_libraries(Zelda -lpng -lGL -lX11)
