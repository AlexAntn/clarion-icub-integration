# Copyright (C) 2018 Fondazione Istituto Italiano di Tecnologia (IIT)
# All Rights Reserved.
# Authors: Alexandre Antunes <alexandre.gomespereira@iit.it>

project(clarionInterface)

yarp_add_idl(IDL_GEN_FILES ${PROJECT_NAME}.thrift)

file(GLOB source src/*.cpp)
file(GLOB header include/*.h)
set(idl ${PROJECT_NAME}.thrift)

source_group("Source Files" FILES ${source})
source_group("Header Files" FILES ${header})
source_group("IDL Files" FILES ${idl})
#source_group("DOC Files" FILES ${doc_files})

add_executable(${PROJECT_NAME} ${source} ${header} ${idl} ${IDL_GEN_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

#file(GLOB scripts app/scripts/*.template)
#yarp_install(FILES ${scripts} DESTINATION ${ICUBCONTRIB_APPLICATIONS_TEMPLATES_INSTALL_DIR})

