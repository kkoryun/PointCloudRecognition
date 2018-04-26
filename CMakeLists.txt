cmake_minimum_required(VERSION 2.8)

project(RecognitionPC)
set (ROOTPATH ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(data_parser)
add_subdirectory(kdTree)
add_subdirectory(description)

#target_link_libraries(${PROJECT_NAME} data_parser) 

set(OSG_LIB_PATH F:/library/OpenSceneGraph/Debug/lib)
set(OSG_LIBRARY ${OSG_LIB_PATH})
set(OSGVIEWER_LIBRARY ${OSG_LIB_PATH})
set(OSGGA_LIBRARY ${OSG_LIB_PATH})
set(OSGUTIL_LIBRARY ${OSG_LIB_PATH})
set(OSGMANIPULATOR_LIBRARY ${OSG_LIB_PATH})
set(OSG_INCLUDE_DIR F:/library/OpenSceneGraph/Debug/include)
set(OPENTHREADS_LIBRARY ${OSG_LIB_PATH})
set(OPENTHREADS_INCLUDE_DIR F:/library/OpenSceneGraph/Debug/include)

include_directories(${PROJECT_NAME} PUBLIC ${OSG_INCLUDE_DIR})

find_package(OpenSceneGraph COMPONENTS osg osgViewer osgGA osgUtil osgManipulator REQUIRED)

set(HEADERS ./scene.h
			./camera.h
			./pc_struct.h
			./userEventHandler.h
			#./kdTree.h
			)

set(SOURCES #./scene.cpp
			#./camera.cpp
			#./pc_struct.cpp
			#./userEventHandler.cpp
			)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})
#message( ${OSG_LIBRARY_DEBUG})
#message( ${OSGVIEWER_LIBRARY_DEBUG})
target_link_libraries(${PROJECT_NAME} debug ${OSG_LIBRARY_DEBUG} debug ${OSGVIEWER_LIBRARY_DEBUG} 
debug ${OSGGA_LIBRARY_DEBUG} debug ${OSGUTIL_LIBRARY_DEBUG} debug ${OSGMANIPULATOR_LIBRARY_DEBUG})