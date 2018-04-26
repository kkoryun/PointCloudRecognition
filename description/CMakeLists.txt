cmake_minimum_required(VERSION 2.8)

project(description)

#MESSAGE(${ROOTPATH})


#set(HEADER_DIR ./Header)
include_directories(description PUBLIC ${ROOTPATH} )

set(HEADERS    	./normalsEstimation.h
		${ROOTPATH}/pc_struct.h
		)

set(SOURCES )
#add_library(data_parser STATIC ${SOURCES} ${HEADERS})

add_executable(description main.cpp ${SOURCES} ${HEADERS})

