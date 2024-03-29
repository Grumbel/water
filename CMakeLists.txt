# Simple Water Wave Effect in OpenGL
# Copyright (C) 2020 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.15)
project(water-fx VERSION 0.0.0)

include(GNUInstallDirs)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(water-fx water.cpp)
target_link_libraries(water-fx PUBLIC
  OpenGL::GL
  OpenGL::GLU
  GLUT::GLUT)

install(TARGETS water-fx
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# EOF #
