set(MODULE_NAME nvds_common)
file(GLOB HEADER_LIST "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB SOURCE_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${MODULE_NAME} ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${MODULE_NAME} PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include" 
                                            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${MODULE_NAME} PUBLIC cuda gstreammer)
target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)
