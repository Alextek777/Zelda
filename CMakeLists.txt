cmake_minimum_required(VERSION 3.16)
project(Zelda)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the output directory for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set the output directory for archives (static libraries)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(COPY src/resources/game/rpgdata DESTINATION ${CMAKE_BINARY_DIR}/bin)

include_directories(src/libs)
include_directories(src/resources)

# Define sources and headers
# file(GLOB Sources src/*.cpp)
# file(GLOB Headers src/*.h)

# Define sources
set(Sources 
    src/main.cpp
    src/resources/menu/menu.cpp

    src/resources/game/RPG_Assets.cpp  
    src/resources/game/RPG_Commands.cpp  
    src/resources/game/RPG_Dynamics.cpp  
    src/resources/game/RPG_Engine.cpp  
    src/resources/game/RPG_Items.cpp  
    src/resources/game/RPG_Maps.cpp  
    src/resources/game/RPG_Quests.cpp
)

# Define headers
set(Headers 
    src/libs/olcPixelGameEngine.h
    src/resources/menu/menu.h
    src/resources/game/RPG_Assets.h  
    src/resources/game/RPG_Commands.h  
    src/resources/game/RPG_Dynamics.h  
    src/resources/game/RPG_Engine.h  
    src/resources/game/RPG_Items.h  
    src/resources/game/RPG_Maps.h  
    src/resources/game/RPG_Quests.h
)

add_executable(Zelda ${Sources} ${Headers})

target_link_libraries(Zelda -lpng -lGL -lX11)
