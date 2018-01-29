# Version de CMake
cmake_minimum_required(VERSION 2.8)
# Nom du projet
project("MCS Quizz")
# On cherche les bonnes librairies
set(CURSES_NEED_NCURSES ON)
find_package(Curses REQUIRED)
set(Cdk_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS ${CMAKE_MODULE_PATH})

find_package(Cdk REQUIRED)
find_package(Threads REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
include_directories(${CDK_INCLUDE_DIRS})

# On active les erreurs de compilations
set(warnings "-Wall -Wextra -Werror -pedantic -g2 -O0 -ggdb")
# On affiche ce que fait le makefile
set(CMAKE_VERBOSE_MAKEFILE OFF)
# On met nos flags
set(CMAKE_C_FLAGS "${warnings}")

# On active les tests
enable_testing ()

# On demande d'inclure le dossier
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(src/Protocole)
add_subdirectory(src/Reseau)
add_subdirectory("src/Serveur Central")
add_subdirectory(src/Client)
add_subdirectory(src/Utilitaires)
add_subdirectory(tests)

add_executable(MCSQuizz_Serveur "src/Serveur Central/serveur_central.c")
target_link_libraries(MCSQuizz_Serveur Reseau Protocole Utilitaires ServeurCentral ${CURSES_LIBRARIES} ${CDK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(MCSQuizz_Client "src/Client/client.c")
target_link_libraries(MCSQuizz_Client Reseau Protocole Utilitaires ${CURSES_LIBRARIES} ${CDK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
