cmake_minimum_required(VERSION 3.17)
project(LabellingTool LANGUAGES CXX)


#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(OpenGL)
find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL Xml Network Widgets)
find_package(Qt6PrintSupport REQUIRED)


#======================= INCLUSION OF Our Code ======================#
set(GUI_DIR "${CMAKE_SOURCE_DIR}/GUI")
set(CORE_DIR "${CMAKE_SOURCE_DIR}/CORE")


include_directories(${GUI_DIR})
include_directories(${CORE_DIR})


file(GLOB_RECURSE SOURCES
	"${CORE_DIR}/*"
        "${GUI_DIR}/*"
        )

# Add the executable
qt_add_executable(LabellingTool ${SOURCES})

set_target_properties(LabellingTool PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
        )

# Add the target includes
target_include_directories(LabellingTool PRIVATE ${GUI_DIR})
target_include_directories(LabellingTool PRIVATE ${CORE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(LabellingTool PUBLIC
        Qt::Core
        Qt::Gui
        Qt::OpenGL
        Qt::Xml
        Qt::Network
        Qt::Widgets
	    Qt::PrintSupport
        Qt_C
        )


#===================== Add SUBDIRECTORY =======================#

add_subdirectory(Qt_C)
