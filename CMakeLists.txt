cmake_minimum_required(VERSION 3.8)

# Project name
project(projectm)

# set the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# path to vcpkg
set(CMAKE_TOOLCHAIN_FILE "D:/cpplibs/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Define the path to SFML
set(SFML_DIR "D:/cpp/sfml/SFML-2.6.1/lib/cmake/SFML")

# Find packages
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

# ADD the source files
set(SOURCES src/main.cpp  
            src/Window.cpp 
            src/EventHandler.cpp 
            src/InputHandler.cpp 
            src/Logger.cpp
 "src/LogConsole.cpp")

# Add the exe target
add_executable(projectm ${SOURCES})

# specify where to look for header files (include directories)
target_include_directories(projectm PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Locate and link SFML
#find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
#target_include_directories(projectm PRIVATE ${SFML_INCLUDE_DIR})

# link libraries
target_link_libraries(projectm PRIVATE sfml-graphics 
                                       sfml-window 
                                       sfml-system 
                                       spdlog::spdlog
                                       imgui::imgui
                                       ImGui-SFML::ImGui-SFML
)

# Copy needed dlls after building
add_custom_command(TARGET projectm POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "D:/cpp/sfml/SFML-2.6.1/bin" $<TARGET_FILE_DIR:projectm>)