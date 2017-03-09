package com.midea.VadAsr.utils;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.LinkedBlockingQueue;

import android.annotation.SuppressLint;
import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import com.midea.VadAsr.Config;
//import com.midea.VadAsr.Decoder;
//import com.midea.VadAsr.Hypothesis;
import com.midea.VadAsr.PocketSphinx;
//import com.midea.asr.Decoder;
import com.midea.VadAsr.utils.IOToolkit;
import com.midea.VadAsr.utils.MideaVad;
import com.midea.VadAsr.LogmmseVar;

/**
 * Speech recognition task, which runs in a worker thread.
 * 
 * This class implements speech recognition for this demo application. It takes
 * the form of a long-running task which accepts requests to start and stop
 * listening, and emits recognition results to a listener.
 * 
 * @author David Huggins-Daines <dhuggins@cs.cmu.edu>
 */
@SuppressLint("SdCardPath")
public class RecognizerTask implements Runnable {
	int volumeNum = 0;
	final static int MAX_VOLUME = 16;
	final static int FIRST_VOLUME = 15;
	public static int VADVOLUME = 60;
	public static boolean checkVolume = false;
	public static boolean isLoad = false;
	public HashMap<String, Integer> mValue = new HashMap<String, Integer>();
	public List<String> valueKey = new ArrayList<String>();
	//public static boolean isEnvEnergyDetect=true;
	

	/**
	 * Audio recording task.
	 * 
	 * This class implements a task which pulls blocks of audio from the system
	 * audio input and places them on a queue.
	 * 
	 * @author David Huggins-Daines <dhuggins@cs.cmu.edu>
	 */
	class AudioTask implements Runnable {
		/**
		 * Queue on which audio blocks are placed.
		 */
		LinkedBlockingQueue<short[]> q;
		AudioRecord rec;
		int block_size;

		static final int DEFAULT_BLOCK_SIZE = 512;

		AudioTask() {
			this.init(new LinkedBlockingQueue<short[]>(), DEFAULT_BLOCK_SIZE);
		}

		AudioTask(LinkedBlockingQueue<short[]> q) {
			this.init(q, DEFAULT_BLOCK_SIZE);
		}

		AudioTask(LinkedBlockingQueue<short[]> q, int block_size) {
			this.init(q, block_size);
		}

		void init(LinkedBlockingQueue<short[]> q, int block_size) {
			done = false;
			this.q = q;
			this.block_size = block_size;
			this.rec = new AudioRecord(MediaRecorder.AudioSource.DEFAULT, 16000,
					AudioFormat.CHANNEL_IN_MONO,
					AudioFormat.ENCODING_PCM_16BIT, 8192);
		}

		public int getBlockSize() {
			return block_size;
		}

		public void setBlockSize(int block_size) {
			this.block_size = block_size;
		}

		public LinkedBlockingQueue<short[]> getQueue() {
			return q;
		}

		public void stop() {
			done = true;
		}

		public void run() {
			this.rec.startRecording();
			while (!done) {
				int nshorts = this.readBlock();
				if (nshorts <= 0)
					break;
			}
			this.rec.stop();
			this.rec.release();
		}

		int readBlock() {
			short[] buf = new short[this.block_size];
			// LogUtils.e("readBlock:" + block_size);
			int nshorts = this.rec.read(buf, 0, buf.length);
			// LogUtils.e("readBlock:" + block_size + "   " + nshorts);
			if (nshorts > 0) {
				this.q.add(buf);
			}
			return nshorts;
		}
	}
	short[] mData = new short[2000];
	
	
    String isEndFlag;

	/**
	 * Audio recording task.
	 */
	AudioTask audio;
	/**
	 * Thread associated with recording task.
	 */
	Thread audio_thread;
	/**
	 * Queue of audio buffers.
	 */
	LinkedBlockingQueue<short[]> audioq;
	/**
	 * Listener for recognition results.
	 */
	public RecognitionListener rl;
	public boolean done;
	/**
	 * Whether to report partial results.
	 */
	boolean use_partials;

	/**
	 * State of the main loop.
	 */
	enum State {
		IDLE, LISTENING
	};

	/**
	 * Events for main loop.
	 */
	enum Event {
		NONE, START, STOP, SHUTDOWN
	};

	/**
	 * Current event.
	 */
	Event mailbox;

	public RecognitionListener getRecognitionListener() {
		return rl;
	}

	public void setRecognitionListener(RecognitionListener rl) {
		this.rl = rl;
	}

	public void setUsePartials(boolean use_partials) {
		this.use_partials = use_partials;
	}

	public boolean getUsePartials() {
		return this.use_partials;
	}

	Thread rec_thread;

	public void fileInitialWith() {
		BufferedReader bufReader = null;
		InputStreamReader inputReader = null;
		try {
			// mValue = new HashMap<String, Integer>();
			valueKey = new ArrayList<String>();
			inputReader = new InputStreamReader(new FileInputStream(new File(
					"/mnt/sdcard/edu.cmu.pocketsphinx/hmm/zh_CN/model/order.txt")));
			bufReader = new BufferedReader(inputReader);
			String line = "";
			while ((line = bufReader.readLine()) != null) {
				if (!line.equals("") || line != null) {
					// mValue.put(line, key);
					valueKey.add(line);
				}
			}
			LogUtils.d("mValue size:" + mValue.size());
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				inputReader.close();
				bufReader.close();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	private Config c;
	
	public RecognizerTask(Context mContext) {
		try {
			fileInitialWith();
/*			c  = new Config();
			c.setString("-hmm",
					"/mnt/sdcard/edu.cmu.pocketsphinx/hmm/zh_CN/tdt_sc_8k");
			c.setString("-lm",
					"/mnt/sdcard/edu.cmu.pocketsphinx/hmm/zh_CN/ask.lm.DMP");
			c.setString("-dict",
					"/mnt/sdcard/edu.cmu.pocketsphinx/hmm/zh_CN/ask.dic");
			c.setFloat("-samprate",8000);*/
			
			c = new Config();
			c.setString("-hmm", IOToolkit.MODEL_PATH + "model/thchs30_ins.cd_semi_200");
			c.setString("-lm", IOToolkit.MODEL_PATH + "model/ask_34_thchs30.lm.DMP");
			c.setString("-dict", IOToolkit.MODEL_PATH + "model/ask_34_thchs30.dic");
			c.setFloat("-samprate", 16000);
			
			this.audio = null;
			this.audioq = new LinkedBlockingQueue<short[]>();
			this.use_partials = false;
			this.mailbox = Event.NONE;
			this.rec_thread = new Thread(this);
			this.rec_thread.start();
		} catch (Exception e) {
			LogUtils.e("语音文件初始化失败---RecognizerTask");
		}
	}

	public void run() {
		/* Main loop for this thread. */
		boolean done = false;
		/* State of the main loop. */
		State state = State.IDLE;

		while (!done) {
			/* Read the mail. */
			Event todo = Event.NONE;
			synchronized (this.mailbox) {
				todo = this.mailbox;
				/* If we're idle then wait for something to happen. */
				if (state == State.IDLE && todo == Event.NONE) {
					try {
						LogUtils.d("waiting");
						this.rl.onVolume(0);
						this.mailbox.wait();
						todo = this.mailbox;
						LogUtils.d("got" + todo);
					} catch (Exception e) {
						/* Quit main loop. */
						LogUtils.e("Interrupted waiting for mailbox, shutting down");
						todo = Event.SHUTDOWN;
					}
				}
				/* Reset the mailbox before releasing, to avoid race condition. */
				this.mailbox = Event.NONE;
			}
			/* Do whatever the mail says to do. */
			switch (todo) {
			case NONE:
				if (state == State.IDLE)
					LogUtils.e("Received NONE in mailbox when IDLE, threading error?");
				break;
			case START:
				if (state == State.IDLE) {
					LogUtils.d("START");
					this.audio = new AudioTask(this.audioq, 2000);
					this.audio_thread = new Thread(this.audio);
					//this.ps.startUtt();
					this.audio_thread.start();
					state = State.LISTENING;
				} else
					LogUtils.e("Received START in mailbox when LISTENING");
				break;
			case STOP:
				if (state == State.IDLE)
					LogUtils.e("Received STOP in mailbox when IDLE");
				else {
					LogUtils.e("STOP");
					assert this.audio != null;
					this.audio.stop();

					try {
						this.audio_thread.join();
						// //利用VAD开始检测语音活动//////////////

						//LogUtils.d("writeTxtFile right  fileName:"
								//+ mArrayList.size() + "  vadStart:" + vadStart
								//+ "   vadend:" + vadEnd);

						//this.ps.endUtt();
						this.audio = null;
						this.audio_thread = null;
						//Hypothesis hyp = this.ps.hyp();""
						if (this.rl != null) {
							if (this.hyp == null) {
								//this.rl.onError("");
								new Handler(Looper.getMainLooper())
										.post(new Runnable() {
											@Override
											public void run() {
												rl.onResults(null);
											}
										});
							} else {
//								final Bundle b = new Bundle();
//								b.putString("hyp", this.hyp);
//								final String bString = ((Bundle) b)
//										.getString("hyp");
								Handler mainThread = new Handler(
										Looper.getMainLooper());
								mainThread.post(new Runnable() {
									@Override
									public void run() {
										rl.onResults(hyp);
										/*boolean isTrue = false;
										try {
											LogUtils.d("+++INFO: mEnergy"
													+ bString);
											for (String str : valueKey) {
												if (bString.contains(str)) {
													rl.onResults(bString + ":"
															+ str);
													isTrue = true;
													break;
												}
											}
											if (!isTrue) {
												rl.onResults(null);
											}
										} catch (Exception e) {
											rl.onResults(null);
										}*/
									}
								});

							}
						}
						state = State.IDLE;
					} catch (Exception e) {
						LogUtils.e("Interrupted waiting for audio thread, shutting down");
						done = true;
					}
				}
				break;
			case SHUTDOWN:
				LogUtils.d("SHUTDOWN");
				if (this.audio != null) {
					this.audio.stop();
					assert this.audio_thread != null;
					try {
						this.audio_thread.join();
					} catch (InterruptedException e) {
						/* We don't care! */
					}
				}
				//this.ps.endUtt();
				this.audio = null;
				this.audio_thread = null;
				state = State.IDLE;
				done = true;
				break;
			}
			if (state == State.LISTENING) {
				assert this.audio != null;
				try {
					short[] buf = this.audioq.take();

					// //利用VAD开始检测语音活动//////////////
					if (!isLoad) {
						loadVoice(buf);
					} else {
						LogUtils.v("startRecognizer");
						startRecognizer(buf);
					}
					// //利用VAD开始检测语音活动//////////////
				} catch (InterruptedException e) {
					LogUtils.d("Interrupted in audioq.take");
				}
			}
		}
	}

	static int vadStart = 0;
	static int vadEnd = 0;

	static int num = 0;
	Integer be = 0, b = 0;
	boolean isStart = false;
	boolean isEnd = false;

	public void start() {
		be = 0;
		b = 0;
		isStart = false;
		isEnd = false;
		vadStart = 0;
		vadEnd = 0;
		//nFrame = 0;
		//mArrayList = new ArrayList<short[]>(); // 存放待识别的数据
		LogUtils.d("signalling START");
		synchronized (this.mailbox) {
			this.mailbox.notifyAll();
			LogUtils.d("signalled START");
			this.mailbox = Event.START;
			Handler mainThread = new Handler(Looper.getMainLooper());
			mainThread.post(new Runnable() {
				@Override
				public void run() {
					rl.onAsrStart();
				}
			});
		}
	}

	public void rStop() {
		LogUtils.d("signalling STOP");
		synchronized (this.mailbox) {
			this.mailbox.notifyAll();
			LogUtils.d("signalled STOP");
			this.mailbox = Event.STOP;
		}
	}
  
	private String hyp="";
	
	MideaVad mMideaVad = new MideaVad();
	float mEnergy = 0;
	int num_estimate=0;

	LogmmseVar logmmse=new LogmmseVar();
	
	public void startRecognizer(short[] mData) {
		//System.out.println("+++INFO: isEnvEnergyDetect is "+isEnvEnergyDetect);
		
			int thre =50;
			String orderfilename = IOToolkit.MODEL_PATH + "model/order.txt";
			
			
			mEnergy = mMideaVad.getFrameEnergy(mData, 2000);
			System.out.println("+++INFO: the Energy before ns is "+mEnergy);
			if (num_estimate==0){
				logmmse.logmmseinit();
				logmmse.noiseestimatebufall(mData,2000);
				num_estimate++;}
			
			isEndFlag=this.logmmse.logmmsedenosebufall(mData,2000,this.c,thre,orderfilename);
			System.out.println("+++INFO: isEndFlag is "+isEndFlag);
			if (isEndFlag != null) {
			if(!isEndFlag.equals("false"))
			{
			    System.out.println("+++INFO: Detected end point!");
			    this.hyp = isEndFlag;
			    System.out.println("+++INFO: hyp is "+this.hyp);
			    
			    rStop();
			}
			}
	}

	
	public void loadVoice(short[] mData) {
		//isEnvEnergyDetect=PocketSphinx.EnvEnergy(mData);
		
		//if (isEnvEnergyDetect) {
		//this.logmmse = new LogmmseVar();
/*		logmmse.logmmseinit();
		if (logmmse.noiseestimatebufall(mData,2000)==1){
				System.out.println("+++INFO: isLoad is true");
				isLoad = true;
				rStop();
		}*/
		isLoad = true;
		rStop();
		//}
	}

	public void shutdown() {
		LogUtils.d("signalling SHUTDOWN");
		synchronized (this.mailbox) {
			this.mailbox.notifyAll();
			LogUtils.d("signalled SHUTDOWN");
			this.mailbox = Event.SHUTDOWN;
		}
	}
}