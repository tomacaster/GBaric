cmake_minimum_required(VERSION 3.28.3)

PROJECT(GBaric  VERSION 0.0.1)

set(GBaric_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(GBaric_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(GBaric_VERSION_PATCH ${PROJECT_VERSION_PATCH})

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config/Version.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Version.h
)

configure_file(${CMAKE_SOURCE_DIR}/README.md.in ${CMAKE_BINARY_DIR}/README.md @ONLY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BINARY_DIR "${CMAKE_BINARY_DIR}/bin/")

find_package(PkgConfig REQUIRED)
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(LIBVLC REQUIRED libvlc)


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
    
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBVLC_LIBRARIES}  ${GTK4_LIBRARIES}  ${GTKMM_LIBRARIES} ${CURL_LIBRARIES}  Threads::Threads)
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

    include_directories(${LIBVLC_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} )
    target_link_libraries(${PROJECT_NAME} PRIVATE ${XCB_LDFLAGS} ${LIBS_FILES} X11 ${LIBVLC_LIBRARIES}  ${GTK_LIBRARIES} ${CURL_LIBRARIES} ${GTKMM_LIBRARIES} Threads::Threads)
    target_compile_options(${PROJECT_NAME} PRIVATE ${XCB_CFLAGS} ${GTK_CFLAGS_OTHER} -Wall -O2 )
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_TYPE="${PLATFORM_TYPE}"  ) 

add_definitions(${GTK_CFLAGS_OTHER} ${GTKMM_CFLAGS_OTHER})
find_library(VLCPP_LIB NAMES vlcpp PATHS )
target_include_directories(${PROJECT_NAME} PRIVATE include ${DESTINATION_DIR} ${CURL_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/lib")

# Adding readme
add_custom_command(
    OUTPUT ${BINARY_DIR}/README.md
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/README.md ${BINARY_DIR}/README.md
    DEPENDS ${CMAKE_BINARY_DIR}/README.md
    COMMENT "Copying README.md to binary directory"
)