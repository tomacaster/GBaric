# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/GBaric/GBaric/build/windows-debug/_deps/libvlcpp-src"
  "D:/GBaric/GBaric/build/windows-debug/_deps/libvlcpp-build"
  "D:/GBaric/GBaric/build/windows-debug/_deps/libvlcpp-subbuild/libvlcpp-populate-prefix"
  "D:/GBaric/GBaric/build/windows-debug/_deps/libvlcpp-subbuild/libvlcpp-populate-prefix/tmp"
  "D:/GBaric/GBaric/build/windows-debug/_deps/libvlcpp-subbuild/libvlcpp-populate-prefix/src/libvlcpp-populate-stamp"
  "D:/GBaric/GBaric/build/windows-debug/_deps/libvlcpp-subbuild/libvlcpp-populate-prefix/src"
  "D:/GBaric/GBaric/build/windows-debug/_deps/libvlcpp-subbuild/libvlcpp-populate-prefix/src/libvlcpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/GBaric/GBaric/build/windows-debug/_deps/libvlcpp-subbuild/libvlcpp-populate-prefix/src/libvlcpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/GBaric/GBaric/build/windows-debug/_deps/libvlcpp-subbuild/libvlcpp-populate-prefix/src/libvlcpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
