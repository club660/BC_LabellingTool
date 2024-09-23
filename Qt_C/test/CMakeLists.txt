file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(Qt_test ${SRCS})
target_link_libraries(Qt_test Qt_C)