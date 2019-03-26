
add_executable(${PROJECT_NAME}Test main.cpp
                                    CXXWinApiTest.cpp
                                    FileTest.cpp
                                    SppStringTest.cpp
                                    XmlParserTest.cpp)

target_include_directories(${PROJECT_NAME}Test PUBLIC ../include)

target_compile_features(${PROJECT_NAME}Test PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME}Test PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME}Test PUBLIC Sugar++ Boost::filesystem Boost::unit_test_framework
                                                            version)

add_test(NAME "${PROJECT_NAME}Test" COMMAND "${PROJECT_NAME}Test" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")