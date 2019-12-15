#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <optional>
#include <array>
#include <set>
#include <unordered_map>
#include "string.h"
#include "errno.h"
#include <android_native_app_glue.h>
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <android/log.h>

#ifndef  LOG_TAG
#define  LOG_TAG "GPU_Bench"
#endif

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
// Replace printf to logcat output.
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);