//
// Created by sno on 2022/8/8.
//

#ifndef GZJ_ALL_ZSGPPMACRO_H
#define GZJ_ALL_ZSGPPMACRO_H

#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <list>
#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#include <algorithm>
#include <memory>
#include <iostream>
#include <array>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>








//这里不能包括gl2.h或gl3.h;

// Interface visibility
#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_DLL
#ifdef __GNUC__
#define PUBLIC __attribute__((dllexport))
#else  // __GNUC__
#define PUBLIC __declspec(dllexport)
#endif  // __GNUC__
#else   // BUILDING_DLL
#ifdef __GNUC__
#define PUBLIC __attribute__((dllimport))
#else
#define PUBLIC __declspec(dllimport)
#endif  // __GNUC__
#endif  // BUILDING_DLL
#define LOCAL
#else  // _WIN32 || __CYGWIN__
#if __GNUC__ >= 4
#define PUBLIC __attribute__((visibility("default")))
#define LOCAL __attribute__((visibility("hidden")))
#else
#define PUBLIC
#define LOCAL
#endif
#endif







// namespcae
#define Render_NS__(x) LSORender##x
#define Render_NS_(x) Render_NS__(x)
#define Render_NS Render_NS_()




//---------字符串的前缀;
#define STRINGIZE(x) #x
#define STRINGIZE2(x) STRINGIZE(x)
#define SHADER_STRING(text)  STRINGIZE2(text)



#define TAG "LanSongSDK"



// Log
#ifdef __ANDROID__

#include <jni.h>
#include <android/log.h>
#define LOGDT(fmt, tag, ...)                                                                                           \
    __android_log_print(ANDROID_LOG_DEBUG, tag, ("%s [File %s][Line %d] " fmt), __PRETTY_FUNCTION__, __FILE__,         \
                        __LINE__, ##__VA_ARGS__);                                                                      \
    fprintf(stdout, ("D/%s: %s [File %s][Line %d] " fmt), tag, __PRETTY_FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGIT(fmt, tag, ...)                                                                                           \
    __android_log_print(ANDROID_LOG_INFO, tag, ("%s [File %s][Line %d] " fmt), __PRETTY_FUNCTION__, __FILE__,          \
                        __LINE__, ##__VA_ARGS__);                                                                      \
    fprintf(stdout, ("I/%s: %s [File %s][Line %d] " fmt), tag, __PRETTY_FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGET(fmt, tag, ...)                                                                                           \
    __android_log_print(ANDROID_LOG_ERROR, tag, ("%s [File %s][Line %d] " fmt), __PRETTY_FUNCTION__, __FILE__,         \
                        __LINE__, ##__VA_ARGS__);                                                                      \
    fprintf(stderr, ("E/%s: %s [File %s][Line %d] " fmt), tag, __PRETTY_FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGDT(fmt, tag, ...)                                                                                           \
    fprintf(stdout, ("D/%s: %s [File %s][Line %d] " fmt), tag, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGIT(fmt, tag, ...)                                                                                           \
    fprintf(stdout, ("I/%s: %s [File %s][Line %d] " fmt), tag, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGET(fmt, tag, ...)                                                                                           \
    fprintf(stderr, ("E/%s: %s [File %s][Line %d] " fmt), tag, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#endif  //__ANDROID__





//#define LOGD(fmt, ...) LOGDT(fmt, DEFAULT_TAG, ##__VA_ARGS__)
//#define LOGI(fmt, ...) LOGIT(fmt, DEFAULT_TAG, ##__VA_ARGS__)
//#define LOGE(fmt, ...) LOGET(fmt, DEFAULT_TAG, ##__VA_ARGS__)
#define LOGE_IF(cond, fmt, ...)                                                                                        \
    if (cond) {                                                                                                        \
        LOGET(fmt, DEFAULT_TAG, ##__VA_ARGS__);                                                                        \
    }





#define LSOLog_i(...)  __android_log_print(ANDROID_LOG_INFO, "LanSongSDK", __VA_ARGS__); // 定义LOGE类型

#define LSOLog_e(...)  __android_log_print(ANDROID_LOG_ERROR, "LanSongSDK", __VA_ARGS__);

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "LanSongSDK", __VA_ARGS__));
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "LanSongSDK", __VA_ARGS__));
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "LanSongSDK", __VA_ARGS__));


#define CHECK_TIME_INIT_LanSongSDKLSdelete \
    float time_use = 0;  \
    struct timeval start1; \
    struct timeval end1;

#define CHECK_TIME_START_LanSongSDKLSdelete gettimeofday(&start1, NULL);

#define CHECK_TIME_END_LanSongSDKLSdelete(tag) \
    gettimeofday(&end1, NULL); \
    time_use = (end1.tv_sec - start1.tv_sec) * 1000 + (end1.tv_usec - start1.tv_usec)/1000; \
    LOGE("%s 耗时 is %f ms \n", tag,time_use);



#define LanSongSDKLSdelete(...)  __android_log_print(ANDROID_LOG_ERROR, "LanSongSDKlsdelete", __VA_ARGS__); // 定义LOGE类型


#define LanSongSDKLSdelete_LINE  __android_log_print(ANDROID_LOG_ERROR, "LanSongSDKlsdelete", " function:%s, line:%d",__FUNCTION__,__LINE__);




//抠像默认强度;  强度40
#define GREEN_MATTING_LEVEL_DEFAULT  40


//绿色
#define  GREEN_MIN_START  0.0
#define  GREEN_MIN_END  150.0
#define  GREEN_MIN_DEFAULT   0.0


#define  GREEN_MAX_START  150.0

//如果单独抠绿色,则最大170就可以了.但很多光线的影响,青色也要抠掉;这里直接到210;
#define  GREEN_MAX_END  250.0
#define  GREEN_MAX_DEFAULT GREEN_MAX_END

// 这样是青色;
//#define  GREEN_MAX_DEFAULT 185.0


//蓝色
#define  BLUE_MIN_START  170.0
#define  BLUE_MIN_END  200.0
#define  BLUE_MIN_DEFAULT  BLUE_MIN_START



//中间大部分的场景下, 是调节 蓝色的最大阈值,
#define  BLUE_MAX_START  220.0
#define  BLUE_MAX_END  260.0
#define  BLUE_MAX_DEFAULT  260.0


//红色
#define  RED_MIN_START  230.0
#define  RED_MIN_END  365.0
#define  RED_MIN_DEFAULT RED_MIN_START


#define  RED_MAX_START  360.0
#define  RED_MAX_END  390.0
#define  RED_MAX_DEFAULT  RED_MAX_END

#define SATURATION_FACTOR_DEFAULT  1.3





#define LanSongSDKLSDelete(...)  __android_log_print(ANDROID_LOG_ERROR, "LanSongSDKlsdelete", __VA_ARGS__); // 定义LOGE类型




#define CHECK_TIME_INIT_LanSongSDKLSdelete \
    float time_use = 0;  \
    struct timeval start1; \
    struct timeval end1;

#define CHECK_TIME_START_LanSongSDKLSdelete gettimeofday(&start1, NULL);

#define CHECK_TIME_END_LanSongSDKLSdelete(tag) \
    gettimeofday(&end1, NULL); \
    time_use = (end1.tv_sec - start1.tv_sec) * 1000 + (end1.tv_usec - start1.tv_usec)/1000; \
    LOGE("%s 耗时 is %f ms \n", tag,time_use);



#define LanSongSDKLSDelete_TEST_SPEED_INIT \
{ \
    checkDecoderFrameStartUs = -1;\
    checkDecoderFrameCount = 0;\
};

/**
 * 测试解码帧率;
 */

#define  LanSongSDKLSDelete_TEST_SPEED_ENTRY(tag) \
{ \
    \
        checkDecoderFrameCount++;\
        if (checkDecoderFrameStartUs == -1) { \
                       timeval tv; \
                    gettimeofday(&tv, 0); \
            checkDecoderFrameStartUs =(int64_t) tv.tv_sec * 1000000 + (int64_t) tv.tv_usec;\
        } else {                     \
               timeval tv; \
                gettimeofday(&tv, 0);    \
              int64_t currentTime =(int64_t) tv.tv_sec * 1000000 + (int64_t) tv.tv_usec;\
              float second = (float) (currentTime - checkDecoderFrameStartUs) / 1000000.0;\
\
            float framePts =(float) checkDecoderFrameCount / second;\
            LOGI("TEST %s speed. count: %d,speed:%f ",tag, checkDecoderFrameCount , framePts);\
        }\
};

// Math
#ifndef UP_DIV
#define UP_DIV(x, y) (((int)(x) + (int)(y) - (1)) / (int)(y))
#endif
#ifndef ROUND_UP
#define ROUND_UP(x, y) (((int)(x) + (int)(y) - (1)) / (int)(y) * (int)(y))
#endif
#ifndef ALIGN_UP4
#define ALIGN_UP4(x) ROUND_UP((x), 4)
#endif
#ifndef ALIGN_UP8
#define ALIGN_UP8(x) ROUND_UP((x), 8)
#endif
#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif
#ifndef ABS
#define ABS(x) ((x) > (0) ? (x) : (-(x)))
#endif





//从jvm 获取字节的宏定义;
#define LOCK_ARRAY_FROM_JVM(bytes) \
          (unsigned char *)env->GetByteArrayElements(bytes,0);
     //   (unsigned char *)env->GetPrimitiveArrayCritical(bytes,0)

        //第一个参数是java传递来的;
#define UNLOCK_ARRAY_TO_JVM(bytes,srcBuf) \
       env->ReleaseByteArrayElements(bytes,( jbyte*)srcBuf,0);

   // env->ReleasePrimitiveArrayCritical(bytes,srcBuf,0);
#endif //GZJ_ALL_ZSGPPMACRO_H
