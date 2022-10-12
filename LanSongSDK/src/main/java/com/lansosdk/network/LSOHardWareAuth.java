package com.lansosdk.network;

//务必放到:com.lansosdk.network; 下面
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;

public class LSOHardWareAuth {
    static {
        System.loadLibrary("LSOSurfaceKey");
    }

      public static String USER_ID=null;

    public static OnRegisterResultListener onRegisterResultListener =null;
    public static OnActiveResultListener onActiveResultListener =null;


    /**
     * 注册设备mac地址;
     * @param context
     * @param listener
     */
    public static void registerDevice(Context context, OnRegisterResultListener listener){
        if(!isNetworkAvailable(context)){
            listener.onRegisterError("network not available...");
        }else{
            onRegisterResultListener =listener;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    registerDevice(null);
                }
            }).start();
        }
    }

    /**
     * 注册指定的mac地址;
     * @param context
     * @param macAddress
     * @param listener
     */
    public static void registerDevice(Context context, final String macAddress, OnRegisterResultListener listener){
        if(!isNetworkAvailable(context)){
            listener.onRegisterError("network not available...");
        }else{
            onRegisterResultListener =listener;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    registerDevice(macAddress);
                }
            }).start();
        }
    }



    /**
     *
     * @param context
     * @param listener
     */
    public static void activeDevice(final Context context, OnActiveResultListener listener){
        if(!isNetworkAvailable(context)){
            listener.onActiveError("network not available...");
        }else{
            onActiveResultListener =listener;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    activationDevice(context);
                }
            }).start();
        }
    }


    public static boolean isNetworkAvailable(Context context) {
        ConnectivityManager connectivity = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);

        if (connectivity != null) {
            NetworkInfo info = connectivity.getActiveNetworkInfo();

            if (info != null && info.isConnected()) {
                if (info.getState() == NetworkInfo.State.CONNECTED) {
                    return true;
                }
            }
        }
        return false;
    }


    private static void registerDevice(String hexString) {

        String hexRegister =null;
        if(hexString!=null){
            hexRegister=   LSOHardWareAuth.getRDataWithMacAddress(USER_ID,hexString);
        }else{
            hexRegister=   LSOHardWareAuth.getRData(USER_ID);
        }

        String sendRegisterData = "data=" + hexRegister;
        String rcvRegisterResult = postHttpData("http://8.142.172.89/appApi/product/encodeAesInfo", sendRegisterData, "", false);
        if(rcvRegisterResult!=null){
            int codeIndex = rcvRegisterResult.indexOf("code");
            try {
                String string2 = rcvRegisterResult.substring(codeIndex + 6, codeIndex + 9);
                int code = Integer.parseInt(string2);
                if (code == 200) {  //解密成功;
                    codeIndex = rcvRegisterResult.indexOf("data");
                    String hexResult = rcvRegisterResult.substring(codeIndex + 7, rcvRegisterResult.length() - 2);
                    if (hexResult != null && hexResult.length() > 15 && setRData(hexResult)) {
                        onRegisterResultListener.onRegisterSuccess();
                    }else{
                        onRegisterResultListener.onRegisterError(getErrorInfo());
                    }
                } else {
                    Log.e("LanSongSDK", "注册失败,返回的code 是:" + code);
                    onRegisterResultListener.onRegisterError("register error. code is:"+ code + " maybe:"+ getErrorInfo());

                }
            } catch (Exception e) {
                e.printStackTrace();
                Log.e("LanSongSDK", "Main0TestDemoActivity test 解析错误, 抛出异常. ");
                onRegisterResultListener.onRegisterError("register error. Exception print");
            }
        }else{
            onRegisterResultListener.onRegisterError("request register dec");
        }
    }


    private static void activationDevice(Context context) {

        String hexRegister = LSOHardWareAuth.getAData(USER_ID);
        String sendData = "data=" + hexRegister;

        String rcvRegisterResult = postHttpData("http://8.142.172.89/appApi/product/encodeAesInfo", sendData, "", false);

        if(rcvRegisterResult!=null){
            // 解析字符串;   {"code":200,"msg":"成功",
            int codeIndex = rcvRegisterResult.indexOf("code");
            try {
                String string2 = rcvRegisterResult.substring(codeIndex + 6, codeIndex + 9);
                int code = Integer.parseInt(string2);
                if (code == 200) {  //解密成功;
                    codeIndex = rcvRegisterResult.indexOf("data");
                    String hexResult = rcvRegisterResult.substring(codeIndex + 7, rcvRegisterResult.length() - 2);

                    checkActiveString(context,hexResult);
                    return ;
                }
            } catch (Exception e) {
                Log.e("LanSongSDK", "Main0TestDemoActivity test 解析错误, 抛出异常.");
            }
        }
        checkActiveString(context,null);
    }


    /**
     * 特定客户使用, 请不要使用;
     * @param context
     * @param macAddress
     * @return
     */
    public static String getActiveInfoWithMacAddress(Context context, String macAddress) {

        String hexRegister = LSOHardWareAuth.getADataWithMacAddress(USER_ID,macAddress);
        String sendData = "data=" + hexRegister;

        String rcvRegisterResult = postHttpData("http://8.142.172.89/appApi/product/encodeAesInfo", sendData, "", false);

        if(rcvRegisterResult!=null){
            // 解析字符串;   {"code":200,"msg":"成功",
            int codeIndex = rcvRegisterResult.indexOf("code");
            try {
                String string2 = rcvRegisterResult.substring(codeIndex + 6, codeIndex + 9);
                int code = Integer.parseInt(string2);
                if (code == 200) {  //解密成功;
                    codeIndex = rcvRegisterResult.indexOf("data");
                    String hexResult = rcvRegisterResult.substring(codeIndex + 7, rcvRegisterResult.length() - 2);

                    return hexResult;
                }
            } catch (Exception e) {
                Log.e("LanSongSDK", "Main0TestDemoActivity test 解析错误, 抛出异常.");
            }
        }
        return null;
    }





    private static final String HEX_STRING_FILE = "visionHex264.key";

    public static void checkActiveString(Context context, String hexString){

        String hex2=hexString;
        if(hex2==null){
            String path=context.getFilesDir().getAbsolutePath()+ "/"+ HEX_STRING_FILE;
            File file=new File(path);
            if(file.exists()){
                try {
                    FileInputStream stream=new FileInputStream(file);
                    BufferedReader reader = new BufferedReader(new InputStreamReader(stream));

                    String str=reader.readLine();
                    Log.e("LanSongSDK", "LSOHardWareAuth activeErrorEntry " + str);
                   hex2=str;
                } catch (Exception e) {
                    e.printStackTrace();
                    Log.e("LanSongSDK", "LSOHardWareAuth checkActiveString ERROR.");
                }
            }
        }
        if(hex2!=null){
            saveHexString(context,hex2);
            if(setAData(hexString)){
                if(onActiveResultListener!=null){
                    onActiveResultListener.onActiveSuccess();
                }
            }else if(onActiveResultListener!=null){
                onActiveResultListener.onActiveError(getErrorInfo());
            }
        }else if(onActiveResultListener!=null){
            onActiveResultListener.onActiveError(getErrorInfo());
        }
    }

    private static void saveHexString(Context context,String hexString){

        String path=context.getFilesDir().getAbsolutePath()+ "/"+ HEX_STRING_FILE;
        File file=new File(path);
        if(file.exists()){
            file.delete();
        }
        FileOutputStream      fos = null;
        try {
            fos = new FileOutputStream(file);
            BufferedOutputStream     bos = new BufferedOutputStream(fos);
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(bos));
            writer.write(hexString);
            writer.close();
            fos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String postHttpData(String arl, String s, String cookie, boolean isJson) {

        int count = 0;
        StringBuilder result = new StringBuilder();
        while (true) {
            int ret = -1;
            OutputStreamWriter out = null;
            URL url;
            BufferedReader in = null;
            try {
                url = new URL(arl);
// 建立http连接
                HttpURLConnection conn = (HttpURLConnection) url.openConnection();
// 设置允许输出
                conn.setDoOutput(true);
                conn.setDoInput(true);
                conn.setUseCaches(false);
                conn.setConnectTimeout(15000);
                conn.setReadTimeout(15000);
                conn.setInstanceFollowRedirects(true);
                if (cookie != "")
                    conn.setRequestProperty("Cookie", cookie);
                if (isJson)
                    conn.setRequestProperty("Content-type", "application/json");
                else
                    conn.setRequestProperty("Content-type", " application/x-www-form-urlencoded");
                conn.setRequestMethod("POST"); // 设置请求方式
                conn.connect();
                out = new OutputStreamWriter(conn.getOutputStream(), "UTF-8"); // utf-8编码
// 写入请求的字符串
                out.append(s);
                out.flush();
                out.close();
                if (conn.getResponseCode() == 200) {
                    in = new BufferedReader(new InputStreamReader(conn.getInputStream(), "utf-8"));
                    String line;
                    while ((line = in.readLine()) != null) {
                        result.append(line);
                    }
                }
                conn.disconnect();
                ret = 1;
            } catch (Exception e) {
                count++;
                e.printStackTrace();
                return null;
            } finally {
                try {

                    if (out != null) {
                        out.close();
                    }
                    if (in != null) {
                        in.close();
                    }

                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
            if (ret > 0 || count >= 3) break;
        }
        return result.toString();
    }


    /**
     * 设置临时license;
     */
    public static native void setTempLicense();

   //-----------
    public static native String getRData(String userId);




    public static native String getRDataWithMacAddress(String userId,String macAddress);

    public static native String getAData(String userId);

    public static native String getADataWithMacAddress(String userId, String macAddress);

    public static native boolean setRData(String hexString);

    public static native boolean setAData(String hexString);



    private static native String getErrorInfo();


    public static interface OnActiveResultListener {

        void onActiveSuccess();

        void onActiveError(String info);

    }

    public static interface OnRegisterResultListener {

        void onRegisterSuccess();

        void onRegisterError(String info);

    }
}
