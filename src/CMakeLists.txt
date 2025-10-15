# src/CMakeLists.txt
file(GLOB_RECURSE PROJECT_SOURCES *.cpp *.c)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Exemples : definitions pour Windows vs POSIX
if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WINDOWS)
else()
  target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_POSIX)
endif()

# Include dirs si besoin
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
