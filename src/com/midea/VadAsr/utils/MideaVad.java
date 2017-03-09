package com.midea.VadAsr.utils;


public class MideaVad {
	// 最小环境方差，当连续帧能量均低于此值时，认为环境能量趋于稳定
	public final static float ENV_ENERGY_MINVAR = (float) 200.0;
	// VAD 触发阈值设置，当说话能量为80倍环境能量时，VAD start
	public final static float VAD_TRIGGER_RATIO_sta = (float) 3;
	
	public final static float VAD_TRIGGER_RATIO_end = (float) 6;
	// VAD 开始持续1帧数
	public final static int VAD_STA_FRAMELAST_THT = 3;
	// VAD 结束持续0帧数
	public final static int VAD_END_FRAMELAST_THT = 3;
	// ENV 环境能量检测持续帧数
	public final static int ENV_DETECT_FRAMELAST = 10;
	// VAD 检测持续帧数
	public final static int VAD_DETECT_FRAMELAST = 6;
	// Valid Comand Wave Last (200ms - 1500ms) + vad 起始和结束多余帧
	public final static int VALID_WAVE_LAST_MIN = 200;
	public final static int VALID_WAVE_LAST_MAX = 2500;

	public boolean isVadSta = false; // vad start flag
	public boolean isVadEnd = false; // vad end flag
	public static boolean isGetEnvEnergy = false; // is get enviroment energy
	public static float vadEnergyTht_sta = (float) 1500.0; // vad energy tht
	public static float vadEnergyTht_end = (float) 2000.0; // vad energy tht
	public static float envEnergyBase = (float) 0.0; // envEnergy

	// 根据wave点数求取持续时间,单位:ms
	public int getWaveTimeLast(int nSamples, int fs) {
		float last = 0;
		last = ((float) nSamples / fs) * 1000;
		
		return (int) (last * 1000);
	}

	// init value for next vad process
	public void mideaVadReset() {
		isVadSta = false;
		isVadEnd = false;
	}

	// get energy
	public float getFrameEnergy(short[] data, int len) {
		float energy = (float) 0.0;
		for (int i = 0; i < len; i++) {
			// energy += Math.abs(data[i]) / (float) len;
			energy += data[i] * data[i] / (float) len;
		}
		energy = (float) Math.sqrt(energy);
		return energy;
	}

	// get Frame Energy Mean
	public float getEnergyMean(float[] energyArray, int frameCnt) {
		float mean = 0;
		for (int i = 0; i < frameCnt; i++) {
			mean += energyArray[i];
		}
		mean = mean / frameCnt;
		return mean;
	}

	// get enviroment energy
	public boolean getEnvEnergy(float[] envEnergyDur, int frameCnt) {
		int flag = 0;
		int temp = 0;
		for (int i = 0; i < frameCnt - 1; i++) {
			if (Math.abs(envEnergyDur[i + 1] - envEnergyDur[i]) < ENV_ENERGY_MINVAR) {
				temp = 0;
			} else {
				temp = 1;
			}
			flag += temp;
		}
		if (0 == flag) {
			isGetEnvEnergy = true;
			// envEnergyBase = envEnergyDur[frameCnt - 2];
			// 将前面环境稳定连续帧的能量平均作为环境能量基准
			
			envEnergyBase = getEnergyMean(envEnergyDur, frameCnt);
			if (envEnergyBase<500){
				vadEnergyTht_sta = VAD_TRIGGER_RATIO_sta * envEnergyBase;
				vadEnergyTht_end = VAD_TRIGGER_RATIO_end * envEnergyBase;
			}
			//vadEnergyTht = VAD_TRIGGER_RATIO * envEnergyBase;
			LogUtils.d("+++INFO: mEnergyBase = " + envEnergyBase);
			LogUtils.d("+++INFO: mEnergyTht_sta = " + vadEnergyTht_sta);
			LogUtils.d("+++INFO: mEnergyTht_end = " + vadEnergyTht_end);
		}

		return isGetEnvEnergy;
	}

	// get vad flag
	public int getVadFlag(float energy,float vadEnergy_Tht) {
		if (isGetEnvEnergy) {
			if (energy > vadEnergy_Tht) {
				return 1;
			} else {
				return 0;
			}
		} else {
			return -1;
		}
	}

/*	public int[] getVadFlag_array(float[] energyarray,float vadEnergyTht) {
		int[] vadArray = new int[VAD_DETECT_FRAMELAST];
		for (int i =0; i <VAD_DETECT_FRAMELAST;i++)
		{
			if (isGetEnvEnergy) {
				if (energyarray[i] > vadEnergyTht) {
					vadArray[i]=1;
				} else {
					vadArray[i]=0;
				}
			} 
			
	}return vadArray;
	}*/

	// is vad start
	public boolean isVadStartPointDetect(float[] vadEnyArray, int frameCnt) {
		
		if (frameCnt < VAD_STA_FRAMELAST_THT) {
			return false;
		}
		
		int[] vadArray = new int[frameCnt];
		for (int i =0; i <frameCnt;i++){
			vadArray[i] = getVadFlag(vadEnyArray[i],vadEnergyTht_sta);
		}
		
		
		int staFlag = 1; // 初始为1
		int staTemp = 0;
		int cnt = 0;
		for (int i = 0; i < frameCnt - 1; i++) {
			// 前一帧为0，后一帧为1，则可能为VAD起点
			if (vadArray[i + 1] == 1 && vadArray[i] == 0) {
				staTemp = 1;
			}
			if (1 == staTemp) {
				cnt++;
				staFlag &= vadArray[i + 1];
				if (cnt >= VAD_STA_FRAMELAST_THT) {
					if (1 == staFlag) {
						return true;
					} else {
						return false;
					}
				}
			}
		}

		return false;
	}

	// is vad end
	public boolean isVadFinishPointDetect(float[] vadEnyArray, int frameCnt) {
		if (frameCnt < VAD_STA_FRAMELAST_THT) {
			return false;
		}
		
		int[] vadArray = new int[frameCnt];
		for (int i =0; i <frameCnt;i++){
			vadArray[i] = getVadFlag(vadEnyArray[i],vadEnergyTht_end);
		}
		
		int endFlag = 0;
		int endTemp = 0;
		int cnt = 0;
		for (int i = 0; i < frameCnt - 1; i++) {
			// 前一帧为1，后一帧为0，则可能为VAD终点
			if (vadArray[i + 1] == 0 && vadArray[i] == 1) {
				endTemp = 1;
			}
			if (1 == endTemp) {
				cnt++;
				endFlag |= vadArray[i + 1];
				if (cnt >= VAD_END_FRAMELAST_THT) {
					if (0 == endFlag) {
						return true;
					} else {
						return false;
					}
				}
			}
		}

		return false;
	}
}
