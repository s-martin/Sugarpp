cmake_minimum_required(VERSION 3.1...3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.13)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.13)
endif()

project(Sugar++ VERSION 0.1
                  DESCRIPTION "Syntactic sugar and helpers for C++"
                  LANGUAGES CXX)
		  
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if(MSVC)
    add_definitions("/W4 /D_CRT_SECURE_NO_WARNINGS /permissive-")
else()
    add_definitions("-Wall -Wextra")
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.71 REQUIRED COMPONENTS log log_setup unit_test_framework)
message(STATUS "Boost version: ${Boost_VERSION}")


find_package(XercesC REQUIRED)
message(STATUS "Xerces-C version: ${XercesC_VERSION}")

                  
# This is needed if your Boost version is newer than your CMake version
# or if you have an old version of CMake (<3.5)
#if(NOT TARGET Boost::filesystem)
#    add_library(Boost::filesystem IMPORTED INTERFACE)
#    set_property(TARGET Boost::filesystem PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
#    set_property(TARGET Boost::filesystem PROPERTY INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
#endif()
                  
enable_testing()
include(CTest)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
	APPEND_COVERAGE_COMPILER_FLAGS()
	# TODO fix not working excludes in project
	set(COVERAGE_LCOV_EXCLUDES 'test/*' '/usr/*')
    SETUP_TARGET_FOR_COVERAGE_LCOV(NAME ${PROJECT_NAME}_lcov EXECUTABLE ${PROJECT_NAME}Test)
	SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(NAME ${PROJECT_NAME}_gcov EXECUTABLE ${PROJECT_NAME}Test)
else()
	# TODO
	#add_custom_target(${PROJECT_NAME}coverage COMMAND "opencppcoverage --working_dir ${CMAKE_CURRENT_BINARY_DIR}/test -- ${CMAKE_CURRENT_BINARY_DIR}/test/Sugar++Test.exe")
endif()

# copy test data
file(COPY test-data/test.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/test-data)
file(COPY test-data/test.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/test-data)

add_subdirectory(src)
add_subdirectory(test)









