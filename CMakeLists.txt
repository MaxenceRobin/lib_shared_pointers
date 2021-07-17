cmake_minimum_required(VERSION 3.10)

# Variables --------------------------------------------------------------------

set(PROJECT_NAME libsharedpointers)
set(TARGET_NAME sharedpointers)

set(SOURCES
        src/libsharedpointers.c
)

set(PUBLIC_HEADERS
        include/public/libsharedpointers.h
)

set(INSTALL_DIR
        bin
)

# Configuration ----------------------------------------------------------------

project(${PROJECT_NAME})

add_library(${TARGET_NAME} SHARED ${SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC include/public)

set_target_properties(${TARGET_NAME}
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${INSTALL_DIR}
        C_STANDARD 11
)
