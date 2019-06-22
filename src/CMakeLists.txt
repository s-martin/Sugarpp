
add_library(${PROJECT_NAME} STATIC 
                                    CXXWinApi.cpp
                                    File.cpp
                                    SppString.cpp
									Tracing.cpp
                                    XmlParser.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../include)

target_include_directories(${PROJECT_NAME} PUBLIC ${XercesC_INCLUDE_DIRS})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
