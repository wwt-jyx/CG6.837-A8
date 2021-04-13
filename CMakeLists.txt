cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)

project("CG")
SET(PROJECT_NAME CG)
SET(LIBRARY_NAME CGShared)
SET(PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
 message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
 message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)



## Our include directories.
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

## Generate our own shared library.
FILE(GLOB_RECURSE SRC_FILES src/*.cpp)
FILE(GLOB_RECURSE HEAD_FILES include/*.h)

ADD_LIBRARY(CGShared SHARED ${SRC_FILES})

## Specify executable source file.
ADD_EXECUTABLE(${PROJECT_NAME} src/main.cpp)

## Add all link directories to project.
TARGET_LINK_LIBRARIES(${PROJECT_NAME} CGShared ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

