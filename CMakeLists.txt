cmake_minimum_required(VERSION 3.10)
project(libsharedpointers)

# Variables --------------------------------------------------------------------

set(TARGET_NAME shared_pointers)

set(SOURCES
        private/lib_shared_pointers.c
)

set(PUBLIC_HEADERS
        public
)

set(INSTALL_DIR
        bin
)

# Configuration ----------------------------------------------------------------

add_library(${TARGET_NAME} SHARED ${SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC ${PUBLIC_HEADERS})

set_target_properties(${TARGET_NAME}
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${INSTALL_DIR}
        C_STANDARD 11
)
