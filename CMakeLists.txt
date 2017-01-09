cmake_minimum_required(VERSION 3.6)
project(connect_4_bot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/board/Board.cpp
        src/board/Board.h
        src/board/BoardIterator.cpp
        src/board/BoardIterator.h
        src/bot/Bot.cpp
        src/bot/Bot.h
        src/bot/Minimax.cpp
        src/bot/Minimax.h
        src/utils/Utils.cpp
        src/utils/Utils.h
        src/main.cpp)

add_executable(connect_4_bot ${SOURCE_FILES})