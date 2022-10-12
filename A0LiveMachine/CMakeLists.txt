# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html
# Sets the minimum version of CMake required to build the native library.




cmake_minimum_required(VERSION 3.4.1)


set(CMAKE_VERBOSE_MAKEFILE on)
# 链接动态库;
set(libs_DIR ../LanSongSDK/src/main/jniLibs/${ANDROID_ABI})
link_directories(${libs_DIR})

# 头文件;
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)


include_directories(../LanSongSDK/src/main/cpp/sdk_header)


add_library(
        DemoNative

        SHARED

        src/main/cpp/TestRender.cpp
        src/main/cpp/TestRender.h
        )

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_RELEASE} -s")


find_library(
        log-lib
        android

        GLESv2
        log
        EGL)

target_link_libraries(
        DemoNative
        android
        VisionSDKPixel
        log
        GLESv2
        EGL
        ${log-lib}
        EGL)
