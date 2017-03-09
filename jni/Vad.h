/*
 * Voice_detect.h
 *
 *  Created on: Feb 5, 2017
 *      Author: mlliu
 */

#ifndef SRC_VOICE_DETECT_H_
#define SRC_VOICE_DETECT_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "pocketsphinx.h"
#include "asr.h"
typedef short		int16;

#define N 1874*2  // 1874(30S)  624(10S) 438(7s)  311(5s)   186(3s)  61(1s)
#define SIZE (N+1)*FRAME_INC  //240000(30S)  80000(10S) 56000(7s) 40000(5s)  24000(3s)  8000(1s)��sap=8000
// VAD
#define VAD_STA_FRAMELAST_THT     3
// VAD
#define VAD_END_FRAMELAST_THT     3
// ENV
#define ENV_DETECT_FRAMELAST      10
// ENV
#define VAD_DETECT_FRAMELAST       6
//
#define ENV_ENERGY_MINVAR         200
//
#define ENV_ZCR_MINVAR              3
//
#define VAD_TRIGGER_RATIO          4
// Valid Comand Wave Last (200ms - 1500ms) + vad
#define WAVEHEAD 44
//VAD 起点检测触发阈值设置，VAD_TRIGGER_RATIO_sta
#define VAD_TRIGGER_RATIO_sta      4
//VAD 终点检测触发阈值设置，VAD_TRIGGER_RATIO_end
#define VAD_TRIGGER_RATIO_end      4.5

#define true 1
#define false 0
#define bool int
#define  DATASAPLES           2000
#define  VALID_WAVE_LAST_MIN  200
#define  VALID_WAVE_LAST_MAX  2500
typedef unsigned char byte;
//bool isVadSta = false; // vad start flag
//bool isVadEnd = false; // vad end flag
//bool isGetEnvEnergy = false; // is get enviroment energy

//extern short byte2short(byte low, byte high);
float getFrameEnergy(int16 const *data, int len);
int getWaveTimeLast(int nSamples, int fs);
bool getEnvEnergy(float *envEnergyDur, int frameCnt);
int getVadFlag(float energy,float vadEnergyTht);
bool isVadStartPointDetect(float* vadArray, int frameCnt);
bool isVadFinishPointDetect(float *vadArray, int frameCnt);

bool EnvEnergyDetect(int16 const *myData);
char const* VoiceDetectMain(int16 const *myData,cmd_ln_t *config,int32 threshold,char const *orderfilename);
//char const *ps_decoder_test(cmd_ln_t *config, int16 *data,long total);

int16 buf_data[VAD_DETECT_FRAMELAST][DATASAPLES];
float   mVadEnergyBuf[VAD_DETECT_FRAMELAST];
float mEnvEnergyBuf[ENV_DETECT_FRAMELAST];
int16 VadData[40000];
/*
bool isVadStaFlagSucceed=false;
bool isVadStaFlag=false;
bool isVadEndFlag=false;
int count=0;
int num=0;
float vadEnergyTht =  0.0; // vad energy tht
int Datasize=0;*/


#endif /* SRC_VOICE_DETECT_H_ */
