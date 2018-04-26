cmake_minimum_required(VERSION 2.8)

project(data_parser)

#MESSAGE(${ROOTPATH})


set(HEADER_DIR ./Header)
include_directories(data_parser PUBLIC ${ROOTPATH} ${HEADER_DIR} )

set(HEADERS ./Header/base_parser.h
			./Header/kitti_parser.h
			${ROOTPATH}/pc_struct.h
			)

set(SOURCES ./Source/base_parser.cpp
			./Source/kitti_parser.cpp)
#add_library(data_parser STATIC ${SOURCES} ${HEADERS})

add_executable(data_parser main.cpp ${SOURCES} ${HEADERS})

