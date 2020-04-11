cmake_minimum_required(VERSION 2.8)
project(MinkowskiNet)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall  -O3 -march=native")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall  -O3 -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall   -O3 -march=native -std=c++11")


# Call python for MaskRCNN
find_package(PythonLibs 3.6 EXACT REQUIRED)
message("PythonLibs Status: ")
message("=======")
message("Using python:  ${PYTHONLIBS_VERSION_STRING} ")
message("Using PYTHON_LIBRARIES:  ${PYTHON_LIBRARIES} ")
message("Using PYTHON_INCLUDE_DIRS:  ${PYTHON_INCLUDE_DIRS} ")
message("=======")
# Copy file necessary for running

set(MINKOWSKINET_DIR ${CMAKE_SOURCE_DIR}/MinkowskiNet CACHE STRING "Location of MinkowskiNet")
set(MINKOWSKINET_PYTHON_VE_PATH ${CMAKE_SOURCE_DIR}/python_env/ CACHE STRING "Python virtual environment to use")
set(MINKOWSKINET_WEIGHT_FILE "${MASKRCNN_DIR}/data/mask_rcnn_coco.h5" CACHE STRING "MinkowskiNet model weights")
#set(MASKRCNN_GPU "0" CACHE STRING "Which GPU should MaskRCNN use")
configure_file("${MINKOWSKINET_DIR}/MinkowskiNet.py.in" "${CMAKE_SOURCE_DIR}/bin/MinkowskiNet.py")
configure_file("${MINKOWSKINET_DIR}/config.py" "${CMAKE_SOURCE_DIR}/bin/config.py")

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
find_package(Glog REQUIRED)


include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include
${GLOG_INCLUDE_DIR}
${PYTHON_INCLUDE_DIRS}
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

#list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")
add_library(${PROJECT_NAME} SHARED
src/SemanticsUtil.cpp
)

target_link_libraries(${PROJECT_NAME}
${GLOG_LIBRARIES}
${PYTHON_LIBRARIES}
)


# Build examples
# ${GLUT_LIBRARY}

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(test
        src/main.cpp
)
target_link_libraries(test 
${GLOG_LIBRARIES}
${PYTHON_LIBRARIES}
# ${GLUT_LIBRARY}
#  ${OPENGL_LIBRARY} ${CUDA_LIBRARIES}
)
