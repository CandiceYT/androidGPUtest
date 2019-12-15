cmake_minimum_required(VERSION 3.4.1)
file(GLOB SAMPLE_FILE ./android_main/*.cpp)
get_filename_component(SHADERC_SRC    ${ANDROID_NDK}/sources/third_party/shaderc    ABSOLUTE)
get_filename_component(GLMINC_PREFIX    "${CMAKE_SOURCE_DIR}/utils"    ABSOLUTE)

# Build Util Lib
set(UTILS_NAME  utils)
set(VKWRAPPER  vkwarpper)
set(MODULE_NAME  module_${SAMPLE_NAME})
set(GLSLANG_SPIRV_INCLUDE_DIR ${SHADERC_SRC}/third_party/glslang)
if(${LOG_TAG})
    set(LOG_TAG GPU_Bench)
else()
    set(LOG_TAG GPUBENCH_${LOG_TAG})
endif()
message(STATUS "LOG_TAG=${LOG_TAG}")
message(STATUS "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message(STATUS "SAMPLE_FILE=${SAMPLE_FILE}")
message(STATUS "SAMPLE_NAME=${SAMPLE_NAME}")
message(STATUS "CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")

add_subdirectory(${CMAKE_SOURCE_DIR}/${SAMPLE_NAME}/cpp ${CMAKE_BINARY_DIR}/${SAMPLE_NAME})
add_subdirectory(${CMAKE_SOURCE_DIR}/utils ${CMAKE_BINARY_DIR}/utils)
add_subdirectory(${CMAKE_SOURCE_DIR}/vulkan_wrapper ${CMAKE_BINARY_DIR}/vulkan_wrapper)


add_library(shaderc_lib STATIC IMPORTED)
set_target_properties(shaderc_lib PROPERTIES IMPORTED_LOCATION
                      ${SHADERC_SRC}/libs/${ANDROID_STL}/${ANDROID_ABI}/libshaderc.a)

## Build application's shared lib

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -D VK_USE_PLATFORM_ANDROID_KHR -DLOG_TAG=\\\"${LOG_TAG}\\\"")
#
## Force export ANativeActivity_onCreate(),
## Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS   "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
#
add_library(${SAMPLE_NAME} SHARED
            ${SAMPLE_FILE})

# build native_app_glue as a static lib
add_library(native_app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

target_include_directories(${SAMPLE_NAME} PRIVATE
                           ${CMAKE_SOURCE_DIR}/data
                           ${CMAKE_SOURCE_DIR}/android_main
                           ${CMAKE_SOURCE_DIR}/utils
                           ${ANDROID_NDK}/sources/third_party/shaderc/include
                           ${SHADERC_SRC}/third_party/spirv-tools/include
                           ${ANDROID_NDK}/sources/android/native_app_glue
                           ${SHADERC_SRC}/third_party/spirv-tools/include/spirv-tools
                           ${CMAKE_SOURCE_DIR}/vulkan_wrapper)
#
target_link_libraries(${SAMPLE_NAME}
                      log
                      ${MODULE_NAME}
                      ${UTILS_NAME}
                      ${VKWRAPPER}
                      shaderc_lib
                      native_app_glue)