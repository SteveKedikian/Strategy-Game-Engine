CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(rts_game.out)

add_executable(rts_game main.cpp headers/game/game.cpp headers/game/camera_view.cpp headers/maps/maps.cpp headers/game/auxiliary_functions.cpp headers/units/soldier.cpp headers/units/dark_legioner.cpp )

target_link_libraries(rts_game sfml-graphics sfml-window sfml-system)