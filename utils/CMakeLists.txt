file(GLOB UTILS_SOURCE *.cpp)
set(SAMPLES_DATA_DIR ${SAMPLES_DATA_DIR} "${PROJECT_SOURCE_DIR}/data")
include_directories( ${SAMPLES_DATA_DIR} ${GLSLANG_SPIRV_INCLUDE_DIR} ${GLMINC_PREFIX} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -D VK_USE_PLATFORM_ANDROID_KHR -DLOG_TAG=\\\"${LOG_TAG}\\\"")
add_library(${UTILS_NAME} STATIC ${UTILS_SOURCE})
message(STATUS "native dir=${ANDROID_NDK}/sources/android/native_app_glue")
include_directories(
        ${ANDROID_NDK}/sources/third_party/shaderc/include
        ${SHADERC_SRC}/third_party/spirv-tools/include
        ${ANDROID_NDK}/sources/android/native_app_glue
)
target_include_directories(${UTILS_NAME} PRIVATE
                          ${CMAKE_CURRENT_SOURCE_DIR}
        ${ANDROID_NDK}/sources/android/native_app_glue)
target_link_libraries(${UTILS_NAME}
                          android
                          log)


