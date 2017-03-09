/*
 * VoiceDetect.c
 *
 *  Created on: Feb 5, 2017
 *      Author: mlliu
 */



#include"Vad.h"

#define MODELDIR "/home/mlliu/sphinx/linux-demo/model"

int main()
{
	cmd_ln_t *config;
	config = cmd_ln_init(NULL, ps_args(), true,
                "-hmm", MODELDIR "/tdt_sc_8k",
                "-lm", MODELDIR "/ask.lm.DMP",
                "-dict", MODELDIR "/ask.dic",
                "-fwdtree", "yes",
                "-fwdflat", "yes",
                "-bestpath", "yes",
                "-mfclogdir", ".",
                "-rawlogdir", ".",
                "-samprate", "8000",
                NULL); 


	FILE *infp=NULL;   //the pointer to input file
    //FILE *outfp=NULL;  // the pointer to output file


	bool isEnvEnergyDetect=false;
	bool isEndFlag=false;

	unsigned char *wav_header;//��record the head of file)
	wav_header=(unsigned char *)malloc(sizeof(unsigned char)* WAVEHEAD);
    if(!wav_header)
	exit(-1);

	int read_len;
	int numwritten;

	byte *myData;
	myData=(byte *)malloc(sizeof(byte)*DATASAPLES*2);
	if(!myData)
	{
		free(wav_header);
	     wav_header=NULL;
		 exit(-1);
	}
	infp=fopen("/home/mlliu/eclipse_workspace/VAD/src/liuwenhui.wav","rb");
	if(NULL == infp)
	{
		printf("+++INFO: erro: Can not open file: \n");
		exit(-1);
	}
	fseek(infp,0L,SEEK_SET);
	fread(wav_header,sizeof(char),44,infp);
	while(true)
	{
		read_len=fread(myData,sizeof(byte),DATASAPLES*2,infp);
		if(read_len<DATASAPLES*2)
				  break;

		//byte2short
		short *mData;
		mData=(short *)malloc(sizeof(short)*DATASAPLES);
		if(!mData)
		{
			exit(-1);
		}
			for(int i=0;i<DATASAPLES;i++)
			{
				mData[i]=byte2short(myData[2*i], myData[2*i+1]);
				//if(i<10)
				//printf("+++INFO: mData[%d]=%d ",i,mData[i]);
			}


		if(!isEnvEnergyDetect)
		isEnvEnergyDetect=EnvEnergyDetect(mData);
		if(isEnvEnergyDetect)
		{
			//short Data[20000];//在这里定义Data，主要是为了刷新Data
			//int Data_size = 0;
		    isEndFlag=VoiceDetectMain(mData,config);
		    if(isEndFlag)
		     {
		    	printf("+++INFO: Detected end point!");
				/*outfp=fopen("/home/mlliu/eclipse_workspace/Voice_Detect/Debug/output.txt","wb");
				if(NULL == outfp)
				{
				printf("+++INFO: error: Can not open file: \n");
				exit(-1);*/
				//}
		        //int l=sizeof (Data)/(sizeof (short));
				//printf("Data_size is %d",Data_size*DATASAPLES);
		        //numwritten=fwrite(Data, sizeof(short),Data_size*DATASAPLES, outfp);
		        //printf( "Write %d items\n", numwritten );
                //fclose( outfp);
                /*char const * hyp = ps_decoder_test(config,Data,Data_size);
                   printf("+++INFO: hyp = %s\n",hyp);*/


           	    if(mData){
           			free(mData);
           			mData=NULL;
           	   }
		       //break;
		    }
			else
              continue;
		}
		else
			continue;
	}
	return 0;
}

//short buf_data[VAD_DETECT_FRAMELAST][DATASAPLES];
//int   mVadEnergyBuf[VAD_DETECT_FRAMELAST];
//float mEnvEnergyBuf[ENV_DETECT_FRAMELAST];
//std::vector<short>svec;
//short VadData[20000];

//bool isGetEnvEnergy = false; // is get enviroment energy

/*bool isVadStaFlagSucceed=false;
bool isVadStaFlag=false;
bool isVadEndFlag=false;
int count=0;
int num=0;
float vadEnergyTht =  0.0; // vad energy tht
int Datasize=0;*/

//byte2short
 extern short byte2short(byte low, byte high)
{
		// TODO Auto-generated method stub
		return (short) (((high & 0x00FF) << 8) | (0x00FF & low));
}
//
 int getWaveTimeLast(int nSamples, int fs)
	{
		float last = 0;
		//last = ((float) nSamples / fs) * 1000;
		last = ((float) nSamples / fs);

		return (int) (last * 1000);
	}
 	// get energy
	float getFrameEnergy(short *data, int len)
   {
		float energy = (float) 0.0;
		for (int i = 0; i < len; i++)
		{
			energy += data[i] * data[i] / (float) len;
		}
		energy = (float)sqrt(energy);
		return energy;
	}
	// get Frame Energy Mean
	 float getEnergyMean(float *energyArray, int frameCnt)
	 {
		float mean = 0;
		for (int i = 0; i < frameCnt; i++) {
			mean += energyArray[i];
		}
		mean = mean / frameCnt;
		return mean;
	}
	// init value for next vad process
/*	 void mideaVadReset()
	{
		isVadSta = false;
		isVadEnd = false;
	}*/
// get enviroment energy
    bool getEnvEnergy(float *envEnergyDur, int frameCnt)
	//bool getEnvEnergy(float *envEnergyDur, int frameCnt,float *envEnergyBase)
	{
		int flag = 0;
		int temp = 0;
		for (int i = 0; i < frameCnt - 1; i++) {
			if (abs(envEnergyDur[i + 1] - envEnergyDur[i]) < ENV_ENERGY_MINVAR) {
				temp = 0;
			} else {
				temp = 1;
			}
			flag += temp;
		}
		if (0 == flag) {
			//isGetEnvEnergy = true;
			// envEnergyBase = envEnergyDur[frameCnt - 2];
			envEnergyBase = getEnergyMean(envEnergyDur, frameCnt);
			//vadEnergyTht = VAD_TRIGGER_RATIO * (*envEnergyBase);
			//采用起点和终点分别触发设置，防止终点不能检测，起点难触发
			if(envEnergyBase<500){
			vadEnergyTht_sta = VAD_TRIGGER_RATIO_sta *(envEnergyBase);
			vadEnergyTht_end = VAD_TRIGGER_RATIO_end *(envEnergyBase);
			printf("+++INFO: vadEnergyTht_sta = %f\n" ,vadEnergyTht_sta);
			printf("+++INFO: vadEnergyTht_end = %f\n" ,vadEnergyTht_end);}
		}

		//return isGetEnvEnergy;
		return true;
	}
	// get vad flag
    int getVadFlag(float energy,float vadEnergyTht)
	{
		//if (isGetEnvEnergy) {
			if (energy > (vadEnergyTht)) {
				return 1;
			} else {
				return 0;
			}
		//} else {
			//return -1;
		//}
	}
	// is vad start
	 bool isVadStartPointDetect(float* vadEnyArray, int frameCnt) {
		if (frameCnt < VAD_STA_FRAMELAST_THT) {
			return false;
		}
		
		int *vadArray;
		vadArray = (int*)malloc(VAD_DETECT_FRAMELAST*sizeof(int));
		for(int i=0;i<frameCnt;i++)
		{
			vadArray[i]=getVadFlag(vadEnyArray[i],vadEnergyTht_sta);
		}
		int staFlag = 1; // ��ʼΪ1
		int staTemp = 0;
		int cnt = 0;
		for (int i = 0; i < frameCnt - 1; i++) {

			if (vadArray[i + 1] == 1 && vadArray[i] == 0) {
				staTemp = 1;
			}
			if (1 == staTemp) {
				cnt++;
				staFlag &= vadArray[i + 1];
				if (cnt >= VAD_STA_FRAMELAST_THT) {
					if (1 == staFlag) {
						free(vadArray);
						return true;
					} else {
						free(vadArray);
						return false;
					}
				}
			}
		}
		free(vadArray);
		return false;
		}

	// is vad end
	bool isVadFinishPointDetect(float *vadEnyArray, int frameCnt)
	{
		if (frameCnt < VAD_STA_FRAMELAST_THT)
		{
			return false;
		}
		int *vadArray;
		vadArray=(int *)malloc(VAD_DETECT_FRAMELAST*sizeof(int));
		if(NULL==vadArray)
		{
			exit(1);
		}
		for(int i=0;i<frameCnt;i++)
		{
			vadArray[i]=getVadFlag(vadEnyArray[i],vadEnergyTht_end);
		}
		int endFlag = 0;
		int endTemp = 0;
		int cnt = 0;
		for (int i = 0; i < frameCnt - 1; i++)
		{
			if (vadArray[i + 1] == 0 && vadArray[i] == 1)
			{
				endTemp = 1;
			}
			if (1 == endTemp) {
				cnt++;
				endFlag |= vadArray[i + 1];
				if (cnt >= VAD_END_FRAMELAST_THT)
				{
					if (0 == endFlag) {
						free(vadArray);
						return true;
					} else {
						free(vadArray);
						return false;
					}
				}
			}
		}
		free(vadArray);
		return false;
	}
	bool VoiceDetectMain(short *mData,cmd_ln_t *config)
	{
		int mFrameLastVad=VAD_DETECT_FRAMELAST;//6
		float mEnergy = 0;
		int mVadFlag = 0;


		printf("+++INFO: start voice activity detect!");
		mEnergy=getFrameEnergy(mData, DATASAPLES);
		printf("+++INFO: mEnergy[%d] = %f\n" ,num,mEnergy);
		//mVadFlag = getVadFlag(mEnergy,vadEnergyTht);
		// System.out.println("+++INFO: mVadFlag = " + mVadFlag);
		if (num < mFrameLastVad)
		{
			//mVadEnergyBuf[num] = mVadFlag;
			mVadEnergyBuf[num]=mEnergy;
			for(int i=0;i<DATASAPLES;i++)
			buf_data[num][i]=mData[i];
			num++;
			return false;
		}
		else
		{
			for (int i = 1; i < mFrameLastVad; i++)
			{
				mVadEnergyBuf[i - 1] = mVadEnergyBuf[i];
			}
			mVadEnergyBuf[mFrameLastVad - 1] = mEnergy;

			for(int k=1;k<mFrameLastVad;k++)
			{
				for(int i=0;i<DATASAPLES;i++)
					{
						buf_data[k-1][i]=buf_data[k][i];
					}
			}
			for(int i=0;i<DATASAPLES;i++)
				{
					buf_data[mFrameLastVad-1][i]=mData[i];
				}


			if (false == isVadStaFlagSucceed)
			{
				getEnvEnergy(mVadEnergyBuf, mFrameLastVad);
				isVadStaFlag = isVadStartPointDetect(mVadEnergyBuf,
						mFrameLastVad);
				
				if (isVadStaFlag)
				{
					printf("+++INFO: Detected start point!");
					// save data,push the buf_data to the svec
					for (int i = 0; i < mFrameLastVad-1; i++)
					{
						for(int j=0;j<DATASAPLES;j++)
						{
							//svec.push_back(buf_data[i][j]);
							VadData[j+i*DATASAPLES]=buf_data[i][j];

						}
					}
					Datasize = mFrameLastVad-1;
				}
				else
					return false;
			}

			if (isVadStaFlag)
			{
				isVadStaFlagSucceed = true;
				// save data
				for(int j=0;j<DATASAPLES;j++)
					{
						//svec.push_back(mData[j]);
					    VadData[j+ Datasize * DATASAPLES]=mData[j];

					}
				Datasize++;
				isVadEndFlag = isVadFinishPointDetect(mVadEnergyBuf, mFrameLastVad);
				if (isVadEndFlag)
				{
					//after isVadEndFlag==true,all the flag must return to be false
					//isEnvEnergyDetect=false;
		            count = 0;
		            num = 0;
		            //Datasize=0;
					isVadStaFlag = false;
					isVadEndFlag = false;
					isVadStaFlagSucceed = false;

					printf("+++INFO: Detected end point!");

					int waveLast = getWaveTimeLast(Datasize * DATASAPLES, 8000);//fs=8000;
					if ((waveLast > VALID_WAVE_LAST_MIN)&& (waveLast < VALID_WAVE_LAST_MAX))
					{
							printf("+++INFO: The Voice is Valid for ASR!");

							printf("+++INFO: The Voice size is %d: ",Datasize * DATASAPLES);
							char const * hyp = ps_decoder_test(config,VadData,Datasize* DATASAPLES);
							printf("+++INFO: hyp = %s\n",hyp);
  							FILE *outfile;
    							outfile = fopen("result.txt","at");
							fputs(hyp,outfile);
                					fputs("\n",outfile);
							fclose(outfile);

							return true;
					}
					else
					{
						    printf("+++INFO: The Voice size is %d: ",Datasize * DATASAPLES);
							printf("+++INFO: The Voice is Unvalid for ASR!");
							return false;
					}
				}
				else
					return false;
				}
			}
	}


	bool EnvEnergyDetect(short *mData)
	{
		 int mFrameLastEnv=ENV_DETECT_FRAMELAST;
		 float mEnergy = 0;
	     	 //float envEnergyBase =  0.0; // envEnergy

		 mEnergy=getFrameEnergy(mData, DATASAPLES);

		 if ((count) < mFrameLastEnv)
		 {
				mEnvEnergyBuf[count] = mEnergy;
				printf("+++INFO: mEnergy[%d] = %f\n" ,count,mEnergy);
				count ++;

				return false;
		 }
		 else
		 {
				for (int i = 1; i < mFrameLastEnv; i++)
					{
						mEnvEnergyBuf[i - 1] = mEnvEnergyBuf[i];
					}
					mEnvEnergyBuf[mFrameLastEnv - 1] = mEnergy;
					if (getEnvEnergy(mEnvEnergyBuf, mFrameLastEnv))
					{
						printf("+++INFO: Enviroment Energy obtain success!");
						printf("+++INFO: Env Energy = %f\n",envEnergyBase);

						return true;
					}
				}
		}




char const *ps_decoder_test1(cmd_ln_t *config, int16 *data,long total)
{
    ps_decoder_t *ps;
    char const *hyp;
    int32 score;

    ps = ps_init(config);
    ps_start_utt(ps);
    //Test it first with pocketsphinx_decode_raw()

    ps_process_raw(ps, data, total, false, true);
    ps_end_utt(ps);

    hyp = ps_get_hyp(ps, &score);

    return hyp;
}




