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

set(TESTS_CLIENT_DIR ${PROJECT_SOURCE_DIR}/tests/Client)
set(TESTS_SERVER_DIR ${PROJECT_SOURCE_DIR}/tests/Server)
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
# -------------------------------- TESTS SERVER -------------------------------- #
set(TESTS_SERVER ${TESTS_SERVER_DIR}/testDirReader.cpp
                 ${TESTS_SERVER_DIR}/testECSEngine.cpp 
                 ${TESTS_SERVER_DIR}/testPathHandler.cpp
)

# -------------------------------- TESTS CLIENT -------------------------------- #
set(TESTS_CLIENT)

add_executable(unit_tests_client ${TESTS_CLIENT} ${SRCS_CLIENT} ${SRCS_SHARED})
target_compile_features(unit_tests_client PRIVATE cxx_std_17)
target_compile_options(unit_tests_client
                        PRIVATE
                        $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_include_directories(unit_tests_client PRIVATE ${INCLUDES_CLIENT_DIR})
target_include_directories(unit_tests_client PRIVATE ${INCLUDES_SHARED_DIR})
target_include_directories(unit_tests_client PRIVATE SYSTEM ${INCLUDES_SHARED_MONSTERS_DIR})
target_link_libraries(unit_tests_client criterion)
target_link_libraries(unit_tests_client ${CONAN_LIBS})
target_link_libraries(unit_tests_client ${CMAKE_THREAD_LIBS_INIT})
add_test(first unit_tests_client)

add_executable(unit_tests_server ${TESTS_SERVER} ${SRCS_SERVER} ${SRCS_SHARED})
target_compile_features(unit_tests_server PRIVATE cxx_std_17)
target_compile_options(unit_tests_server
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDES_SERVER_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDES_SHARED_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDE_COMPONENTS_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDE_SYSTEMS_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDE_ENGINE_DIR})
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDES_SHARED_MONSTERS_DIR})
target_link_libraries(unit_tests_server criterion)
target_link_libraries(unit_tests_server ${CONAN_LIBS})
target_link_libraries(unit_tests_server ${CMAKE_THREAD_LIBS_INIT})
add_test(second unit_tests_server)

                      