cmake_minimum_required(VERSION 3.16)
project(libs)

set(LIBAPNG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libpng)
message(${LIBAPNG_DIR})
set(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/zlib)
set(ZLIB_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/zlib/libz${CMAKE_SHARED_LIBRARY_SUFFIX})

# Download Mozilla's libpng patch (apng + filter)
set(MOZILLA_LIBPNG_PATCH_COMMIT 51f5424c3d2f39c642419b40598e06ef91ac5062)
set(MOZILLA_LIBPNG_PATCH_COMMIT_REMOTE a40189cf881e9f0db80511c382292a5604c3c3d1)
set(MOZILLA_LIBPNG_PATCH_URL https://raw.githubusercontent.com/mozilla/gecko-dev/${MOZILLA_LIBPNG_PATCH_COMMIT}/media/libpng)
file(DOWNLOAD ${MOZILLA_LIBPNG_PATCH_URL}/1737038.patch ${CMAKE_CURRENT_BINARY_DIR}/patch/1737038.patch)
file(DOWNLOAD ${MOZILLA_LIBPNG_PATCH_URL}/apng.patch ${CMAKE_CURRENT_BINARY_DIR}/patch/apng.patch)
# Apply lib png patch
execute_process(COMMAND git reset --hard
        WORKING_DIRECTORY ${LIBAPNG_DIR})
execute_process(COMMAND git checkout ${MOZILLA_LIBPNG_PATCH_COMMIT_REMOTE}
        WORKING_DIRECTORY ${LIBAPNG_DIR})
execute_process(COMMAND git clean -fdx
        WORKING_DIRECTORY ${LIBAPNG_DIR})
execute_process(COMMAND git apply ${CMAKE_CURRENT_BINARY_DIR}/patch/apng.patch
        WORKING_DIRECTORY ${LIBAPNG_DIR})
execute_process(COMMAND git apply ${CMAKE_CURRENT_BINARY_DIR}/patch/1737038.patch
        WORKING_DIRECTORY ${LIBAPNG_DIR})
execute_process(COMMAND git apply ${CMAKE_CURRENT_SOURCE_DIR}/../patch/symbols.patch
        WORKING_DIRECTORY ${LIBAPNG_DIR})
execute_process(COMMAND git apply ${CMAKE_CURRENT_SOURCE_DIR}/../patch/acTL.patch
        WORKING_DIRECTORY ${LIBAPNG_DIR})

# Build zlib
add_subdirectory(${ZLIB_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR})
# Build libpng
add_subdirectory(${LIBAPNG_DIR} ${LIBAPNG_DIR})