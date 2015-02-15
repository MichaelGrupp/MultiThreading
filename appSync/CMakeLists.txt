cmake_minimum_required(VERSION 2.6)

set(SUBPROJECT_NAME appSync)
project(${SUBPROJECT_NAME})

set(${SUBPROJECT_NAME}_VERSION_MAJOR 1)
set(${SUBPROJECT_NAME}_VERSION_MINOR 0)


# find dependencies:

find_package(Boost 1.50.0 COMPONENTS thread atomic program_options system filesystem REQUIRED)
if(Boost_FOUND)
  message(STATUS "Boost found at ${Boost_INCLUDE_DIRS}")
else(Boost_FOUND)
  message(FATAL_ERROR "Boost not found")
endif()


# Source and header files:
set(SOURCE
	synchronizedThreads.cpp
)

set(HEADERS
)

include_directories(${Boost_INCLUDE_DIRS})


add_executable(${SUBPROJECT_NAME} ${SOURCE} ${HEADERS})


target_link_libraries(${SUBPROJECT_NAME} ${Boost_LIBRARIES})

