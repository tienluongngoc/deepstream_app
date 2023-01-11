set(MODULE_NAME opencv)

find_package(OpenCV REQUIRED)

add_library(${MODULE_NAME} INTERFACE)
target_include_directories(${MODULE_NAME} INTERFACE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${MODULE_NAME} INTERFACE opencv_core opencv_highgui opencv_cudawarping opencv_imgcodecs opencv_cudaimgproc opencv_imgproc opencv_objdetect)
