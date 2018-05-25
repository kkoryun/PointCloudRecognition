cmake_minimum_required(VERSION 2.8)

project(kdTree)

#MESSAGE(${ROOTPATH})


#set(HEADER_DIR ./Header)
#include_directories(kdTree PUBLIC ${ROOTPATH} )

set(HEADERS    	kdTree.h
		#${ROOTPATH}/pc_struct.h
		)

set(SOURCES )
#add_library(data_parser STATIC ${SOURCES} ${HEADERS})

add_executable(kdTree main.cpp ${SOURCES} ${HEADERS})


