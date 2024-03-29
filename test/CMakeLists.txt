
add_executable(${PROJECT_NAME}Test 
                    main.cpp
                    $<$<PLATFORM_ID:Windows>:CXXWinApiTest.cpp>
                    FileTest.cpp
                    SppStringTest.cpp
                    XmlParserTest.cpp)

target_include_directories(${PROJECT_NAME}Test PUBLIC ../include)

target_compile_features(${PROJECT_NAME}Test PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME}Test PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME}Test
    PUBLIC
        Sugar++ 
        Boost::filesystem 
        Boost::unit_test_framework 
        XercesC::XercesC
        $<$<PLATFORM_ID:Windows>:version>)
        
set(CMAKE_CTEST_ARGUMENTS "--rerun-failed;--output-on-failure")

add_test(NAME "${PROJECT_NAME}Test" COMMAND "${PROJECT_NAME}Test" --logger=JUNIT,message,${PROJECT_NAME}Test_results.xml WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
