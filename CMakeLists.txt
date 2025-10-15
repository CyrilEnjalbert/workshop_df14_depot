cmake_minimum_required(VERSION 3.20)
project(MyWorkshopProject VERSION 0.1 LANGUAGES CXX)

# Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optionnel : build type par défaut
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Sources
add_subdirectory(src)

# Installer / packaging léger (copie docs dans package/install)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/docs DESTINATION share/${PROJECT_NAME}/docs)
