package com.midea.VadAsr.utils;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.sql.Date;
import java.text.SimpleDateFormat;

import android.os.Environment;

public class Fileutils {
	
	//public static String filename = "recodFile.txt";

	public static void saveTxtForBuf(short[] buf) {
		// 写文件
		String str = "";
		for (int i = 0; i < buf.length; i++) {
			// String str1 = mArrayList.get(i)[j];
			str += Short.toString(buf[i]);
			str += "\r\n";
		}
		saveTxtForStr(str);
	}
	
	public static String getSysDate(String dataFor){
		Date curDate = new Date(System.currentTimeMillis());
		SimpleDateFormat dfs = new SimpleDateFormat(dataFor);
		return dfs.format(curDate);
	}

	public static void saveTxtForStr(String str) {
		String filename  = getSysDate("yyyyMMddHHmmss")+"log.txt";
		File mFileRes = new File(Environment.getExternalStorageDirectory()
				.getAbsolutePath() + "/midea/files/"+filename);
		writeTxtFile(str, mFileRes);
	}

	public static boolean writeTxtFile(String content, File fileName) {
		RandomAccessFile mm = null;
		boolean flag = false;
		FileOutputStream o = null;
		try {
			o = new FileOutputStream(fileName);
			o.write(content.getBytes("UTF-8"));
			o.close();
			flag = true;
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (mm != null) {
				try {
					mm.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return flag;
	}
	
	public static void saveTxtForWav(short[] buf) {
		// 写文件
		String str = "";
		for (int i = 0; i < buf.length; i++) {
			// String str1 = mArrayList.get(i)[j];
			str += Short.toString(buf[i]);
			str += "\r\n";
		}
		//File mFileRes = new File(Environment.getExternalStorageDirectory()
				//.getAbsolutePath() + "/midea/files/recod.txt");
		//writeTxtFileForWav(str, mFileRes);
		saveTxtForWav(str);
	}
	public static void saveTxtForWav(String str) {
		String filename  = getSysDate("yyyyMMddHHmmss")+"wav.txt";
		File mFileRes = new File(Environment.getExternalStorageDirectory()
				.getAbsolutePath() + "/midea/files/"+filename);
		writeTxtFile(str, mFileRes);
	}
	public static boolean writeTxtFileForWav(String content, File fileName) {
		RandomAccessFile mm = null;
		boolean flag = false;
		FileOutputStream o = null;
		try {
			o = new FileOutputStream(fileName);
			o.write(content.getBytes("GBK"));
			o.close();
			flag = true;
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (mm != null) {
				try {
					mm.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return flag;
	}
}
