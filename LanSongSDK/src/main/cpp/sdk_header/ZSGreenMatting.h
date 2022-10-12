//
// Created by sno on 2022/7/25.
//

#ifndef GZJ_ALL_TEST_LSOGREENMATTINGWRAPPER_H
#define GZJ_ALL_TEST_LSOGREENMATTINGWRAPPER_H


#include "ZSCppUtils.h"


class GreenMattingGM1;
class GreenMattingGM2;
class GreenMattingGM3;

/**
 * 是ZSLayer中的一个filter;
 */
class PUBLIC ZSGreenMatting {


public:
    ZSGreenMatting();

    ~ZSGreenMatting();

    /**
     *  初始化, 工作在gpu语境下
     * @param path1 抠绿模型1的路径
     * @param path2 抠绿模型2的路径
     * @param path3 抠绿模型3的路径
     */
    void initWithLicenseOnGPU(unsigned char *path1, unsigned char *path2, unsigned char *path3);

    /**
     * 抠图一帧,
     * 工作在GPU语境下
     * @param width 纹理的宽度
     * @param height 纹理的高度
     * @param textureId 输入纹理id;
     * @return 结果输出;
     */
    int mattingOneFrameOnGPU(int width, int height, int textureId);


    /**
     * 释放;
     */
    void releaseOnGPU();


    //参数设置;
    void setGreenMattingType(int type);

    void setMattingLevel(int level);



    void setGreenMinThreshold(float min);

    void setGreenMaxThreshold(float max);

    float getGreenMaxThreshold();

    float getGreenMinThreshold();

    void setBlueMinThreshold(float value);

    float getBlueMinThreshold();

    void setBlueMaxThreshold(float value);

    float getBlueMaxThreshold();

    void setRedMinThreshold(float value);

    void setRedMaxThreshold(float value);


    float getRedMinThreshold();


    float getRedMaxThreshold();

private:


    GreenMattingGM1 *gm1;
    GreenMattingGM2 *gm2;
    GreenMattingGM3 *gm3;




};


#endif //GZJ_ALL_TEST_LSOGREENMATTINGWRAPPER_H
