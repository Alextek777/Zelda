cmake_minimum_required(VERSION 3.16)

Project(Zelda)

set(Sources src/main.cpp)
set(Headers src/libs/olcPixelGameEngine.h)


add_executable( Zelda ${Sources} ${Headers} )

target_link_libraries(Zelda -lpng -lGL -lX11)