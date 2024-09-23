file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(Qt_C ${SRCS})

target_include_directories(Qt_C PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Qt_C PUBLIC
	Qt::Core
        Qt::Gui
        Qt::OpenGL
        Qt::Xml
        Qt::Network
        Qt::Widgets
	Qt::PrintSupport
        )

add_subdirectory(test)