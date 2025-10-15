cmake_minimum_required(VERSION 3.20)
project(WorkshopUploader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 auto-moc, auto-uic, auto-rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(WorkshopUploader
    src/main.cpp
    src/MainWindow.cpp
    src/GitUploader.cpp 
)


target_link_libraries(WorkshopUploader Qt6::Widgets)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIT2 REQUIRED libgit2)
target_include_directories(WorkshopUploader PRIVATE ${LIBGIT2_INCLUDE_DIRS})
target_link_libraries(WorkshopUploader Qt6::Widgets ${LIBGIT2_LIBRARIES})
