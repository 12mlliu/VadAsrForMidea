package com.midea.VadAsr.utils;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.annotation.SuppressLint;
import android.os.Environment;
import android.util.Log;

public class LogUtils {
	public static boolean isSaveDebugInfo = false;// 是否保存调试日志
	public static boolean isSaveCrashInfo = false;// 是否保存报错日志
	public static final String CACHE_DIR_NAME = "waterHeater";

	private LogUtils() {
		throw new UnsupportedOperationException("cannot be instantiated");
	}

	public static boolean isDebug = true;// 是否需要打印bug，可以在application的onCreate函数里面初始化
	public static String APP_TAG = "mideaAsr";

	// 下面四个是默认tag的函数
	public static void i(final String msg) {
		if (isDebug)
			Log.i(APP_TAG, msg);

		if (isSaveDebugInfo) {
			new Thread() {
				public void run() {
					write(time() + APP_TAG + " --> " + msg + "\n");
				};
			}.start();
		}
	}

	public static void d(final String msg) {
		if (isDebug)
			Log.d(APP_TAG, msg);

		if (isSaveDebugInfo) {
			new Thread() {
				public void run() {
					write(time() + APP_TAG + " --> " + msg + "\n");
				};
			}.start();
		}
	}

	public static void e(final String msg) {
		if (isDebug){
			Log.e(APP_TAG, msg);}

		if (isSaveDebugInfo) {
			new Thread() {
				public void run() {
					write(time() + APP_TAG + " --> " + msg + "\n");
				};
			}.start();
		}
	}

	public static void v(final String msg) {
		if (isDebug)
			Log.v(APP_TAG, msg);

		if (isSaveDebugInfo) {
			new Thread() {
				public void run() {
					write(time() + APP_TAG + " --> " + msg + "\n");
				};
			}.start();
		}
	}

	// 下面是传入自定义tag的函数
	public static void i(final String tag, final String msg) {
		if (isDebug)
			Log.i(APP_TAG, msg);

		if (isSaveDebugInfo) {
			new Thread() {
				public void run() {
					write(time() + tag + " --> " + msg + "\n");
				};
			}.start();
		}
	}

	public static void d(final String tag, final String msg) {
		if (isDebug)
			Log.i(APP_TAG, msg);
		if (isSaveDebugInfo) {
			new Thread() {
				public void run() {
					write(time() + tag + " --> " + msg + "\n");
				};
			}.start();
		}
	}

	public static void e(final String tag, final String msg) {
		if (isDebug)
			Log.i(APP_TAG, msg);
		if (isSaveDebugInfo) {
				new Thread() {
					public void run() {
						write(time() + tag + " --> " + msg + "\n");
					};
				}.start();
			}
	}

	public static void v(final String tag, final String msg) {
		if (isDebug)
			Log.i(APP_TAG, msg);
		if (isSaveDebugInfo) {
			new Thread() {
				public void run() {
					write(time() + tag + " --> " + msg + "\n");
				};
			}.start();
		}
	}

	/**
	 * 标识每条日志产生的时间
	 * 
	 * @return
	 */
	@SuppressLint("SimpleDateFormat")
	private static String time() {
		return "[" + new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date(System.currentTimeMillis())) + "] ";
	}

	/**
	 * 保存到日志文件
	 * 
	 * @param content
	 */
	public static synchronized void write(String content) {
		try {
			String fP = getFile();
			FileWriter writer = new FileWriter(getFile(), true);
			Log.e("fP:", fP);
			writer.write(content);
			writer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 获取日志文件路径
	 * 
	 * @return
	 */
	public static String getFile() {
		File sdDir = null;

		if (Environment.getExternalStorageState().equals(android.os.Environment.MEDIA_MOUNTED))
			sdDir = Environment.getExternalStorageDirectory();
		if (sdDir == null) {
			sdDir = Environment.getExternalStorageDirectory();
		}
//		LogUtils.e("sdDir", "sdDir:" + sdDir + "");
		File cacheDir = new File(sdDir + File.separator + CACHE_DIR_NAME);
		if (!cacheDir.exists())
			cacheDir.mkdir();
		File filePath = new File(cacheDir + File.separator + date() + ".txt");
		return filePath.toString();
	}

	/**
	 * 以年月日作为日志文件名称
	 * 
	 * @return
	 */
	@SuppressLint("SimpleDateFormat")
	private static String date() {
		return new SimpleDateFormat("yyyy-MM-dd").format(new Date(System.currentTimeMillis()));
	}
}
