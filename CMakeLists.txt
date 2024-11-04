cmake_minimum_required(VERSION 3.16...3.27)
project(B3a)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})

set(EXAMPLEB3_SCRIPTS
  debug.mac
  exampleB3.in
  exampleB3.out
  init_vis.mac
  run1.mac
  run2.mac
  vis.mac
  beam.mac
  )

foreach(_script ${EXAMPLEB3_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(B3a DEPENDS exampleB3a)

install(TARGETS sim DESTINATION bin )
