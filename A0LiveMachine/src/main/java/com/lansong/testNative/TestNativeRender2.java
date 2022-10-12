package com.lansong.testNative;

/**
 * Description : 杭州蓝松科技有限公司
 *
 * @author guozhijun
 * @date 2022/7/25
 */
public class TestNativeRender2 {

    private long handler;

    public static final int GREEN_MATTING = 0;
    public static final int BLUE_MATTING = 1;
    public static final int RED_MATTING = 2;
    public static final int NONE = 3;


    //---各种默认值;
//抠像默认强度;  强度改成25;
    public static final int GREEN_MATTING_LEVEL_DEFAULT = 25;


    //绿色
    public static final float GREEN_MIN_START = 0.0f;
    public static final float GREEN_MIN_END = 100.0f;
    public static final float GREEN_MIN_DEFAULT = 80.0f;
    ;


    public static final float GREEN_MAX_START = 150.0f;

    //如果单独抠绿色,则最大170就可以了.但很多光线的影响,青色也要抠掉;这里直接到210;
    public static final float GREEN_MAX_END = 210.0f;
    public static final float GREEN_MAX_DEFAULT = GREEN_MAX_END;


    //蓝色
    public static final float BLUE_MIN_START = 170.0f;
    public static final float BLUE_MIN_END = 200.0f;
    public static final float BLUE_MIN_DEFAULT = BLUE_MIN_START;


    //中间大部分的场景下, 是调节 蓝色的最大阈值,
    public static final float BLUE_MAX_START = 220.0f;
    public static final float BLUE_MAX_END = 260.0f;
    public static final float BLUE_MAX_DEFAULT = 260.0f;


    //红色
    public static final float RED_MIN_START = 230.0f;
    public static final float RED_MIN_END = 365.0f;
    public static final float RED_MIN_DEFAULT = RED_MIN_START;


    public static final float RED_MAX_START = 360.0f;
    public static final float RED_MAX_END = 390.0f;
    public static final float RED_MAX_DEFAULT = RED_MAX_END;


    public  void initRender(String path1, String path2, String path3, int width, int height){
        handler = TestNativeRenderAPI2.initRender(path1, path2, path3,width,height);
    }

    /**
     * 抠图一帧,
     * 工作在GPU语境下
     */
    public   boolean mattingOneFrameWithRgba(int width, int height,int rotate, byte[] rgbaSrc, byte[] rgbaDst){
        return TestNativeRenderAPI2.mattingOneFrameOnRGBA(handler, width, height,rotate, rgbaSrc,rgbaDst);
    }

    public   boolean mattingOneFrameWithNv21(int width, int height,int rotate, byte[] rgbaSrc, byte[] rgbaDst){
        return TestNativeRenderAPI2.mattingOneFrameWithNv21(handler, width, height,rotate, rgbaSrc,rgbaDst);
    }


    /**
     * 释放;
     */
    public  void releaseOnRGBA()
    {
        if (handler != 0) {
            TestNativeRenderAPI2.releaseOnRGBA(handler);
            handler = 0;
        }
    }

    public boolean pushBackGroundRGBA(int width,int height,byte[] rgba)
    {
        return handler!=0 && TestNativeRenderAPI2.pushBackGroundRGBA(handler,width,height,rgba);
    }


    public boolean pushBackGroundWithNv21(int width,int height,int rotate,byte[] rgba)
    {
        return handler!=0 && TestNativeRenderAPI2.pushBackGroundWithNv21(handler,width,height,rotate,rgba);
    }


    public boolean testAddLayer(int width,int height,byte[] rgba)
    {
        return handler!=0 && TestNativeRenderAPI2.testAddLayer(handler,width,height,rgba);
    }
    public boolean testAddLayerWithNv21 (int width,int height,int rotate,byte[] rgba)
    {
        return handler!=0 && TestNativeRenderAPI2.testAddLayerWithNv21(handler,width,height,rotate,rgba);
    }

    // 删除图层
    public boolean testRemoveMattingLayer()
    {
        return handler!=0 && TestNativeRenderAPI2.testRemoveMattingLayer(handler);
    }
    public boolean testRemoveBackGroundLayer(){
        return handler!=0 && TestNativeRenderAPI2.testRemoveBackGroundLayer(handler);
    }

    // 获取图层
    public boolean testGetMattingLayer(){
        return handler!=0 && TestNativeRenderAPI2.testGetMattingLayer(handler);
    }
    public boolean testGetBackGroundLayer(){
        return handler!=0 && TestNativeRenderAPI2.testGetBackGroundLayer(handler);
    }
    public boolean testGetAllLayer(){
        return handler != 0 && TestNativeRenderAPI2.testGetAllLayer(handler);
    }




    public float getGLDrawOneFrameTimeMS()
    {
        if(handler!=0){
            return TestNativeRenderAPI2.getGLDrawOneFrameTimeMS(handler);
        }else{
            return 0.0f;
        }
    }


    private int greenType = 0;


    //参数设置;
    public void setGreenMattingType(int type) {
        greenType = 0;
        TestNativeRenderAPI2.setGreenMattingType(handler, type);
    }

    public int getMattingType() {
        return greenType;
    }


    private int currentLevel = 24;

    public void setMattingLevel(int level) {
        currentLevel = level;
        TestNativeRenderAPI2.setMattingLevel(handler, level);
    }

    public int getMattingLevel() {
        return currentLevel;
    }



    public void setGreenMinThreshold(float min) {
        TestNativeRenderAPI2.setGreenMinThreshold(handler, min);
    }

    public void setGreenMaxThreshold(float max) {
        TestNativeRenderAPI2.setGreenMaxThreshold(handler, max);
    }

    public float getGreenMaxThreshold() {
        return TestNativeRenderAPI2.getGreenMaxThreshold(handler);
    }

    public float getGreenMinThreshold() {
        return TestNativeRenderAPI2.getGreenMinThreshold(handler);
    }

    public void setBlueMinThreshold(float value) {
        TestNativeRenderAPI2.setBlueMinThreshold(handler, value);
    }

    public float getBlueMinThreshold() {
        return TestNativeRenderAPI2.getBlueMinThreshold(handler);
    }

    public void setBlueMaxThreshold(float value) {
        TestNativeRenderAPI2.setBlueMaxThreshold(handler, value);
    }

    public float getBlueMaxThreshold() {
        return TestNativeRenderAPI2.getBlueMaxThreshold(handler);
    }

    public void setRedMinThreshold(float value) {
        TestNativeRenderAPI2.setRedMinThreshold(handler, value);
    }

    public void setRedMaxThreshold(float value) {
        TestNativeRenderAPI2.setRedMaxThreshold(handler, value);
    }

    public float getRedMinThreshold() {
        return TestNativeRenderAPI2.getRedMinThreshold(handler);
    }

    public float getRedMaxThreshold() {
        return TestNativeRenderAPI2.getRedMaxThreshold(handler);
    }


    //-----------各种默认值;

}
