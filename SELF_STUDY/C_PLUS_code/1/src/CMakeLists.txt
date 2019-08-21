ADD_EXECUTABLE(2_1 2_1.cpp)
FIND_PACKAGE(OpenCV REQUIRED)

MESSAGE(STATUS "OpenCV libary status:")
MESSAGE(STATUS " version: ${OpenCV_VERSION}")
MESSAGE(STATUS " libaries:${OpenCV_LIBS}")
MESSAGE(STATUS " include path: ${OpenCV_INCLUDE_DIRS}")

# Add OpenCV headers location to your include paths
include_directories(${OpenCV_INCLUDE_DIRS})


TARGET_LINK_LIBRARIES(2_1 )