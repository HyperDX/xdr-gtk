cmake_minimum_required(VERSION 3.6)
project(xdr-gtk)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK REQUIRED gtk+-3.0)
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)
execute_process(COMMAND ${GLIB_COMPILE_RESOURCES} --generate-source --sourcedir=${CMAKE_SOURCE_DIR} --target=${CMAKE_BINARY_DIR}/resources.c ${CMAKE_SOURCE_DIR}/icons/icons.xml)
execute_process(COMMAND ${GLIB_COMPILE_RESOURCES} --generate-header --sourcedir=${CMAKE_SOURCE_DIR} --target=${CMAKE_BINARY_DIR}/resources.h ${CMAKE_SOURCE_DIR}/icons/icons.xml)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wno-overlength-strings")

add_subdirectory(src)

if(NOT MINGW)
    install(TARGETS xdr-gtk DESTINATION bin)
    install(FILES xdr-gtk.desktop DESTINATION share/applications)
    install(DIRECTORY icons/ DESTINATION share/icons/hicolor
            FILES_MATCHING
            PATTERN "xdr-gtk\.png"
            PATTERN "xdr-gtk\.svg")
    install(CODE "execute_process(COMMAND gtk-update-icon-cache /usr/share/icons/hicolor)")
endif()
