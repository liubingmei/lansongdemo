package com.lansong.testNative;


import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.os.Bundle;
import android.os.PowerManager;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.lansong.a0live.R;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;

/**
 * 测试底层的绘制
 * <p>
 * Description : 杭州蓝松科技有限公司
 *
 * @author guozhijun
 * @date 2022/8/11
 */
public class TestNativeRenderActivity extends AppCompatActivity implements Camera.PreviewCallback, SurfaceHolder.Callback, View.OnTouchListener {


    private Camera camera;
    private SurfaceView sv_main;
    private SurfaceHolder holder;
    private Camera.Parameters parameters;
    private int camWidth = 1920;
    private int camHeight = 1080;
    private ImageView imageView;
    private Bitmap bitmap;
    private TextView tvRunTime;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.native_render_layout);
        initSurfaceView();
    }


    private void initSurfaceView() {



        sv_main = (SurfaceView) findViewById(R.id.sv_main);
        imageView = findViewById(R.id.id_native_cpp_image_view);

        tvRunTime = findViewById(R.id.id_live_run_time_tv);

        sv_main.setOnTouchListener(this);
        holder = sv_main.getHolder();
        holder.addCallback(this);
        holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);


    }

    private void initCamera() {
        parameters = camera.getParameters();
        parameters.setFlashMode("off");
        parameters.setWhiteBalance(Camera.Parameters.WHITE_BALANCE_AUTO);
        parameters.setSceneMode(Camera.Parameters.SCENE_MODE_AUTO);
        parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_AUTO);
        parameters.setPreviewFormat(ImageFormat.NV21);

        parameters.setPictureSize(camWidth, camHeight);
        parameters.setPreviewSize(camWidth, camHeight);
        camera.setParameters(parameters);
        setOrientation();

        byte[] buf = new byte[camWidth * camHeight * 3 / 2];
        camera.addCallbackBuffer(buf);
        camera.setPreviewCallback(this);
    }

    private void setOrientation() {
        if (this.getResources().getConfiguration().orientation != Configuration.ORIENTATION_LANDSCAPE) {
            parameters.set("orientation", "portrait"); //
            parameters.set("rotation", 90); // 镜头角度转90度（默认摄像头是横拍）
            camera.setDisplayOrientation(90); // 在2.2以上可以使用
        } else {// 如果是横屏
            parameters.set("orientation", "landscape"); //
            camera.setDisplayOrientation(0); // 在2.2以上可以使用
        }
    }

    @Override
    protected void onDestroy() {
        releaseCamera();
        super.onDestroy();
    }

    private PowerManager.WakeLock wakeLock;

    @SuppressLint("InvalidWakeLockTag")
    @Override
    protected void onResume() {
        super.onResume();
        if (wakeLock == null) {
            PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
            wakeLock = pm.newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK, "CameraMatting");
            wakeLock.acquire();
        }
    }

    private void releaseCamera() {
        if (camera != null) {
            this.camera.setPreviewCallback(null);
            this.camera.stopPreview();
            this.camera.release();
            this.camera = null;
        }
    }

    private int frameCount = 0;
    byte[] dstRgbaBytes = null;

    TestNativeRender2 nativeRender;
    private long startTimeMs = 0;


    // 绿色抠图阈值设置 测试
    public  void  testGreenThreshold(TestNativeRender2 nativeRender){
        // 绿色抠图阈值设置
        nativeRender.setGreenMinThreshold(0.1f);
        nativeRender.getGreenMinThreshold();
        nativeRender.setGreenMaxThreshold(1.0f);
        nativeRender.getGreenMaxThreshold();
    }


    public boolean addLayer(String pathFile,String layerType){
        String path = copyAssets(getApplicationContext(), pathFile);
        Bitmap bmp = BitmapFactory.decodeFile(path);
        ByteBuffer byteBuffer = ByteBuffer.allocate(bmp.getWidth() * bmp.getHeight() * 4);
        bmp.copyPixelsToBuffer(byteBuffer);
        // 增加一个Nv21 图层
        switch (layerType){
            case "nv21":
                nativeRender.testAddLayerWithNv21(bmp.getWidth(),bmp.getHeight(),0,byteBuffer.array());
                nativeRender.pushBackGroundWithNv21(bmp.getWidth(),bmp.getHeight(),90,byteBuffer.array());
                return true;
            case "rgba":
                nativeRender.testAddLayer(bmp.getWidth(),bmp.getHeight(),byteBuffer.array());
                nativeRender.pushBackGroundRGBA(bmp.getWidth(),bmp.getHeight(),byteBuffer.array()); // 背景层输入 ,使用RGBA格式
                return true;
            default:
                return false;
        }
    }

    public boolean removeLayer(String LayerType){
        switch (LayerType){
            case "matting":
                return nativeRender.testRemoveMattingLayer();  //删除matting 类型的图层
            case "background":
                return nativeRender.testRemoveBackGroundLayer(); //删除背景图层
            default:
                return false;
        }
    }

    public boolean getLayer(String layerType){
        switch (layerType){
            case "matting":
                return nativeRender.testGetMattingLayer();  //获取matting 类型的图层
            case "background":
                return nativeRender.testGetBackGroundLayer(); //获取背景图层
            case "all":
                return nativeRender.testGetAllLayer(); //获取所有图层
            default:
                return false;
        }
    }


    @Override
    public void onPreviewFrame(byte[] data, Camera camera) {

        if (dstRgbaBytes == null) {
            //设置分辨率
            dstRgbaBytes = new byte[camWidth * camHeight * 4];
        }


        if (nativeRender == null) {
            nativeRender = new TestNativeRender2();

            String path1 = copyAssets(getApplicationContext(), "gm10824Model.model");
            String path2 = copyAssets(getApplicationContext(), "gm2630Model.model");
            String path3 = copyAssets(getApplicationContext(), "glesgm3.so");

            nativeRender.initRender(path1, path2, path3,  camHeight,camWidth);

            nativeRender.setMattingLevel(TestNativeRender2.GREEN_MATTING_LEVEL_DEFAULT);
            nativeRender.setGreenMattingType(TestNativeRender2.GREEN_MATTING);


            // 增加一个Nv21 图层 ,并设置背景层为Nv21类型
            addLayer("20459084.jpg","nv21");

            // 增加一个图层 RGBA 图层 ,并设置背景层为RGBA类型
            addLayer("shoot_bg_default1.jpg","rgba");

            //
            String path = copyAssets(getApplicationContext(), "shoot_bg_default1.jpg");
            Bitmap bmp = BitmapFactory.decodeFile(path);
            ByteBuffer byteBuffer = ByteBuffer.allocate(bmp.getWidth() * bmp.getHeight() * 4);
            bmp.copyPixelsToBuffer(byteBuffer);
            //输入流;
            nativeRender.pushBackGroundRGBA(bmp.getWidth(),bmp.getHeight(),byteBuffer.array());
        }

        nativeRender.mattingOneFrameWithNv21(camWidth,camHeight,90,data,dstRgbaBytes);


        System.out.println("获取图层MattingLayer -->"+getLayer("matting")); // 获取matting 类型的图层

       // System.out.println("删除background图层--->"+removeLayer("background")); // 不能删除MattingLayer 图层，否则会奔溃

        System.out.println("获取图层BackGround--->"+getLayer("background")); // 获取背景图层

        System.out.println("获取所有图层--->"+getLayer("all"));

        if (bitmap == null) {
            bitmap = Bitmap.createBitmap(camHeight,camWidth, Bitmap.Config.ARGB_8888);
        }

        bitmap.copyPixelsFromBuffer(ByteBuffer.wrap(dstRgbaBytes));


        imageView.setImageBitmap(bitmap);

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                frameCount++;
                if (startTimeMs == 0) {
                    startTimeMs = System.currentTimeMillis();
                } else if (nativeRender != null) {
                    long timeMs = System.currentTimeMillis() - startTimeMs;
                    float fps = (float) frameCount * 1000 / (float) timeMs;
                    tvRunTime.setText("分辨率:" + camWidth+"x"+camHeight+ "\n"
                            + " GL耗时(ms):" + nativeRender.getGLDrawOneFrameTimeMS() + "\n"
                            + " 一帧耗时(ms):" + TestNativeRenderAPI2.getMattingOneFrameOnRGBATimeMS() + "\n"
                            + " 运行时间" + timeParse(timeMs) + " 分");
                }
            }
        });


    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        camera = Camera.open();
        initCamera();
    }

    /**
     * 输入的是毫秒
     *
     * @param durationMs
     * @return 返回的是分钟
     */
    public static String timeParse(long durationMs) {
        String time = "";
        long minute = durationMs / 60000;
        long seconds = durationMs % 60000;
        long second = Math.round((float) seconds / 1000);
        if (minute < 10) {
            time += "0";
        }
        time += minute + ":";
        if (second < 10) {
            time += "0";
        }
        time += second;
        return time;
    }


    public static String copyAssets(Context context, String assetsName) {

        String filePath = context.getFilesDir() .getAbsolutePath()+ "/" + assetsName;
        try {
            if (!(new File(filePath)).exists()) { // 如果不存在.
                InputStream is = context.getAssets().open(assetsName);
                FileOutputStream fos = new FileOutputStream(filePath);
                byte[] buffer = new byte[7168];
                int count = 0;
                while ((count = is.read(buffer)) > 0) {
                    fos.write(buffer, 0, count);
                }
                fos.close();
                is.close();
            }
            return filePath;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        try {
            camera.setPreviewDisplay(holder);
            camera.startPreview();
            System.out.println("startPreview");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

        if (nativeRender != null) {
            nativeRender.releaseOnRGBA();
            nativeRender = null;
        }
    }



    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {//按下时自动对焦
            camera.autoFocus(null);
        }
        return true;
    }
}
