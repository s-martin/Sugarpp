
add_library(${PROJECT_NAME} STATIC 
                                    CXXWinApi.cpp
                                    File.cpp
                                    SppString.cpp
                                    XmlParser.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../include)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

#target_link_libraries(${PROJECT_NAME} PUBLIC Boost::filesystem)

target_link_libraries(${PROJECT_NAME} PRIVATE xerces_xerces-c XercesC::XercesC)
