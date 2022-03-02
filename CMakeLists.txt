cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME cpp-gstreamer-stream_to_localhost)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})

find_package(PkgConfig)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

include_directories(
	${GLIB_INCLUDE_DIRS}
	${GSTREAMER_INCLUDE_DIRS}
)

link_directories(
	${GLIB_INCLUDE_DIRS}
	${GSTREAMER_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} 
	src/main.cpp
)

target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES})

