cmake_minimum_required(VERSION 3.22.1)

project(GBaric VERSION 0.0.1)

# Ustawienia wersji
set(GBaric_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(GBaric_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(GBaric_VERSION_PATCH ${PROJECT_VERSION_PATCH})

# Konfiguracja plików
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config/Version.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Version.h
)

configure_file(${CMAKE_SOURCE_DIR}/README.md.in ${CMAKE_BINARY_DIR}/README.md @ONLY)

# Ustawienia C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BINARY_DIR "${CMAKE_BINARY_DIR}/bin/")

# Znajdowanie pakietów
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
pkg_search_module(FMT REQUIRED fmt)
pkg_check_modules(SQLiteCpp REQUIRED sqlite3)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(LIBVLC REQUIRED libvlc)
pkg_search_module(gstreamer REQUIRED IMPORTED_TARGET gstreamer-1.0>=1.4)
pkg_search_module(gstreamer-sdp REQUIRED IMPORTED_TARGET gstreamer-sdp-1.0>=1.4)
pkg_search_module(gstreamer-app REQUIRED IMPORTED_TARGET gstreamer-app-1.0>=1.4)
pkg_search_module(gstreamer-video REQUIRED IMPORTED_TARGET gstreamer-video-1.0>=1.4)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

# FetchContent dla nlohmann_json
include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(nlohmann_json)

# Dodanie subdirectories dla src i include
add_subdirectory(src)
add_subdirectory(include)

# Dodanie subdirectory dla mptf_core
add_subdirectory(components/mptf_core)

# Dodanie ścieżek do nagłówków libvlc
include_directories(${LIBVLC_INCLUDE_DIRS})

# Dodanie bibliotek libvlc
link_directories(${LIBVLC_LIBRARY_DIRS})

# Tworzenie executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Kopiowanie zasobów
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/bin)

# Linkowanie bibliotek
if(WIN32)
    set(PLATFORM_TYPE "WIN32")
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)

    target_link_libraries(${PROJECT_NAME} PRIVATE 
        mptf_core::mptf_core
        ${LIBVLC_LIBRARIES} 
        ${GTK4_LIBRARIES}  
        ${GTKMM_LIBRARIES}  
        ${SQLiteCpp_LIBRARIES} 
        spdlog::spdlog 
        $<$<BOOL:${MINGW}>:ws2_32> 
        Threads::Threads
    )
    target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS_OTHER} -Wall -O2 -g )
    
elseif(UNIX)
    set(PLATFORM_TYPE "LINUX")

    pkg_check_modules(XCB REQUIRED xcb)

    include_directories(${LIBVLC_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} ${FMT_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        mptf_core::mptf_core
        ${XCB_LDFLAGS} 
        ${LIBS_FILES} 
        X11 
        ${LIBVLC_LIBRARIES}  
        ${GTK_LIBRARIES} 
        ${GTKMM_LIBRARIES} 
        ${FMT_LIBRARIES} 
        ${SQLiteCpp_LIBRARIES} 
        SQLiteCpp 
        sqlite3 
        spdlog::spdlog 
        $<$<BOOL:${MINGW}>:ws2_32> 
        Threads::Threads     
        PkgConfig::gstreamer
        PkgConfig::gstreamer-sdp
        PkgConfig::gstreamer-app
        PkgConfig::gstreamer-video
    )
    target_compile_options(${PROJECT_NAME} PRIVATE ${XCB_CFLAGS} ${GTK_CFLAGS_OTHER} -Wall -O0 )
    
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Definicje kompilacji
target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_TYPE="${PLATFORM_TYPE}")

# Dodanie ścieżek do bibliotek SQLiteCpp
link_directories(${SQLiteCpp_LIBRARY_DIRS})

# Definicje dla GTK
add_definitions(${GTK_CFLAGS_OTHER} ${GTKMM_CFLAGS_OTHER})

# Znalezienie biblioteki vlcpp (opcjonalnie)
find_library(VLCPP_LIB NAMES vlcpp PATHS )

# Dodanie katalogów nagłówków
target_include_directories(${PROJECT_NAME} PRIVATE 
    include 
    ${DESTINATION_DIR}  
    ${GTK_INCLUDE_DIRS} 
    ${GTKMM_INCLUDE_DIRS} 
    ${SQLiteCpp_INCLUDE_DIRS}
)

# Ustawienia RPATH
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/lib")

# Dodanie README.md do katalogu bin
add_custom_command(
    OUTPUT ${BINARY_DIR}/README.md
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/README.md ${BINARY_DIR}/README.md
    DEPENDS ${CMAKE_BINARY_DIR}/README.md
    COMMENT "Copying README.md to binary directory"
)
