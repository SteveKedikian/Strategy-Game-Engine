CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(rts_game.out)

add_executable(rts_game main.cpp src/game_pve.cpp src/utility.cpp src/world_map/maps.cpp src/units/human.cpp src/units/soldier.cpp src/units/dark_legioner.cpp )

target_link_libraries(rts_game sfml-graphics sfml-window sfml-system)