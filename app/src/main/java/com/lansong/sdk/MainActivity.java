package com.lansong.sdk;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.constraintlayout.widget.ConstraintLayout;

import com.lansong.testNative.TestNativeRenderActivity;


public class MainActivity extends Activity implements View.OnClickListener {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        findViewById(R.id.id_main_setting).setOnClickListener(this);
        View green_matting_v = findViewById(R.id.id_main_green_matting);
        green_matting_v.setOnClickListener(this);
        findViewById(R.id.id_main_ai_matting).setOnClickListener(this);
        findViewById(R.id.id_main_video_edit).setOnClickListener(this);
        findViewById(R.id.id_main_matting_template).setOnClickListener(this);
        findViewById(R.id.id_main_matting_layer).setOnClickListener(this);
        findViewById(R.id.id_main_ai_record).setOnClickListener(this);

        ConstraintLayout.LayoutParams params = (ConstraintLayout.LayoutParams) green_matting_v.getLayoutParams();
        params.topMargin = getResources().getDisplayMetrics().heightPixels * 2 / 5;
        green_matting_v.setLayoutParams(params);


        firstButtonClock();

    }


    private void firstButtonClock(){
        if (PermissionManager.checkStorage(MainActivity.this, 0) &&
                PermissionManager.checkCamera(MainActivity.this, 0)) {
            startActivity(new Intent(MainActivity.this, TestNativeRenderActivity.class));
        }
    }

    @Override
    public void onClick(View v) {

        firstButtonClock();
    }


    @Override
    protected void onResume() {
        super.onResume();
    }

    // 两次点击按钮之间的点击间隔不能少于300毫秒
    private final int MIN_CLICK_DELAY_TIME = 300;
    private long lastClickTime = -1;




}
