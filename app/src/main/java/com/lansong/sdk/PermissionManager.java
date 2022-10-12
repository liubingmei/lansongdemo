package com.lansong.sdk;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;

/**
 * 权限管理
 */

public class PermissionManager {

    /* 权限请求码 */
    public static final int REQ_PERMISSION_CAMERA = 2; // 拍照
    public static final int REQ_PERMISSION_ALBUM = 3; // 获取相册
    public static final int REQ_PERMISSION_AUDIO = 4; // 音频设置
    public static final int REQ_PERMISSION_RECORD = 5; // 录音
    public static final int REQ_PERMISSION_CALL = 6; // 拨打电话

    /**
     * 判断是否已获取权限
     * @param grantResults
     * @return
     */
    public static boolean check(int[] grantResults) {
        for (int result : grantResults) {
            if (result != PackageManager.PERMISSION_GRANTED) {
                return false;
            }
        }
        return true;
    }


    /**
     * 跳转到权限设置界面
     * @param context
     */
    public static void startDetailSetting(Context context){
        Intent intent = new Intent();
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.setAction("android.settings.APPLICATION_DETAILS_SETTINGS");
        intent.setData(Uri.fromParts("package", context.getPackageName(), null));
        context.startActivity(intent);
    }

    /**
     * 读取手机状态权限
     *
     * @param activity
     * @param requestCode
     * @param isNeedRequest 是否需要请求，否则只判断是否已获取
     * @return
     */
    public static boolean checkReadPhoneState(Activity activity, int requestCode, boolean isNeedRequest) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (activity.checkSelfPermission(Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {
                if(isNeedRequest) {
                    activity.requestPermissions(new String[]{Manifest.permission.READ_PHONE_STATE}, requestCode);
                }
                return false;
            }
        }
        return true;
    }

    /**
     * 拍照权限
     *
     * @param activity
     * @param requestCode
     * @return
     */
    public static boolean checkCamera(Activity activity, int requestCode) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (activity.checkSelfPermission(Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED || activity.checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                activity.requestPermissions(new String[]{Manifest.permission.CAMERA, Manifest.permission.WRITE_EXTERNAL_STORAGE}, requestCode == 0 ? REQ_PERMISSION_CAMERA : requestCode);
                return false;
            }
        }
        return true;
    }

    /**
     * SD卡读写权限（获取相册时必须检测此权限）
     *
     * @param activity
     * @param requestCode
     */
    public static boolean checkStorage(Activity activity, int requestCode) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (activity.checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED || activity.checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                activity.requestPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE}, requestCode == 0 ? REQ_PERMISSION_ALBUM : requestCode);
                return false;
            }
        }
        return true;
    }

    /**
     * 音频设置权限
     *
     * @param activity
     * @param requestCode
     * @return
     */
    public static boolean checkAudioSetting(Activity activity, int requestCode) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (activity.checkSelfPermission(Manifest.permission.MODIFY_AUDIO_SETTINGS) != PackageManager.PERMISSION_GRANTED) {
                activity.requestPermissions(new String[]{Manifest.permission.MODIFY_AUDIO_SETTINGS}, requestCode == 0 ? REQ_PERMISSION_AUDIO : requestCode);
                return false;
            }
        }
        return true;
    }


    /**
     * 录音权限
     *
     * @param activity
     * @param requestCode
     * @return
     */
    public static boolean checkRecord(Activity activity, int requestCode) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (activity.checkSelfPermission(Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED || activity.checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                activity.requestPermissions(new String[]{Manifest.permission.RECORD_AUDIO, Manifest.permission.WRITE_EXTERNAL_STORAGE}, requestCode == 0 ? REQ_PERMISSION_RECORD : requestCode);
                return false;
            }
        }
        return true;
    }

    /**
     * 通话权限
     *
     * @param activity
     * @param requestCode
     * @return
     */
    public static boolean checkCall(Activity activity, int requestCode) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (activity.checkSelfPermission(Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
                activity.requestPermissions(new String[]{Manifest.permission.CALL_PHONE}, requestCode == 0 ? REQ_PERMISSION_CALL : requestCode);
                return false;
            }
        }
        return true;
    }

}
