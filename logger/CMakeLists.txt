cmake_minimum_required(VERSION 2.8)

project(logger)

#MESSAGE(${ROOTPATH})



#set(HEADER_DIR ./Header)
#include_directories(logger PUBLIC ${ROOTPATH} )

set(HEADERS    	./logger.h
		#${ROOTPATH}/pc_struct.h
		)

set(SOURCES )
#add_library(data_parser STATIC ${SOURCES} ${HEADERS})

add_executable(logger main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} debug ${GTEST_LIBRARY})

