package com.lansong.sdk;

import android.app.Application;
import android.util.Log;


import com.lansosdk.network.LSOHardWareAuth;



public class LSOApplication extends Application {

    private static LSOApplication mInstance;

    public static LSOApplication getsInstance() {
        return mInstance;
    }

    @Override
    public void onCreate() {
        super.onCreate();

        mInstance = this;


        initLanSongSDK_hardWare();

    }




    /**
     * 硬件客户使用
     */
    private void initLanSongSDK_hardWare(){


        if (LSOHardWareAuth.USER_ID == null) {
            Log.e("LanSongSDK", "LSOApplication initLanSongSDK_hardWare 当前使用临时授权演示,有时间段限制,请注意...(请尽快设置userId)");
            LSOHardWareAuth.setTempLicense();
        } else {
            LSOHardWareAuth.activeDevice(getApplicationContext(), new LSOHardWareAuth.OnActiveResultListener() {
                @Override
                public void onActiveSuccess() {

                }
                @Override
                public void onActiveError(String info) {

                }
            });
        }
    }

}
