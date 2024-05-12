cmake_minimum_required(VERSION 3.22.1)

PROJECT(GBaric  VERSION 0.0.1)

set(GBaric_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(GBaric_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(GBaric_VERSION_PATCH ${PROJECT_VERSION_PATCH})

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config/Version.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Version.h
)

configure_file(${CMAKE_SOURCE_DIR}/README.md.in ${CMAKE_BINARY_DIR}/README.md @ONLY)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BINARY_DIR "${CMAKE_BINARY_DIR}/bin/")

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

include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(nlohmann_json)

add_subdirectory(src)
add_subdirectory(include)
 
add_executable(${PROJECT_NAME} ${SRC_FILES})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
    set(PLATFORM_TYPE "WIN32")
    # set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs/windows/")
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    # list(APPEND HEADERS
    #     include/Win32WindowManager.hpp
    # )
    # list(APPEND SOURCES
    #     src/Win32WindowManager.cpp
    # )
    
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBVLC_LIBRARIES}  ${GTK4_LIBRARIES}  ${GTKMM_LIBRARIES}  ${SQLiteCpp_LIBRARIES} spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> Threads::Threads)
    target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS_OTHER} -Wall -O2 -g ) # -fsanitize=address -fno-omit-frame-pointer -g

elseif(UNIX)
    set(PLATFORM_TYPE "LINUX")
    # list(APPEND HEADERS
    #     include/X11WindowManager.hpp
    # )
    # list(APPEND SOURCES
    #     src/X11WindowManager.cpp
    # )

    pkg_check_modules(XCB REQUIRED xcb)

    include_directories(${LIBVLC_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} ${FMT_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${XCB_LDFLAGS} ${LIBS_FILES} X11 ${LIBVLC_LIBRARIES}  ${GTK_LIBRARIES} ${GTKMM_LIBRARIES} ${FMT_LIBRARIES} ${SQLiteCpp_LIBRARIES} SQLiteCpp sqlite3 spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> Threads::Threads     PkgConfig::gstreamer
    PkgConfig::gstreamer-sdp
    PkgConfig::gstreamer-app
    PkgConfig::gstreamer-video)
    target_compile_options(${PROJECT_NAME} PRIVATE ${XCB_CFLAGS} ${GTK_CFLAGS_OTHER} -Wall -O2 )
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_TYPE="${PLATFORM_TYPE}"  ) 

link_directories(${SQLiteCpp_LIBRARY_DIRS})

add_definitions(${GTK_CFLAGS_OTHER} ${GTKMM_CFLAGS_OTHER})
find_library(VLCPP_LIB NAMES vlcpp PATHS )
target_include_directories(${PROJECT_NAME} PRIVATE include ${DESTINATION_DIR}  ${GTK_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS} ${SQLiteCpp_INCLUDE_DIRS})
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/lib")

# Adding readme
add_custom_command(
    OUTPUT ${BINARY_DIR}/README.md
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/README.md ${BINARY_DIR}/README.md
    DEPENDS ${CMAKE_BINARY_DIR}/README.md
    COMMENT "Copying README.md to binary directory"
)