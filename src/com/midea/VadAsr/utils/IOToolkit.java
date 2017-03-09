package com.midea.VadAsr.utils;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.Closeable;
import java.io.DataInputStream;
import java.io.EOFException;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import android.annotation.SuppressLint;
import android.content.Context;

import com.midea.VadAsr.utils.RecognizerUtils.ASrListener;

/**
 * <Description>
 * 
 * @author linhs
 * @date Mar 21, 2016
 * @version 1.0.0
 */
@SuppressLint("SdCardPath")
public class IOToolkit {

	public static boolean isInit = false;
	public static String MODEL_PATH = "/mnt/sdcard/edu.cmu.pocketsphinx/hmm/zh_CN/";
	static {
		System.loadLibrary("pocketsphinx_jni");
	}

	public static void setAsrWask(Context context, int resource, ASrListener aSrListener) {
		File home = new File("/mnt/sdcard/edu.cmu.pocketsphinx/hmm/zh_CN/");
		if (home.exists() == false) {
			LogUtils.d("----- Mkdir home dictionary ----");
			home.mkdirs();
			try {
				unzip(context, resource, home);
				isInit = true;
			} catch (IOException e) {
				LogUtils.e("-----midea asr initialization failed ----");
				e.printStackTrace();
			}
		}
		RecognizerUtils recognizerUtils = new RecognizerUtils(context);
		recognizerUtils.setLoad();
		recognizerUtils.setaSrListener(aSrListener);
		recognizerUtils.startRec();
	}

	public static void ReInitialization(Context context, int resource, ASrListener aSrListener) {
		isInit = false;
		DeleteFolder("/mnt/sdcard/edu.cmu.pocketsphinx/");
		setAsrWask(context, resource, aSrListener);
	}

	/**
	 * 根据路径删除指定的目录或文件，无论存在与否
	 * 
	 * @param filePath
	 *            要删除的目录或文件
	 * @return 删除成功返回 true，否则返回 false。
	 */
	public static boolean DeleteFolder(String filePath) {
		File file = new File(filePath);
		if (!file.exists()) {
			return false;
		} else {
			if (file.isFile()) {
				// 为文件时调用删除文件方法
				return deleteFile(filePath);
			} else {
				// 为目录时调用删除目录方法
				return deleteDirectory(filePath);
			}
		}
	}

	/**
	 * 删除文件夹以及目录下的文件
	 * 
	 * @param filePath
	 *            被删除目录的文件路径
	 * @return 目录删除成功返回true，否则返回false
	 */
	public static boolean deleteDirectory(String filePath) {
		boolean flag = false;
		// 如果filePath不以文件分隔符结尾，自动添加文件分隔符
		if (!filePath.endsWith(File.separator)) {
			filePath = filePath + File.separator;
		}
		File dirFile = new File(filePath);
		if (!dirFile.exists() || !dirFile.isDirectory()) {
			return false;
		}
		flag = true;
		File[] files = dirFile.listFiles();
		// 遍历删除文件夹下的所有文件(包括子目录)
		for (int i = 0; i < files.length; i++) {
			if (files[i].isFile()) {
				// 删除子文件
				flag = deleteFile(files[i].getAbsolutePath());
				if (!flag)
					break;
			} else {
				// 删除子目录
				flag = deleteDirectory(files[i].getAbsolutePath());
				if (!flag)
					break;
			}
		}
		if (!flag)
			return false;
		// 删除当前空目录
		return dirFile.delete();
	}

	/**
	 * 删除单个文件
	 * 
	 * @param filePath
	 *            被删除文件的文件名
	 * @return 文件删除成功返回true，否则返回false
	 */
	public static boolean deleteFile(String filePath) {
		File file = new File(filePath);
		if (file.isFile() && file.exists()) {
			return file.delete();
		}
		return false;
	}

	public static short readCShort(InputStream in) throws IOException {

		int ch2 = in.read();
		int ch1 = in.read();
		if ((ch1 | ch2) < 0)
			throw new EOFException();
		return (short) ((ch1 << 8) + (ch2 << 0));
	}

	public static short readShort(InputStream in) throws IOException {

		int ch1 = in.read();
		int ch2 = in.read();
		if ((ch1 | ch2) < 0)
			throw new EOFException();
		return (short) ((ch1 << 8) + (ch2 << 0));
	}

	public static final void writeCShort(OutputStream out, int v) throws IOException {

		out.write((v >>> 0) & 0xFF);
		out.write((v >>> 8) & 0xFF);
	}

	public static String readString(DataInputStream in, int length) throws IOException {

		byte[] buffer = new byte[length];
		length = in.read(buffer);
		if (length == -1) {
			return null;
		}
		return new String(buffer);
	}

	public static short[] readShortArray(DataInputStream in, int length) throws IOException {

		short[] array = new short[length];
		for (int i = 0; i < length; i++) {
			array[i] = in.readShort();
		}
		return array;
	}

	public static String[] readLineArray(BufferedReader in, boolean trim) throws IOException {

		ArrayList<String> array = new ArrayList<String>();
		String line;
		while ((line = in.readLine()) != null) {
			if (trim) {
				line = line.trim();
			}
			array.add(line);
		}
		return array.toArray(new String[0]);
	}

	public static String[] readLineArray(InputStream in, boolean trim) throws IOException {

		return readLineArray(new BufferedReader(new InputStreamReader(in)), trim);
	}

	public static String[] readLineArray(File file, boolean trim) throws IOException {

		BufferedReader in = new BufferedReader(new FileReader(file));
		String[] array = readLineArray(in, trim);
		in.close();
		return array;
	}

	public static void unzip(ZipFile zip, File path) throws IOException {

		Enumeration<? extends ZipEntry> emu = zip.entries();
		int size = 2048;
		while (emu.hasMoreElements()) {
			ZipEntry entry = emu.nextElement();
			if (entry.isDirectory()) {
				new File(path, entry.getName()).mkdirs();
				continue;
			}
			BufferedInputStream bis = new BufferedInputStream(zip.getInputStream(entry));
			File file = new File(path, entry.getName());
			File parent = file.getParentFile();
			if (parent != null && (!parent.exists())) {
				parent.mkdirs();
			}
			FileOutputStream fos = new FileOutputStream(file);
			BufferedOutputStream bos = new BufferedOutputStream(fos, size);

			int count;
			byte data[] = new byte[size];
			while ((count = bis.read(data)) != -1) {
				bos.write(data, 0, count);
			}
			bos.flush();
			bos.close();
			bis.close();
		}
		zip.close();
	}

	public static void copy(InputStream in, OutputStream out) throws IOException {

		byte buffer[] = new byte[1024];
		int length;
		while ((length = in.read(buffer)) != -1) {
			out.write(buffer, 0, length);
		}
	}

	public static boolean close(Closeable stream) {

		try {
			stream.close();
			return true;
		} catch (IOException e) {
			return false;
		}
	}

	public static void copy(Context context, int resource, File file) throws IOException {

		InputStream in = context.getResources().openRawResource(resource);
		OutputStream out = new FileOutputStream(file);
		try {
			IOToolkit.copy(in, out);
		} catch (IOException e) {
			IOToolkit.close(in);
			IOToolkit.close(out);
			throw e;
		}
		IOToolkit.close(in);
		IOToolkit.close(out);
	}

	public static void unzip(Context context, int resource, File file) throws IOException {

		if (file.exists()) {
			if (file.isDirectory() == false) {
				file.delete();
				file.mkdirs();
			}
		} else {
			file.mkdirs();
		}
		File zip = new File(file, String.format("%d.zip", resource));
		try {
			if (zip.exists() == false) {
				IOToolkit.copy(context, resource, zip);
			}
			IOToolkit.unzip(new ZipFile(zip), file);
		} catch (IOException e) {
			LogUtils.e("-----midea asr initialization failed ----");
			throw e;
		} finally {
			zip.delete();
		}
	}
}