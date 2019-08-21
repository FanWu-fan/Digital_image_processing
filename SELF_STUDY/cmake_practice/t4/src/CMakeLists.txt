ADD_EXECUTABLE(main main.cpp)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#INCLUDE_DIRECTORIES(/tmp/t3/include/hello)

FIND_PATH(myHeader hello.h)
IF(myHeader)
MESSAGE(STATUS "This is hello.h -->" ${myHeader})
INCLUDE_DIRECTORIES(${myHeader})
ENDIF(myHeader)

#TARGET_LINK_LIBRARIES(main /tmp/t3/lib/libhello.so)

FIND_LIBRARY(mylib hello)
IF(mylib)
MESSAGE(STATUS "This is mylib.so -->" ${mylib})
TARGET_LINK_LIBRARIES(main ${mylib})
ENDIF(mylib)
