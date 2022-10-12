//
// Created by sno on 2022/9/1.
//

#ifndef GZJ_HARDWARE_ALL_ZSLAYER_H
#define GZJ_HARDWARE_ALL_ZSLAYER_H


#include "ZSCppUtils.h"


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <vector>
#include <mutex>
#include <sys/stat.h>

#include "ZSGreenMatting.h"


class DLNv21Drawable;
class DLFBOBoard;
class DLTransformIO;
class DLTransform;


typedef enum {
    LAYER_INPUT_RGBA = 0,
    LAYER_INPUT_NV21 = 1,
    LAYER_INPUT_NV12 = 2

} ZSInputType;

typedef enum {
    POSITION_NONE,
    LEFT_TOP,
    LEFT_BOTTOM,
    RIGHT_TOP,
    RIGHT_BOTTOM,

    //新增;
    LEFT,
    TOP,
    RIGHT,
    BOTTOM,
    CENTER
} ZSPosition;


typedef enum {
    /**
     * 无缩放形式.则内部会根据不同的素材,采用默认形式;
     */
    SCALE_TYPE_NONE,
    /**
     * 原始大小
     * 直接放入, 不做任意处理;
     */
    ORIGINAL,
    /**
     * 忽略百分比,把宽度等于容器的宽度, 高度等于容器的高度,填满整个容器.
     * 这样有些画面可能会变形;
     */
    FILL_COMPOSITION,

    /**
     * 裁剪填满 放入到容器中;
     * 把视频的中心点放到容器的中心点,然后 把画面等比例提填满整个容器,把多的部分裁剪掉.
     */
    CROP_FILL_COMPOSITION,

    /**
     * 视频缩放模式
     * 如果视频宽度大于高度, 则宽度和容器对齐, 然后等比例调整高度;
     * 如果高度大于宽度, 则反之.
     */
    VIDEO_SCALE_TYPE,

} ZSScaleType;


#ifdef __cplusplus
extern "C" {
#endif


#pragma pack(push) //保存对齐状态
#pragma pack(8)//设定为8字节对齐

class PUBLIC ZSLayer {


public:

    ZSLayer(int compWidth, int compHeight, int width, int height,int rotate, ZSInputType type);

    void initOnGPU();

    void drawLinkOnGPU();

    void drawOnGPU();

    int getEndTexture();


    void releaseOnGPU();



    bool isAfterInit();
    void setLayerPosition(int pos);
    void setGreenMatting(ZSGreenMatting *matting);

public:
//外部可见的类;
//容器宽高

/**
 * 获取容器宽度
 * @return
 */
    int getCompWidth();

    /**
     * 获取容器高度
     * @return
     */
    int getCompHeight();

    /**
     * 获取原始宽度
     * @return
     */
    int getOriginalWidth();

    /**
     * 获取原始高度
     * @return
     */
    int getOriginalHeight();

    /**
     * 获取数据的宽高
     * 当旋转角度是90 或270的时候, 等于高度;
     * @return
     */
    int  getDataWidth();

    /**
     * 获取数据的高度;
     * 当旋转角度是90 或270的时候, 等于宽度
     * @return
     */
    int getDataHeight();

    /**
     * push输入rgba的图像数据,
     * @param data 指针长度一定等于宽度*高度*4;
     */
    void pushRgbaDataFromOut(unsigned char *data);
    void pushNv21DataFromOut(unsigned char *data);

    /**
     * 缩放
     * @param type
     */
    void setScaleType(ZSScaleType type);

    /**
     * 缩放到具体的宽高
     * @param width
     * @param height
     */
    void setScaledValue(float width, float height);

    /**
     * 获取缩放后的宽度
     * @return
     */
    float getScaleWidth();

    /**
     * 获取缩放后的高度
     * @return
     */
    float getScaleHeight();


    /**
     * 设置具体的位置, 左上角是0.0;
     * @param xPos
     * @param yPos
     */
    void setPosition(float xPos, float yPos);

    /**
     * 设置枚举类型位置
     * @param position
     */
    void setPosition(ZSPosition position);

    /**
     * 获取位置X坐标
     * @return
     */
    float getPositionX();

    /**
     * 获取位置Y坐标;
     * @return
     */
    float getPositionY();

    /**
     * 设置角度. 0--360;
     * @param angle
     */
    void setRotation(float angle);

    /**
     * 获取角度;
     * @return
     */
    float getRotation();



    void setObject(long object);

    long getObject();

    void setName(int8_t *name);

    int8_t *getName();


    /**
     * 获取在容器中的图层位置;
     * @return
     */
    int  getLayerPositionAtRender();


protected:
    void setEnable(bool is) {
        isEnable = is;
    }


private:

    int compWidth;
    int compHeight;


    int originalWidth=0;
    int originalHeight=0;
    int originalRotate=0;


    //角度
    float rotateAngle;

    //缩放
    float scaleWidth;
    float scaleHeight;

    //位置
    float positionX = 0;
    float positionY = 0;


    GLuint src_rgba_texture = -1;

    DLNv21Drawable *nv21Drawable= nullptr;
    DLFBOBoard *fboBoard= nullptr;

    unsigned char *ptr_input_data = nullptr;
    volatile bool input_data_update = true;


    GLuint endTexture = -1;

    bool isEnable = true;

    DLTransformIO *transformIo;

    DLTransform *drawPass = nullptr;



    ZSGreenMatting *pGreenMatting = nullptr;

    ZSInputType input_type=LAYER_INPUT_RGBA;


    int layerPositionAtRender=0;

    long user_object;

    //用户设置的图层名字;
    int8_t *layer_name = (int8_t *) "notSet";

    std::mutex file_io_mtx;//线程锁
};
#pragma pack(pop)
#ifdef __cplusplus
}
#endif

#endif //GZJ_HARDWARE_ALL_ZSLAYER_H
