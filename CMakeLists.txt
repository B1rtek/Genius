cmake_minimum_required(VERSION 3.10)
project(Genius)

set(CMAKE_CXX_STANDARD 17)

set(PATH_TO_QT5 "D:\\Kody\\Qt5\\5.15.2\\mingw81_64") # path to your Qt5 directory goes here
if (WIN32)
    set(CMAKE_PREFIX_PATH ${PATH_TO_QT5})
endif (WIN32)

find_package(Qt5Widgets REQUIRED)

set(GUI_SOURCE_FILES src/Genius.cpp include/Genius.h src/WordleButton.cpp include/WordleButton.h src/WordleWord.cpp include/WordleWord.h src/GeniusWindow.cpp include/GeniusWindow.h src/WordlistLoader.cpp include/WordlistLoader.h)

add_executable(Genius-cli mainOld.cpp)
if (WIN32)
    set(EXECUTABLE_NAME "Genius-win32")
    add_executable(${EXECUTABLE_NAME} WIN32 main.cpp ${GUI_SOURCE_FILES})
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/WindowsQt5files ${CMAKE_CURRENT_BINARY_DIR})
endif (WIN32)
if (UNIX)
    set(EXECUTABLE_NAME "Genius-linux")
    add_executable(${EXECUTABLE_NAME} main.cpp ${GUI_SOURCE_FILES})
endif (UNIX)
target_include_directories(${EXECUTABLE_NAME} PRIVATE include)
target_link_libraries(${EXECUTABLE_NAME} Qt5::Widgets)