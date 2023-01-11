set(MODULE_NAME yolov5_parser)
enable_language(CUDA)
file(GLOB SOURCE_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*[.h, .cc, .cu, .hpp, .cpp]")

add_library(${MODULE_NAME} SHARED ${SOURCE_LIST})
target_link_libraries(${MODULE_NAME} PUBLIC cuda gstreammer nvds_common config opencv)
target_compile_features(${MODULE_NAME} PUBLIC cxx_std_20)

add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/libs/custom_libs"
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${MODULE_NAME}> "${PROJECT_SOURCE_DIR}/libs/custom_libs"
)

