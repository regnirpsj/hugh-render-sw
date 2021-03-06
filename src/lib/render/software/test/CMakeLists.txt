# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED COMPONENTS unit_test_framework)

include_directories(SYSTEM ${Boost_INLCUDE_DIR})

set(SRC)
list(APPEND SRC pipeline_fixed_shared.cpp)

cma_setup_library(${LIB}_test_shared SOURCES ${SRC} STATIC NOINSTALL)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRC)
list(APPEND SRC attribute.cpp)
list(APPEND SRC context.cpp)
list(APPEND SRC fragment.cpp)
list(APPEND SRC line.cpp)
list(APPEND SRC triangle.cpp)
list(APPEND SRC pipeline_fixed_direct3d.cpp)
list(APPEND SRC pipeline_fixed_opengl.cpp)
list(APPEND SRC primitive_line_list.cpp)
list(APPEND SRC primitive_line_strip.cpp)
list(APPEND SRC primitive_point_list.cpp)
list(APPEND SRC primitive_triangle_list.cpp)
list(APPEND SRC primitive_triangle_strip.cpp)
list(APPEND SRC rasterizer_simple.cpp)

#add_definitions(-DHUGH_ALL_TRACE)

set(LIBS)
list(APPEND LIBS ${LIB}_test_shared)
list(APPEND LIBS ${LIB})
list(APPEND LIBS ${Boost_LIBRARIES})

cma_setup_test(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS})
