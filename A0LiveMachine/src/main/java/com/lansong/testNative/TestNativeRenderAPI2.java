package com.lansong.testNative;

/**
 * Description : 杭州蓝松科技有限公司
 *
 * @author guozhijun
 * @date 2022/7/25
 */
public class TestNativeRenderAPI2 {
    static {
        System.loadLibrary("VisionSDKPixel");
        System.loadLibrary("DemoNative");
    }


    public native static long initRender(String path1, String path2, String path3, int width, int height);

    /**
     * 抠图一帧,
     * 工作在GPU语境下
     */
    public native static boolean mattingOneFrameOnRGBA(long handle, int width, int height,int rotate, byte[] rgbaSrc, byte[] rgbaDst);
    public native static boolean mattingOneFrameWithNv21(long handle, int width, int height,int rotate, byte[] rgbaSrc, byte[] rgbaDst);

    /**
     * 释放;
     */
    public native static void releaseOnRGBA(long handle);

    public native static boolean pushBackGroundRGBA(long handle, int width,int height,byte[] rgba);

    public native static boolean pushBackGroundWithNv21(long handle, int width,int height,int rotate,byte[] rgba);



    public native static boolean testAddRgbaLayer(long handle, int width,int height,byte[] rgba);

    public native static boolean testAddLayerWithNv21(long handle, int width,int height,int rotate,byte[] rgba);

    // 添加图层，返回图层对象
    public native static long addRgbaLayer(long handle, int width,int height,byte[] rgba);
    public native static long addLayerWithNv21(long handle, int width,int height,int rotate,byte[] rgba);


    // 删除图层
    public native static boolean testRemoveMattingLayer(long handle);
    public native static boolean testRemoveBackGroundLayer(long handle);

    public native static boolean removeLayer(long handle, long layerId);

    // 获取图层
    public native static boolean testGetMattingLayer(long handle);
    public native static boolean testGetBackGroundLayer(long handle);

    public native static long getMattingLayer(long handle);
    public native static long getBackGroundLayer(long handle);

    public native static boolean testGetAllLayer(long handle);


    // 设置图层对象位置
    public native static boolean testSetLayerPosition(long handle, long layer,int position);

    public native static float getMattingOneFrameOnRGBATimeMS();


    public native static float getGLDrawOneFrameTimeMS(long handle);


    //参数设置;
    public native static void setGreenMattingType(long handle, int type);

    public native static void setMattingLevel(long handle, int level);




    public native static void setGreenMinThreshold(long handle, float min);

    public native static void setGreenMaxThreshold(long handle, float max);

    public native static float getGreenMaxThreshold(long handle);

    public native static float getGreenMinThreshold(long handle);

    public native static void setBlueMinThreshold(long handle, float value);

    public native static float getBlueMinThreshold(long handle);

    public native static void setBlueMaxThreshold(long handle, float value);

    public native static float getBlueMaxThreshold(long handle);

    public native static void setRedMinThreshold(long handle, float value);

    public native static void setRedMaxThreshold(long handle, float value);

    public native static float getRedMinThreshold(long handle);

    public native static float getRedMaxThreshold(long handle);



}
