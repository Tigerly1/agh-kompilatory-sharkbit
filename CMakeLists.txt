#CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
project("sharkbit")

CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

# required if linking to static library
#add_definitions(-DANTLR4CPP_STATIC)
# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

set(ANTLR_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/antlr.jar)
find_package(ANTLR REQUIRED)

antlr_target(sharkbit sharkbit.g4
    PACKAGE sharkbit
    LISTENER
    )

# include generated files in project environment
include_directories(${ANTLR_sharkbit_OUTPUT_DIR})

# add generated grammar to demo binary target
add_executable(sharkbit
sharkbit.cpp
${ANTLR_sharkbit_CXX_OUTPUTS})

target_link_libraries(sharkbit antlr4_shared)
add_custom_command(TARGET sharkbit
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                           -E copy ${ANTLR4_RUNTIME_LIBRARIES} .
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})