cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(cliff)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

include(AutoFiles)

SET(MERRY_GO_ROUND_DEPENDENCY_PATH "${CMAKE_SOURCE_DIR}/deps")
SET(MERRY_GO_ROUND_DEPENDENCIES "lua" "lzma" "json" "sqlite" "ocgcore")
SET(
    MERRY_GO_ROUND_DEPENDENCY_REPOS
    "https://github.com/ygoreplay/Lua"
    "https://github.com/ygoreplay/lzma"
    "https://github.com/nlohmann/json"
    "https://github.com/SRombauts/SQLiteCpp"
    "https://github.com/Fluorohydride/ygopro-core"
)
SET(MERRY_GO_ROUND_DEPENDENCY_LIBRARIES "lua" "lzma" "json" "sqlite" "ocgcore")

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(
        MERRY_GO_ROUND_DEPENDENCY_REVISION
        "master"
        "master"
        "master"
        "master"
        "master"
    )
else()
    SET(
        MERRY_GO_ROUND_DEPENDENCY_REVISION
        "master"
        "master"
        "master"
        "master"
        "mycard-x64"
    )
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SQLITECPP_USE_STATIC_RUNTIME)

set(
    CompilerFlags
    CMAKE_CXX_FLAGS
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_C_FLAGS
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_RELEASE
)

foreach (CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach ()

LIST(LENGTH MERRY_GO_ROUND_DEPENDENCIES MERRY_GO_ROUND_DEPENDENCY_COUNT)

#
# import ExternalProject module
#
include(ExternalProject)

#
# compiler options
#
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(SUPPORT_LARGE_FILES ON)
if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif ()

#
# Download and build dependencies
#
MATH(EXPR MERRY_GO_ROUND_DEPENDENCY_COUNT "${MERRY_GO_ROUND_DEPENDENCY_COUNT} - 1")
FOREACH (i RANGE 0 ${MERRY_GO_ROUND_DEPENDENCY_COUNT})
    LIST(GET MERRY_GO_ROUND_DEPENDENCIES ${i} DEPENDENCY_NAME)
    LIST(GET MERRY_GO_ROUND_DEPENDENCY_REPOS ${i} DEPENDENCY_REPO)
    LIST(GET MERRY_GO_ROUND_DEPENDENCY_LIBRARIES ${i} DEPENDENCY_LIBRARY)
    LIST(GET MERRY_GO_ROUND_DEPENDENCY_REVISION ${i} DEPENDENCY_REVISION)

    MESSAGE(STATUS "Using dependency '${DEPENDENCY_NAME}' from '${DEPENDENCY_REPO}'")

    SET(DEPENDENCY_PATH "${MERRY_GO_ROUND_DEPENDENCY_PATH}/${DEPENDENCY_NAME}")

    ExternalProject_Add(
        ${DEPENDENCY_NAME}-src
        PREFIX "${MERRY_GO_ROUND_DEPENDENCY_PATH}/build/${DEPENDENCY_NAME}"
        GIT_REPOSITORY ${DEPENDENCY_REPO}
        GIT_TAG ${DEPENDENCY_REVISION}
        GIT_SHALLOW TRUE
        SOURCE_DIR "${MERRY_GO_ROUND_DEPENDENCY_PATH}/${DEPENDENCY_NAME}"
        CONFIGURE_COMMAND ""
        INSTALL_COMMAND ""
        BUILD_COMMAND ""
        WORKING_DIRECTORY "${MERRY_GO_ROUND_DEPENDENCY_PATH}/${DEPENDENCY_NAME}"
    )

    if (EXISTS "${MERRY_GO_ROUND_DEPENDENCY_PATH}/${DEPENDENCY_NAME}/CMakeLists.txt")
        add_subdirectory("${MERRY_GO_ROUND_DEPENDENCY_PATH}/${DEPENDENCY_NAME}")
    endif ()
ENDFOREACH ()

include_directories("C:\\Users\\Home10\\.cmake-js\\node-x64\\v14.17.0\\include\\node")
include_directories(deps/lua)
include_directories(deps/ocgcore)
include_directories(deps/lzma)
include_directories(deps/sqlite/include)
include_directories(deps/json/include)
include_directories(BEFORE ${CMAKE_JS_INC})

file(GLOB CLIFF_SOURCES
    "src/*.hpp"
    "src/*.cc"
    )

add_library(cliff SHARED ${CLIFF_SOURCES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

if (MSVC OR (${CMAKE_SYSTEM_NAME} MATCHES "Darwin"))
    target_link_libraries(cliff lua ocgcore clzma SQLiteCpp nlohmann_json::nlohmann_json)
else ()
    target_link_libraries(cliff ocgcore clzma SQLiteCpp nlohmann_json::nlohmann_json)
endif ()

# Include Node-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODE_ADDON_API_DIR
    )
string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

# define NPI_VERSION
add_definitions(-DNAPI_VERSION=3)
