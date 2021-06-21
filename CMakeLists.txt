cmake_minimum_required(VERSION 3.12)
project(r-type)

set(INCLUDE_ENGINE_DIR ${PROJECT_SOURCE_DIR}/engine/include/)
set(SRCS_ENGINE_DIR ${PROJECT_SOURCE_DIR}/engine/src/)

set(INCLUDE_SYSTEMS_DIR ${PROJECT_SOURCE_DIR}/include/Server/Systems)
set(SRCS_SYSTEMS_DIR ${PROJECT_SOURCE_DIR}/src/Server/Systems)

set(INCLUDE_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/include/Server/Components)
set(SRCS_COMPONENTS_DIR ${PROJECT_SOURCE_DIR}/src/Server/Components)

set(INCLUDES_SHARED_DIR ${PROJECT_SOURCE_DIR}/include/Shared)
set(SRCS_SHARED_DIR ${PROJECT_SOURCE_DIR}/src/Shared)

set(INCLUDES_SHARED_MONSTERS_DIR ${INCLUDES_SHARED_DIR}/Monsters)
set(SRCS_SHARED_MONSTERS_DIR ${SRCS_SHARED_DIR}/Monsters)

set(INCLUDES_CLIENT_DIR ${PROJECT_SOURCE_DIR}/include/Client)
set(SRCS_CLIENT_DIR ${PROJECT_SOURCE_DIR}/src/Client)

set(INCLUDES_SERVER_DIR ${PROJECT_SOURCE_DIR}/include/Server)
set(SRCS_SERVER_DIR ${PROJECT_SOURCE_DIR}/src/Server)

# WINDOWS USERNAME AND VARIABLE TO BE SET
set(USERS "$4L0100-HTIUPI4CB281")
set(SFML_WIN_INCLUDE_DIR "C:/Users/$4L0100-HTIUPI4CB281/Downloads/SFML-2.5.1-windows-vc15-32-bit/SFML-2.5.1/include/SFML")
set(SFML_WIN_DIR "C:/Users/$4L0100-HTIUPI4CB281/Downloads/SFML-2.5.1-windows-vc15-32-bit/SFML-2.5.1")
set(CONAN_SFML_DIR "C:/Users/${USER}/.conan/data/sfml/2.5.1/bincrafters/stable/package/7fb22053704eee59cfda675d9b91bdb52a86d20c")

if (WIN32)

    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

    find_library(SFML_WIN_LIB
        NAMES sfml-graphics sfml-window sfml-system sfml-audio
        PATHS
            "${SFML_WIN_DIR}/lib"
            "${CONAN_SFML_DIR}/lib"
    )

    if (NOT SFML_WIN_LIB)
        message(FATAL_ERROR "SFML not found ..........")
    endif()

    find_library(ws2_32_LIBRARY_PATH ws2_32)
endif (WIN32)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Threads)

# -------------------------------- CLIENT SOURCES -------------------------------- #
set (SRCS_CLIENT ${SRCS_CLIENT_DIR}/Alien.cpp
                 ${SRCS_CLIENT_DIR}/AlienShoot.cpp
                 ${SRCS_CLIENT_DIR}/Audio.cpp
                 ${SRCS_CLIENT_DIR}/Background.cpp
                 ${SRCS_CLIENT_DIR}/Bomb.cpp
                 ${SRCS_CLIENT_DIR}/Client.cpp
                 ${SRCS_CLIENT_DIR}/Entity.cpp
                 ${SRCS_CLIENT_DIR}/GifDrawer.cpp
                 ${SRCS_CLIENT_DIR}/ItemSpeed.cpp
                 ${SRCS_CLIENT_DIR}/keyTraducer.cpp
                 ${SRCS_CLIENT_DIR}/main.cpp
                 ${SRCS_CLIENT_DIR}/MenuDrawer.cpp
                 ${SRCS_CLIENT_DIR}/Obstacle.cpp
                 ${SRCS_CLIENT_DIR}/parallaxShader.cpp
                 ${SRCS_CLIENT_DIR}/Parser.cpp
                 ${SRCS_CLIENT_DIR}/Pirate.cpp
                 ${SRCS_CLIENT_DIR}/PirateShoot.cpp
                 ${SRCS_CLIENT_DIR}/Player.cpp
                 ${SRCS_CLIENT_DIR}/Players.cpp
                 ${SRCS_CLIENT_DIR}/PlayerShoot.cpp
                 ${SRCS_CLIENT_DIR}/SFMLModule.cpp
                 ${SRCS_CLIENT_DIR}/Spaceship.cpp
                 ${SRCS_CLIENT_DIR}/SpaceshipShoot.cpp
                 ${SRCS_CLIENT_DIR}/TextDrawer.cpp
                 ${SRCS_CLIENT_DIR}/Ufo.cpp
                 ${SRCS_CLIENT_DIR}/UfoShoot.cpp
                 ${SRCS_CLIENT_DIR}/Wall.cpp
)
# -------------------------------- SERVER SOURCES -------------------------------- #
set(SRCS_SERVER ${SRCS_COMPONENTS_DIR}/Bomb.cpp
                ${SRCS_COMPONENTS_DIR}/Dimensions.cpp
                ${SRCS_COMPONENTS_DIR}/entityDetails.cpp
                ${SRCS_COMPONENTS_DIR}/Life.cpp
                ${SRCS_COMPONENTS_DIR}/Player.cpp
                ${SRCS_COMPONENTS_DIR}/Position.cpp
                ${SRCS_COMPONENTS_DIR}/Velocity.cpp
                ${SRCS_SYSTEMS_DIR}/bombSystem.cpp
                ${SRCS_SYSTEMS_DIR}/collisionSystem.cpp
                ${SRCS_SYSTEMS_DIR}/eventSystem.cpp
                ${SRCS_SYSTEMS_DIR}/monsterSystem.cpp
                ${SRCS_SYSTEMS_DIR}/movementSystem.cpp
                ${SRCS_SYSTEMS_DIR}/routineSystem.cpp
                ${SRCS_SYSTEMS_DIR}/winSystem.cpp
                ${SRCS_SERVER_DIR}/Buffer.cpp
                ${SRCS_SERVER_DIR}/Client.cpp
                ${SRCS_SERVER_DIR}/dirReader.cpp
                ${SRCS_SERVER_DIR}/gameLoop.cpp
                ${SRCS_SERVER_DIR}/Lobby.cpp
                ${SRCS_SERVER_DIR}/main.cpp
                ${SRCS_SERVER_DIR}/udpServer.cpp
                ${SRCS_ENGINE_DIR}/ASystem.cpp
                ${SRCS_ENGINE_DIR}/ECSEngine.cpp
                ${SRCS_ENGINE_DIR}/EntityManager.cpp
                ${SRCS_ENGINE_DIR}/Filter.cpp
                ${SRCS_ENGINE_DIR}/StorageManager.cpp
                ${SRCS_ENGINE_DIR}/SystemManager.cpp
)
# -------------------------------- SHARED SOURCES -------------------------------- #
set(SRCS_SHARED ${SRCS_SHARED_MONSTERS_DIR}/Error.cpp
                ${SRCS_SHARED_DIR}/BinaryProtocol.cpp
                ${SRCS_SHARED_DIR}/pathHandler.cpp
                ${SRCS_SHARED_DIR}/SignalHandler.cpp
)
add_executable(r-type_server ${SRCS_SERVER} ${SRCS_SHARED})
target_compile_features(r-type_server PRIVATE cxx_std_17)
target_compile_options(r-type_server
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /std:c++17 /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3 -Wno-unused-local-typedefs>)
target_include_directories(r-type_server PRIVATE SYSTEM ${INCLUDES_SERVER_DIR})
target_include_directories(r-type_server PRIVATE SYSTEM ${INCLUDES_SHARED_DIR})
target_include_directories(r-type_server PRIVATE SYSTEM ${INCLUDE_COMPONENTS_DIR})
target_include_directories(r-type_server PRIVATE SYSTEM ${INCLUDE_SYSTEMS_DIR})
target_include_directories(r-type_server PRIVATE SYSTEM ${INCLUDE_ENGINE_DIR})
target_include_directories(r-type_server PRIVATE SYSTEM ${INCLUDES_SHARED_MONSTERS_DIR})
target_link_libraries(r-type_server ${CONAN_LIBS})
target_link_libraries(r-type_server ${CMAKE_DL_LIBS})
target_link_libraries(r-type_server ${CMAKE_THREAD_LIBS_INIT})
add_executable(r-type_client ${SRCS_CLIENT} ${SRCS_SHARED})
target_compile_features(r-type_client PRIVATE cxx_std_17)
target_compile_options(r-type_client
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- -D_WIN32_WINNT=0x0A00 -DWIN32_LEAN_AND_MEAN /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3 -Wno-unused-local-typedefs -lpthread -lboost_system -lboost_thread>)
target_include_directories(r-type_client PRIVATE SYSTEM ${INCLUDES_CLIENT_DIR})
target_include_directories(r-type_client PRIVATE SYSTEM ${INCLUDES_SHARED_DIR})
target_include_directories(r-type_client PRIVATE SYSTEM ${INCLUDES_SHARED_MONSTERS_DIR})

if (WIN32)
    target_include_directories(r-type_client PRIVATE SYSTEM ${SFML_WIN_INCLUDE_DIR})
endif (WIN32)

target_link_libraries(r-type_client ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(r-type_client ${CONAN_LIBS})

if (WIN32)
    target_link_libraries(r-type_client ${SFML_WIN_LIB})
    target_link_libraries(r-type_client ${ws2_32_LIBRARY_PATH})
endif (WIN32)

if (UNIX)
    target_link_libraries(r-type_client ${SFML_LIBRARIES})
    target_link_libraries(r-type_client sfml-window sfml-system sfml-audio sfml-graphics)
endif (UNIX)

if (UNIX)
    include(CTest)
    enable_testing(MAKE_DIRECTORY tests)
    add_subdirectory(tests)
endif (UNIX)

add_subdirectory(ressources/monsters/)