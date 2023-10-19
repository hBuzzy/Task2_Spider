cmake_minimum_required(VERSION 3.26)
project(l4)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Code/C++/qt6/qt6-static/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(
        COPY assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

include_directories(src)

add_executable(l4 main.cpp
        src/spider/spider.cpp
        src/widget/widget.cpp
        src/limited_queue.hpp)

target_link_libraries(l4
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
