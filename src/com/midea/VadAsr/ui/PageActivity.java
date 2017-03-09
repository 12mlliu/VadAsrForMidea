package com.midea.VadAsr.ui;

import java.io.File;
import java.io.FileOutputStream;
import java.io.RandomAccessFile;

import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageButton;
import android.widget.TextView;

import com.midea.VadAsr.ui.R;
import com.midea.VadAsr.utils.Fileutils;
import com.midea.VadAsr.utils.LogUtils;
import com.midea.VadAsr.utils.RecognizerUtils;
import com.midea.VadAsr.utils.RecognizerUtils.ASrListener;

public class PageActivity extends FragmentActivity implements ASrListener {

	TextView asr_txt, sdk_txt, asrw_txt, asrwe_txt, asrt_txt;
	private boolean isBegin = false;
	ImageButton asr_btn;
	public RecognizerUtils recognizerUtils;
	boolean isStop = false;
	private String results = "";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);// 隐藏标题
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);// 设置全屏
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		setContentView(R.layout.activity_page);
		asr_txt = (TextView) findViewById(R.id.asr_txt);
		sdk_txt = (TextView) findViewById(R.id.sdk_txt);
		asrt_txt = (TextView) findViewById(R.id.asrt_txt);
		asrw_txt = (TextView) findViewById(R.id.asrw_txt);
		asrwe_txt = (TextView) findViewById(R.id.asrwe_txt);
		asr_btn = (ImageButton) findViewById(R.id.asr_btn);
		asr_btn.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				asr_txt.setText("你想说什么");
				if (isBegin) {
					isBegin = false;
					asr_btn.setBackgroundResource(R.drawable.begin_btn);
					recognizerUtils.onAsrStop();
					Fileutils.saveTxtForStr(results);
					results = "";
					isStop = true;
				} else {
					str = "";
					asr_txt.setText("你想说什么");
					recognizerUtils.startRec();
					isBegin = true;
					isStop = false;
					asr_btn.setBackgroundResource(R.drawable.end_btn);
				}
			}
		});

		findViewById(R.id.sdk_txt).setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
			}
		});
		findViewById(R.id.vadbtn).setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				// recognizerUtils.startRec();
			}
		});
	}

	String str = "";

	// @Override
	// public void onVolume(int volume) {
	// str = str + "\nvolume1:" + volume + "";
	// asrwe_txt.setText("volume1:" + volume + "");
	// }

	public boolean writeTxtFile(String content, File fileName) throws Exception {
		RandomAccessFile mm = null;
		boolean flag = false;
		FileOutputStream o = null;
		try {
			o = new FileOutputStream(fileName);
			o.write(content.getBytes("GBK"));
			o.close();
			flag = true;
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		} finally {
			if (mm != null) {
				mm.close();
			}
		}
		return flag;
	}

	public void getRecognize(int code) {
		recognizerUtils = new RecognizerUtils(this);
		recognizerUtils.setaSrListener(this);
	}

	@Override
	protected void onResume() {
		super.onResume();
		sdk_txt.setText("美的语音识别SDK");
		LogUtils.i("main onResume()");
		recognizerUtils = new RecognizerUtils(this);
		recognizerUtils.setaSrListener(this);
		// 接口启动
		// recognizerUtils.startRec();
	}

	@Override
	protected void onStart() {
		super.onStart();
		LogUtils.i("main onStart()");
	}

	@Override
	protected void onStop() {
		super.onStop();
	}

	@Override
	protected void onPause() {
		super.onPause();
		recognizerUtils.onAsrStop();
	}

	@Override
	public void onResults(String results) {
		if (isStop)
			return;
		//Fileutils.saveTxtForStr(results);
		this.results += Fileutils.getSysDate("yyyyMMddHHmmss") + " "+results + "\n";
		LogUtils.e("INFO: Detected end point  onResults!:" + results);
		// asr_btn.setBackgroundResource(R.drawable.begin_btn);
		asrw_txt.setText(asrw_txt.getText() + "\n" + "start");
		LogUtils.d("MainActivity onResults:" + results);
		// isBegin = false;
		asr_txt.setText("识别内容：" + results);
		// 接口启动
		recognizerUtils.startRec();
	}

	@Override
	public void onError(String err) {
		recognizerUtils.onAsrStop();
	}

	@Override
	public void onAsrStart() {
		asrw_txt.setText("start");
	}
}
