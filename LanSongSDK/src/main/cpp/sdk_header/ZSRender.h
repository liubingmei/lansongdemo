//
// Created by sno on 2022/9/1.
//

#ifndef GZJ_HARDWARE_ALL_ZSLAYERRENDER_H
#define GZJ_HARDWARE_ALL_ZSLAYERRENDER_H

#include "ZSLayer.h"


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


class ZSGpuThread;

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push) //保存对齐状态
#pragma pack(32)//设定为32字节对齐


class PUBLIC ZSRender {

public:

    /**
     * 创建一个渲染容器;
     * @param model1 模型1,2,3
     * @param model2
     * @param model3
     */
    ZSRender(char *model1,
             char *model2,
             char *model3);

    ~ZSRender();


    /**
     * 创建渲染容器大小;
     * @param width
     * @param height
     */
    void initWithCompSize(int width, int height);

     /**
      * 要抠图的相机画面输入;
      * @param width  宽度
      * @param height  高度
      * @param rotate 当前无效果
      * @param data rgba数据; 长度一定等于width*height *4;
      * @return 合成后的图像, 图像的宽高等于容器的宽高;
      */
    void *mattingOneFrameWithRgba(int width, int height, int rotate,void *data);

    /**
     *
     * @param width
     * @param height
     * @param rotate
     * @param data
     * @return
     */
    void *mattingOneFrameWithNv21(int width, int height, int rotate,void *data);

    /**
     * 输入背景流
     * 可实时切换, 输入不同的分辨率;
     * @param width
     * @param height
     * @param rgbaData
     */
    bool setBackGroundRgba(int width, int height, void *rgbaData);
    bool setBackGroundWithNv21(int width, int height,int rotate, void *rgbaData);

    /**
     * 释放容器;
     */
    void release();

    /**
     * 设置抠图的相机的参数设置;
     * 比如抠图范围, 强度等.
     * @return
     */
    ZSGreenMatting *getGreenMatting();


    /**
     * 增加一个RGBA的图层, 图层增加后
     * @param width 图层的宽度
     * @param height 图层的高度
     * @return 返回图层对象
     */
    ZSLayer *addRgbaLayer(int width, int  height);


    /**
     * 增加nv21图层;
     * @param width  nv21数据的宽度
     * @param height  nv21数据的高度
     * @param rotate 图层旋转角度
     * @return
     */
    ZSLayer *addNv21Layer(int width, int  height, int rotate);


    /**
     * 删除一个图层
     * @param layer 图层对象
     */
    void removeLayer(ZSLayer *layer);


    /**
     * 设置图层的上下级位置
     * @param layer  图层对象
     * @param position  要设置的位置
     */
    void setLayerPosition(ZSLayer * layer, int position);


    /**
     * 读取所有的图层对象
     * 此方法只是拷贝一份list并返回,
     * @return
     */
    std::list<ZSLayer *> *getAllLayers();


    ZSLayer *getMattingLayer();
    ZSLayer *getBackGroundLayer();

    /**
     * 获取一帧的opengl的渲染时间;
     * @return
     */
    float getOpenGLOneFrameTime();


public:
//一下是内部线程使用, 外界请勿使用;
    void addLayerOnGpuEvent();

    void removeLayerOnGpuEvent();


    void drawOneFrameEvent();

    void releaseOnGpuEvent();




    void changePositionEvent();


    void updateLayerPosition();


private:
    bool waitEventFinish(size_t timeOutMs);

    void notifyEventFinish();

private:

    ZSGpuThread *gpuThread;

    //相机层;
    ZSLayer *cameraLayer;


    ZSLayer *backGroundLayer;


    std::list<ZSLayer *> *layerArray;

    void *ptrDstRgba;

    ZSGreenMatting *pGreenMatting;

    float gl_draw_one_frame_time;

    int compWidth;
    int compHeight;

    sem_t head_data_available;

    //外接传递到thread中的指针;
    void *eventObject;
    int eventArg1;

};
#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif //GZJ_HARDWARE_ALL_ZSLAYERRENDER_H
