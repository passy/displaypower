CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(gnome-displaypower C)

INCLUDE(FindPkgConfig)

# Where to find local cmake scripts
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

PKG_CHECK_MODULES(GLIB REQUIRED glib-2.0)
PKG_CHECK_MODULES(DBUS_GLIB REQUIRED dbus-glib-1)
INCLUDE_DIRECTORIES(${GLIB_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${DBUS_GLIB_INCLUDE_DIRS})

ADD_DEFINITIONS(-ggdb -fsigned-char -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror)
ADD_SUBDIRECTORY(src bin)
