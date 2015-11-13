PROJECT(simuvo)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
add_definitions(-std=c++11)

FIND_PACKAGE(VISP REQUIRED)
IF(VISP_FOUND)
  INCLUDE(${VISP_USE_FILE})
ENDIF(VISP_FOUND)

SET(SRC 
    kvisp.cpp
    Scene2D.cpp
    main.cpp
    )

SET(HDR
    kvisp.h
    Scene2D.h
    )

ADD_EXECUTABLE(simuvo ${SRC} ${HDR})
