cmake_minimum_required(VERSION 3.5...3.25)
project(SimCD)
set(CMAKE_CXX_STANDARD 17)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB MACROS ${PROJECT_SOURCE_DIR}/macros/*.mac)
file(COPY ${MACROS} DESTINATION ${PROJECT_BINARY_DIR})

#aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCES)
#aux_source_directory(${PROJECT_SOURCE_DIR}/include HEADERS)

add_executable(smcd smcd.cc ${sources} ${headers})
target_link_libraries(smcd ${Geant4_LIBRARIES})

add_custom_target(SimCD DEPENDS smcd)
