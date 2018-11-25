cmake_minimum_required(VERSION 3.12)
project(KingOfNewYork_A4)

set(CMAKE_CXX_STANDARD 14)

include_directories(KingOfNewYork_A4)
include_directories(KingOfNewYork_A4/nlohmann)
include_directories(maps)
include_directories(maps/fake_directory)

add_executable(KingOfNewYork_A4
        KingOfNewYork_A4/deck_info/cards.json
        KingOfNewYork_A4/nlohmann/json.hpp
        KingOfNewYork_A4/aggressive_strategy.cpp
        KingOfNewYork_A4/aggressive_strategy.h
        KingOfNewYork_A4/dice_rolling.cpp
        KingOfNewYork_A4/dice_rolling.h
        KingOfNewYork_A4/engine.cpp
        KingOfNewYork_A4/engine.h
        KingOfNewYork_A4/human_strategy.cpp
        KingOfNewYork_A4/human_strategy.h
        KingOfNewYork_A4/input.cpp
        KingOfNewYork_A4/input.h
        KingOfNewYork_A4/main.cpp
        KingOfNewYork_A4/map.cpp
        KingOfNewYork_A4/map.h
        KingOfNewYork_A4/map_finder.cpp
        KingOfNewYork_A4/map_finder.h
        KingOfNewYork_A4/map_loader.cpp
        KingOfNewYork_A4/map_loader.h
        KingOfNewYork_A4/moderate_strategy.cpp
        KingOfNewYork_A4/moderate_strategy.h
        KingOfNewYork_A4/observer.cpp
        KingOfNewYork_A4/observer.h
        KingOfNewYork_A4/player.cpp
        KingOfNewYork_A4/player.h
        KingOfNewYork_A4/player_view.cpp
        KingOfNewYork_A4/player_view.h
        KingOfNewYork_A4/power_cards.cpp
        KingOfNewYork_A4/power_cards.h
        KingOfNewYork_A4/resolve.cpp
        KingOfNewYork_A4/resolve.h
        KingOfNewYork_A4/statistics_view.cpp
        KingOfNewYork_A4/statistics_view.h
        KingOfNewYork_A4/strategy.cpp
        KingOfNewYork_A4/strategy.h
        KingOfNewYork_A4/subject.cpp
        KingOfNewYork_A4/subject.h
        KingOfNewYork_A4/tiles.cpp
        KingOfNewYork_A4/tiles.h
        KingOfNewYork_A4/tokens.cpp
        KingOfNewYork_A4/tokens.h
        maps/fake_directory/dir_faulty2.map
        maps/faulty.map
        maps/newyork.map
        maps/Untitled.txt)
