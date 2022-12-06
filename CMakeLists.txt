cmake_minimum_required(VERSION 3.23)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(minesweeper minesweeper.cpp minesweeper.h Toolbox.cpp Toolbox.h Button.cpp Button.h Tile.cpp Tile.h GameState.cpp GameState.h MineTile.cpp MineTile.h ImageHelper.cpp ImageHelper.h Constants.h)
target_link_libraries(minesweeper sfml-graphics sfml-audio)
