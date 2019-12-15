file(GLOB VKWRAPPER_FILE *.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -D VK_USE_PLATFORM_ANDROID_KHR -DLOG_TAG=\\\"${LOG_TAG}\\\"")
include_directories(${CMAKE_SOURCE_DIR}/utils
                    ${CMAKE_SOURCE_DIR}/android_main
                    ${ANDROID_NDK}/sources/android/native_app_glue/
                    ${SHADERC_SRC}/third_party/spirv-tools/include/spirv-tools
                    ${ANDROID_NDK}/sources/third_party/shaderc/include
                    )

add_library(${VKWRAPPER} STATIC
        ${VKWRAPPER_FILE})

target_link_libraries(${VKWRAPPER}
        )