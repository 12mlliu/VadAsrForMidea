package com.midea.VadAsr.utils;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;

public class RecognizerUtils implements RecognitionListener {

	public RecognizerTask rec = null;
	private ASrListener aSrListener;
	private Context mContext;

	public RecognizerUtils(Context mContext) {
		rec = new RecognizerTask(mContext);
		rec.setRecognitionListener(this);
	}

	public void setLoad() {
		rec.isLoad = false;
	}

	@Override
	public void onPartialResults(Bundle b) {
		LogUtils.d("onPartialResults:" + b);
	}

	@Override
	public void onResults(final Object b) {
		LogUtils.i("RecognizerUtils onResults:" + "");
		if (b == null) {
			new Handler(Looper.getMainLooper()).post(new Runnable() {
				@Override
				public void run() {
					aSrListener.onResults(null);
				}
			});
			return;
		} else {
			new Handler(Looper.getMainLooper()).post(new Runnable() {
				@Override
				public void run() {
					aSrListener.onResults(b.toString());
				}
			});
		}

	}

	@Override
	public void onError(final String err) {
		if (err == null) {
			return;
		}
		new Handler(Looper.getMainLooper()).post(new Runnable() {
			@Override
			public void run() {
				aSrListener.onError(err);
			}
		});
	}

	@Override
	public void onVolume(final int volume) {
		new Handler(Looper.getMainLooper()).post(new Runnable() {
			@Override
			public void run() {
				// aSrListener.onVolume(volume);
			}
		});
	}

	@Override
	public void onAsrStart() {
		new Handler(Looper.getMainLooper()).post(new Runnable() {
			@Override
			public void run() {
				aSrListener.onAsrStart();
			}
		});
	}

	public void onAsrStop() {
		try {
			rec.rStop();
			rec = null;
		} catch (Exception e) {
		}
	}

	public void startRec() {
		if (rec != null) {
			rec.rStop();
		}
		rec = new RecognizerTask(mContext);
		rec.setRecognitionListener(this);
		rec.start();
	}

	public ASrListener getaSrListener() {
		return aSrListener;
	}

	public void setaSrListener(ASrListener aSrListener) {
		this.aSrListener = aSrListener;
	}

	public interface ASrListener {
		void onAsrStart();

		void onResults(String results);

		// void onVolume(int volume);

		void onError(String str);
	}

}
