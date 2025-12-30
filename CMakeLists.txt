cmake_minimum_required(VERSION 3.10)
project(popcat_help_you_search CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# On macOS, ensure SDK is properly configured
if(APPLE)
    execute_process(COMMAND xcrun --show-sdk-path
                    OUTPUT_VARIABLE OSX_SDK_PATH
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(CMAKE_OSX_SYSROOT ${OSX_SDK_PATH})
    include_directories(SYSTEM "${OSX_SDK_PATH}/usr/include/c++/v1")
endif()

# Detect architecture
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|arm64)")
    set(ARCHITECTURE "arm64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)")
    set(ARCHITECTURE "x86")
else()
    message(FATAL_ERROR "Unknown architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

# Find the Qt libraries
set(CMAKE_AUTOMOC ON)

# Set Qt5 path for macOS Homebrew
if(APPLE)
    set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5" ${CMAKE_PREFIX_PATH})
endif()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Set include directories
include_directories(
    include  # Add your include directory here
)

############################################################

add_executable(popcat_help_you_search_${ARCHITECTURE}
    src/main.cpp
    src/searchServer.cpp
    src/searchNaiveLinear.cpp
    # src/searchHashTable.cpp
    # src/searchBinary.cpp
    # src/searchFuzzy.cpp
)


# Link Qt libraries
target_link_libraries(popcat_help_you_search_${ARCHITECTURE} PRIVATE Qt5::Core Qt5::Widgets)

############################################################

add_executable(lala_${ARCHITECTURE}
    src/lala.cpp
    # src/mainwindow.cpp  # You don't need to include this again if it's already included in popcat_help_you_search
)

# Link Qt libraries
target_link_libraries(lala_${ARCHITECTURE} PRIVATE Qt5::Core Qt5::Widgets)
