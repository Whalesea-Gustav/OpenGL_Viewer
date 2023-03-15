CMAKE_MINIMUM_REQUIRED(VERSION 3.18)

SET(TargetName GurobiMIP)

include_directories(../../include/gurobi/)

PROJECT(${TargetName})

find_package(OpenMP)

FILE(GLOB_RECURSE CPP_SRC
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp")

ADD_EXECUTABLE(${TargetName} ${CPP_SRC})


SET_PROPERTY(TARGET ${TargetName} PROPERTY CXX_STANDARD 20)
SET_PROPERTY(TARGET ${TargetName} PROPERTY CXX_STANDARD_REQUIRED ON)

IF(MSVC)
    SET_PROPERTY(
            TARGET ${TargetName}
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/")
ENDIF()

#TARGET_LINK_LIBRARIES(${TargetName} PUBLIC AGZUtils m_common assimp::assimp)

if(OpenMP_CXX_FOUND)
    TARGET_LINK_LIBRARIES(${TargetName} PUBLIC OpenMP::OpenMP_CXX)
endif()

target_link_libraries(${TargetName} PUBLIC gurobi95.lib gurobi_c++md2019.lib)

