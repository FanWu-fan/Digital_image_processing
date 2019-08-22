find_package(OpenCV REQUIRED)

MESSAGE(STATUS "OpenCV libary status:")
MESSAGE(STATUS " version: ${OpenCV_VERSION}")
MESSAGE(STATUS " libaries:${OpenCV_LIBS}")
MESSAGE(STATUS " include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(2_3 2_3.cpp)
target_link_libraries(2_3 ${OpenCV_LIBS})