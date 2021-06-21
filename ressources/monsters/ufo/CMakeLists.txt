cmake_minimum_required(VERSION 3.12)
project(ufo_monster)

set(SRCS_DIR ${PROJECT_SOURCE_DIR}/src)
set(SRCS_SHARED_DIR ${PROJECT_SOURCE_DIR}/../src)

set(INCLUDE_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/../../../include/Server/Components)
set(SOURCE_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/../../../src/Server/Components)

set(INCLUDE_ENGINE_DIR ${PROJECT_SOURCE_DIR}/../../../engine/include)
set(SOURCE_ENGINE_DIR ${PROJECT_SOURCE_DIR}/../../../engine/src)

set(INCLUDE_SHARED_MONSTERS_DIR ${PROJECT_SOURCE_DIR}/../../../include/Shared/Monsters)
set(SOURCE_SHARED_MONSTERS_DIR ${PROJECT_SOURCE_DIR}/../../../src/Shared/Monsters)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_SHARED_MONSTERS_DIR})
include_directories(${INCLUDE_ENGINE_DIR})
include_directories(${INCLUDE_COMPONENTS_DIR})

# -------------------------------- SERVER SOURCES -------------------------------- #
set(SRCS_SERVER ${SRCS_COMPONENTS_DIR}/Bomb.cpp
                ${SRCS_COMPONENTS_DIR}/Dimensions.cpp
                ${SRCS_COMPONENTS_DIR}/entityDetails.cpp
                ${SRCS_COMPONENTS_DIR}/Life.cpp
                ${SRCS_COMPONENTS_DIR}/Player.cpp
                ${SRCS_COMPONENTS_DIR}/Position.cpp
                ${SRCS_COMPONENTS_DIR}/Velocity.cpp
                ${SRCS_ENGINE_DIR}/ASystem.cpp
                ${SRCS_ENGINE_DIR}/ECSEngine.cpp
                ${SRCS_ENGINE_DIR}/EntityManager.cpp
                ${SRCS_ENGINE_DIR}/Filter.cpp
                ${SRCS_ENGINE_DIR}/StorageManager.cpp
                ${SRCS_ENGINE_DIR}/SystemManager.cpp
)

# -------------------------------- SHARED SOURCES -------------------------------- #
set(SRCS_SHARED ${SRCS_SHARED_MONSTERS_DIR}/Error.cpp
)

# -------------------------------- PIRATE SOURCES -------------------------------- #
set(SRCS ${SRCS_DIR}/Ufo.cpp
         ${SRCS_SHARED_DIR}/AMonster.cpp
)
# Create shared library
add_library(ufo_monster SHARED ${SRCS} ${SRCS_SHARED} ${SRCS_SERVER})