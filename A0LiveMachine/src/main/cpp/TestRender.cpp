//
// Created by sno on 2022/9/23.
//

#include "TestRender.h"


#include <sys/time.h>
#include "../../../../LanSongSDK/src/main/cpp/sdk_header/ZSRender.h"
#include <jni.h>

#include <android/log.h>


//从jvm 获取字节的宏定义;
#define LOCK_ARRAY_FROM_JVM(bytes) \
          (unsigned char *)env->GetByteArrayElements(bytes,0);
//   (unsigned char *)env->GetPrimitiveArrayCritical(bytes,0)

//第一个参数是java传递来的;
#define UNLOCK_ARRAY_TO_JVM(bytes,srcBuf) \
       env->ReleaseByteArrayElements(bytes,( jbyte*)srcBuf,0);



char *jstring2string(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}



extern "C"
JNIEXPORT void JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_setGreenMattingType(JNIEnv *env, jclass clazz,
                                                                    jlong handle, jint type) {

    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        render->getGreenMatting()->setGreenMattingType(type);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_setMattingLevel(JNIEnv *env, jclass clazz,
                                                                jlong handle, jint level) {


    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        render->getGreenMatting()->setMattingLevel(level);
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_setGreenMinThreshold(JNIEnv *env, jclass clazz,
                                                                     jlong handle,
                                                                     jfloat min) {

    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        render->getGreenMatting()->setGreenMinThreshold(min);
    }

}
extern "C"
JNIEXPORT void JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_setGreenMaxThreshold(JNIEnv *env, jclass clazz,
                                                                     jlong handle,
                                                                     jfloat max) {

    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        render->getGreenMatting()->setGreenMaxThreshold(max);
    }
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_getGreenMaxThreshold(JNIEnv *env, jclass clazz,
                                                                     jlong handle) {
    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        return render->getGreenMatting()->getGreenMaxThreshold();
    }else{
        return 0.0;
    }
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_getGreenMinThreshold(JNIEnv *env, jclass clazz,
                                                                     jlong handle) {

    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        return render->getGreenMatting()->getGreenMinThreshold();
    }else{
        return 0.0;
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_setBlueMinThreshold(JNIEnv *env, jclass clazz,
                                                                    jlong handle,
                                                                    jfloat value) {
    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        render->getGreenMatting()->setBlueMinThreshold(value);
    }

}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_getBlueMinThreshold(JNIEnv *env, jclass clazz,
                                                                    jlong handle) {


    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        return render->getGreenMatting()->getBlueMinThreshold();
    }else{
        return 0.0;
    }

}
extern "C"
JNIEXPORT void JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_setBlueMaxThreshold(JNIEnv *env, jclass clazz,
                                                                    jlong handle,
                                                                    jfloat value) {

    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        render->getGreenMatting()->setBlueMaxThreshold(value);
    }


}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_getBlueMaxThreshold(JNIEnv *env, jclass clazz,
                                                                    jlong handle) {


    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        return render->getGreenMatting()->getBlueMaxThreshold();
    }else{
        return 0.0;
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_setRedMinThreshold(JNIEnv *env, jclass clazz,
                                                                   jlong handle,
                                                                   jfloat value) {

    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        render->getGreenMatting()->setRedMinThreshold(value);
    }

}
extern "C"
JNIEXPORT void JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_setRedMaxThreshold(JNIEnv *env, jclass clazz,
                                                                   jlong handle,
                                                                   jfloat value) {

    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        render->getGreenMatting()->setRedMaxThreshold(value);
    }

}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_getRedMinThreshold(JNIEnv *env, jclass clazz,
                                                                   jlong handle) {


    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        return render->getGreenMatting()->getRedMinThreshold();
    }else{
        return 0;
    }
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_getRedMaxThreshold(JNIEnv *env, jclass clazz,
                                                                   jlong handle) {

    ZSRender *render = (ZSRender *) handle;
    if(render!= nullptr ){
        return render->getGreenMatting()->getRedMaxThreshold();
    }else{
        return 0;
    }
}






extern "C"
JNIEXPORT jlong JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_initRender(JNIEnv *env, jclass clazz,
                                                           jstring path1, jstring path2,
                                                           jstring path3,
                                                           int width, int height) {
    char *modelPath1 = jstring2string(env, path1);
    char *modelPath2 = jstring2string(env, path2);
    char *modelPath3 = jstring2string(env, path3);




    ZSRender *render=new ZSRender(modelPath1,
                                  modelPath2,
                                  modelPath3);
    render->initWithCompSize(width,height);
    return (long)render;

}

float lansongSDK_matting_timeMs = 0;

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_mattingOneFrameOnRGBA(JNIEnv *env, jclass clazz,
                                                                      jlong handle, jint width,
                                                                      jint height,jint rotate, jbyteArray rgba_src,
                                                                      jbyteArray rgba_dst) {

    unsigned char *srcBuf = (unsigned char *) LOCK_ARRAY_FROM_JVM(rgba_src);
    unsigned char *dstBuf = (unsigned char *) LOCK_ARRAY_FROM_JVM(rgba_dst);


    bool  ret= false;


    struct timeval start1;
    struct timeval end1;

    gettimeofday(&start1, NULL);

    void *ptr= nullptr;

    ZSRender *matting = (ZSRender *) handle;
    if (matting != nullptr) {
        ptr= matting->mattingOneFrameWithRgba(width,height,rotate,srcBuf);
    }

    gettimeofday(&end1, NULL); \
    lansongSDK_matting_timeMs = (end1.tv_sec - start1.tv_sec) * 1000 + (end1.tv_usec - start1.tv_usec) / 1000; \

    if(ptr!= nullptr){
        memcpy(dstBuf,ptr,width*height*4);
        ret= true;
    }

    UNLOCK_ARRAY_TO_JVM(rgba_dst, dstBuf);
    UNLOCK_ARRAY_TO_JVM(rgba_src, srcBuf);

    return ret;
}
#define LanSongSDKLSDelete(...)  __android_log_print(ANDROID_LOG_ERROR, "LanSongSDKlsdelete", __VA_ARGS__); // 定义LOGE类型


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_mattingOneFrameWithNv21(JNIEnv *env, jclass clazz,
                                                                        jlong handle, jint width,
                                                                        jint height,jint rotate, jbyteArray nv21_bytes,
                                                                        jbyteArray rgba_dst) {

    unsigned char *nv21Buf = (unsigned char *) LOCK_ARRAY_FROM_JVM(nv21_bytes);
    unsigned char *dstBuf = (unsigned char *)LOCK_ARRAY_FROM_JVM(rgba_dst);

    bool  ret= false;



    struct timeval start1;
    struct timeval end1;

    gettimeofday(&start1, NULL);

    void *ptr= nullptr;

    ZSRender *pRender = (ZSRender *) handle;

    if (pRender != nullptr) {
        ptr= pRender->mattingOneFrameWithNv21(width, height, rotate, nv21Buf);
    }


    gettimeofday(&end1, NULL); \
    lansongSDK_matting_timeMs = (end1.tv_sec - start1.tv_sec) * 1000 + (end1.tv_usec - start1.tv_usec) / 1000; \

    if(ptr!= nullptr){
        memcpy(dstBuf,ptr,width*height*4);
        ret= true;
    }

    UNLOCK_ARRAY_TO_JVM(rgba_dst, dstBuf);
    UNLOCK_ARRAY_TO_JVM(nv21_bytes, nv21Buf);

    return ret;
}


extern "C"
JNIEXPORT jfloat JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_getMattingOneFrameOnRGBATimeMS(JNIEnv *env, jclass clazz) {
    return lansongSDK_matting_timeMs;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_releaseOnRGBA(JNIEnv *env, jclass clazz,
                                                              jlong handle) {

    ZSRender *pRender = (ZSRender *) handle;
    if (pRender != nullptr) {
        pRender->release();
    }

}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_pushBackGroundRGBA(JNIEnv *env, jclass clazz,
                                                                   jlong handle, jint width,
                                                                   jint height, jbyteArray rgba) {
    unsigned char *srcBuf = (unsigned char *) LOCK_ARRAY_FROM_JVM(rgba);

    bool  ret= false;
    ZSRender *matting = (ZSRender *) handle;
    if (matting != nullptr) {
        ret= matting->setBackGroundRgba(width, height, srcBuf);
    }
    UNLOCK_ARRAY_TO_JVM(rgba, srcBuf);
    return ret;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_pushBackGroundWithNv21(JNIEnv *env, jclass clazz,
                                                                       jlong handle, jint width,
                                                                       jint height,jint rotate, jbyteArray rgba) {
    unsigned char *srcBuf = (unsigned char *) LOCK_ARRAY_FROM_JVM(rgba);

    bool  ret= false;
    ZSRender *matting = (ZSRender *) handle;
    if (matting != nullptr) {
        ret= matting->setBackGroundWithNv21(width, height,rotate, srcBuf);
    }
    UNLOCK_ARRAY_TO_JVM(rgba, srcBuf);
    return ret;
}



extern "C"
JNIEXPORT jfloat JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_getGLDrawOneFrameTimeMS(JNIEnv *env, jclass clazz,long handle) {
    ZSRender *matting = (ZSRender *) handle;
    if(matting!= nullptr){
        return matting->getOpenGLOneFrameTime();
    }else{
        return 0.0;
    }
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_testAddLayer(JNIEnv *env, jclass clazz,
                                                             jlong handle, jint width, jint height,
                                                             jbyteArray rgba) {




    ZSRender *pRender = (ZSRender *) handle;
    if(pRender != nullptr){
        ZSLayer *layer=pRender->addRgbaLayer(width, height);
        if(layer!= nullptr){
            layer->setScaledValue(540,540);
            layer->setPosition(LEFT_TOP);

            unsigned  char *src_buf= LOCK_ARRAY_FROM_JVM(rgba);
            layer->pushRgbaDataFromOut(src_buf);
            UNLOCK_ARRAY_TO_JVM(rgba,src_buf);
        }
        return true;
    }else{
        return false;
    }
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_testAddLayerWithNv21(JNIEnv *env, jclass clazz,
                                                                      jlong handle, jint width,
                                                                      jint height,jint rotate, jbyteArray nv21) {
    ZSRender *pRender = (ZSRender *) handle;
    if(pRender != nullptr){
        ZSLayer *layer=pRender->addNv21Layer(width, height,rotate);
        if(layer!= nullptr){
            layer->setScaledValue(540,540); //设置缩放值
            layer->setPosition(LEFT_TOP); //设置位置
            layer ->setName((int8_t *) "nv21"); //设置一个名字, 用于调试.
            layer->setRotation(90); // 旋转90度
            layer->setScaleType(ORIGINAL); //缩放 原始大小
            unsigned  char *src_buf= LOCK_ARRAY_FROM_JVM(nv21);
            layer->pushNv21DataFromOut(src_buf);
            UNLOCK_ARRAY_TO_JVM(nv21,src_buf);
        }
        return true;
    }else{
        return false;
    }
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_testRemoveMattingLayer(JNIEnv *env, jclass clazz,
                                                                        jlong handle) {
    ZSRender *pRender = (ZSRender *) handle;
    if(pRender != nullptr){
        ZSLayer *layer =pRender->getMattingLayer();
        pRender-> removeLayer(layer);
        return true;
    }
    else{
        return false;
    }
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_testRemoveBackGroundLayer(JNIEnv *env, jclass clazz,
                                                                           jlong handle) {
    ZSRender *pRender = (ZSRender *) handle;
    if(pRender != nullptr){
        ZSLayer *layer =pRender->getBackGroundLayer();
        pRender-> removeLayer(layer);
        return true;
    }
    else{
        return false;
    }
}



extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_testGetMattingLayer(JNIEnv *env, jclass clazz,
                                                                     jlong handle) {
    ZSRender *pRender = (ZSRender *) handle;
    if(pRender != nullptr){
        ZSLayer *layer =pRender->getMattingLayer();
        if(layer!= nullptr){

            return true;
        }else{
            return false;
        }
    }
    else{
        return false;
    }
}


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_testGetBackGroundLayer(JNIEnv *env, jclass clazz,
                                                                        jlong handle) {
    ZSRender *pRender = (ZSRender *) handle;
    if(pRender != nullptr){
        ZSLayer *layer =pRender->getBackGroundLayer();
        if(layer!= nullptr){
            return true;
        }else{
            return false;
        }
    }
    else{
        return false;
    }
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_testGetAllLayer(JNIEnv *env, jclass clazz,
                                                                 jlong handle) {
    ZSRender *pRender = (ZSRender *) handle;
    if(pRender != nullptr){
        std::list<ZSLayer *> *layers =pRender->getAllLayers();
        // 从layers 遍历所有图层
        for (std::list<ZSLayer *>::iterator it = layers->begin(); it != layers->end(); it++) {
            ZSLayer *layer = *it;
            std::cout << *it;
            LOGI("layer name=%s",layer->getName());
            LOGI("layer 容器宽度=%d",layer->getCompWidth());
            LOGI("layer 容器高度=%d",layer->getCompHeight());
            LOGI("layer 数据的宽度=%d",layer->getDataWidth());
            LOGI("layer 数据的高度=%d",layer->getDataHeight());
            LOGI("layer 获取在容器中的图层位置=%d",layer->getLayerPositionAtRender());
            LOGI("layer 位置X坐标=%f",layer->getPositionX());
            LOGI("layer 位置Y坐标=%f",layer->getPositionY());
            LOGI("layer 旋转角度=%f",layer->getRotation());
            LOGI("layer 获取缩放后的宽度=%f", layer ->getScaleWidth());
            LOGI("layer 获取缩放后的高度=%f", layer ->getScaleHeight());
            LOGI("layer 获取原始宽度=%d", layer ->getOriginalWidth());
            LOGI("layer 获取原始高度=%d", layer ->getOriginalHeight());
        }
        return true;
    }
    else{
        return false;
    }
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_lansong_testNative_TestNativeRenderAPI2_testSetMattingLayerPosition(JNIEnv *env,
                                                                             jclass clazz,
                                                                             jlong handle,
                                                                             jint position) {

    ZSRender *pRender = (ZSRender *) handle;
    // 设置图层上下级的位置
    if(pRender != nullptr){
        ZSLayer *layer =pRender->getBackGroundLayer();
        if(layer!= nullptr){
            pRender->setLayerPosition(layer,position);
            return true;
        }else{
            return false;
        }
    }
    else{
        return false;
    }


}