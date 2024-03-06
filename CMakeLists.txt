cmake_minimum_required(VERSION 3.10)
project(popcat_help_you_search)

# Find the Qt libraries
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Set include directories
include_directories(
    include  # Add your include directory here
)

############################################################

# Create target for popcat_help_you_search executable
add_executable(popcat_help_you_search
    src/main.cpp
    src/searchServer.cpp
    src/search.cpp
)


# Link Qt libraries
target_link_libraries(popcat_help_you_search PRIVATE Qt5::Core Qt5::Widgets)

############################################################

# Create target for lala executable
add_executable(lala
    src/lala.cpp
    # src/mainwindow.cpp  # You don't need to include this again if it's already included in popcat_help_you_search
)

# Link Qt libraries
target_link_libraries(lala PRIVATE Qt5::Core Qt5::Widgets)
