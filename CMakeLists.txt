project(FYOU)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
# find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
# find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(tWin
	src/Ball.h
	src/Ball.cpp
	src/Entity.h
	src/Entity.cpp
	src/Hole.h
	src/Hole.cpp
	src/Tile.h
	src/Tile.cpp
	src/RenderWindow.h
	src/RenderWindow.cpp
	src/Math.h
	src/main.cpp
	src/Game.h
	src/Game.cpp
)

target_link_libraries(tWin SDL2::Main SDL2::Mixer SDL2::Image SDL2::TTF)
