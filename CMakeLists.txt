cmake_minimum_required(VERSION 3.14)
project(sfs2x_sniffer VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MINGW)
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -static")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static -s")
endif()

# Vendored zlib
file(GLOB ZLIB_SOURCES deps/zlib/*.c)
add_library(zlib_static STATIC ${ZLIB_SOURCES})
target_include_directories(zlib_static PUBLIC deps/zlib)

# MinHook
add_library(minhook STATIC
    deps/minhook/src/buffer.c
    deps/minhook/src/hook.c
    deps/minhook/src/trampoline.c
    deps/minhook/src/hde/hde32.c
    deps/minhook/src/hde/hde64.c
)
target_include_directories(minhook PUBLIC deps/minhook/include)

# Sniffer DLL
add_library(sfs2x_sniffer SHARED
    src/main.cpp
    src/exports.def
)
target_include_directories(sfs2x_sniffer PRIVATE
    deps/minhook/include
    deps/cleverfox
    deps/zlib
    src
)
target_link_libraries(sfs2x_sniffer PRIVATE minhook zlib_static)

set_target_properties(sfs2x_sniffer PROPERTIES
    OUTPUT_NAME "rockyhaxx"
    PREFIX ""
)
