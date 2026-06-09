cmake_minimum_required(VERSION 3.11)
project(focworld_tcg)

# Utiliser C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- nlohmann_json FetchContent ---
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# --- Raylib FetchContent ---
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
FetchContent_MakeAvailable(raylib)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    find_package(OpenSSL REQUIRED)
endif()

# --- IXWebSocket FetchContent ---
set(USE_TLS OFF CACHE BOOL "" FORCE) # Désactivé pour le dév local
set(USE_OPEN_SSL OFF CACHE BOOL "" FORCE)
set(USE_MBED_TLS OFF CACHE BOOL "" FORCE)
set(USE_WS ON CACHE BOOL "" FORCE)
set(USE_ZLIB OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  ixwebsocket
  GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
  GIT_TAG master
)
FetchContent_MakeAvailable(ixwebsocket)

# --- Source files ---
file(GLOB_RECURSE SOURCES "src/*.cpp")

# --- Exécutable ---
# L'exécutable est WIN32 sous Windows pour éviter la console en arrière-plan (en prod)
# mais on peut la garder pour le debug pour le moment
add_executable(focworld_tcg src/main.cpp src/NetworkManager.cpp src/Board.cpp src/AutoUpdater.cpp)

# --- Includes et Lier Raylib & IXWebSocket ---
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(focworld_tcg PUBLIC raylib ixwebsocket spdlog::spdlog nlohmann_json::nlohmann_json urlmon)

# Définir l'URL du serveur en fonction du type de build
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(focworld_tcg PRIVATE SERVER_URL="wss://focworld-ws-server-production.up.railway.app")
endif()

# Sur Windows, lier les bibliothèques système supplémentaires requises par Raylib
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()
