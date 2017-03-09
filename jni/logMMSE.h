#include<stdlib.h>
#include<stdio.h>
#include"Vad.h"
#ifndef _LOGMMSE_H_
#define _LOGMMSE_H_


#define FALSE 0


#define X_FLOAT32 float
#define X_INT16 short
#define X_INT32 int
#define PIx2                          6.28318530717958647692

/*----------------------------------------------------------------------------
 *                            logMMSE
 *----------------------------------------------------------------------------*/
#define samplRate                     (X_INT16)(8000)
#define FRAME_LEN                     (X_INT16)(20*samplRate/1000)
#define OVERLAP_RATE                  (X_FLOAT32) (0.5)
#define FRAME_SHIFT                   (X_INT16)(FRAME_LEN * OVERLAP_RATE)
#define FFT_LEN                       (X_INT16)(256)


#define PI          3.1415926
#define pi          3.14159265358979

#define max(a,b) ((a>b)?(a):(b))
#define min(a,b) ((a<b)?(a):(b))

typedef struct
{
  float real;
  float imag;
} Complex;

enum
{
  FFT,IFFT
};

typedef struct LOGMMSE_VAR LOGMMSE_VAR;


struct LOGMMSE_VAR
{
  X_INT16     SampFreq;                    // sampling frequency
  X_INT32     nbFrame;
  X_FLOAT32   Buf2denoise[FFT_LEN];
  X_FLOAT32   old_denosebuf[FRAME_SHIFT];
  Complex     FFTIn[FFT_LEN];
  X_FLOAT32   spect[FFT_LEN];
  X_FLOAT32   noiseMean[FFT_LEN];
  X_FLOAT32   sig[FFT_LEN];
  X_FLOAT32   gammak[FFT_LEN];
  X_FLOAT32   ksi[FFT_LEN];
  X_FLOAT32   Xk_prev[FFT_LEN];
  X_FLOAT32   log_sigma_k[FFT_LEN];
  X_FLOAT32   A[FFT_LEN];
  X_FLOAT32   vk[FFT_LEN];
  X_FLOAT32   ei_vk[FFT_LEN];
  X_FLOAT32   hw[FFT_LEN];
  X_FLOAT32   sigWindow [FRAME_LEN];
};



static void DoSigWindowing (X_FLOAT32 *Data, X_FLOAT32 *window, X_INT16 frameLength, X_INT16 FFTLength);

double expp(double x);




int fft(Complex *x, int lenforfft );
int ifft(Complex *x, int lenforifft);
int BitReverse(int src, int size);
void reverse_idx(Complex *in,int log4_N);
void fft_ifft_4_common(Complex *in,Complex * win,int log4_N,int reverse);
void fft4(Complex *in,int log4_N);
void ifft4(Complex *in,int log4_N);


void logMMSE_Init(LOGMMSE_VAR *NSX);

int logMMSE_denosie(X_INT16 *sigBuf, X_INT16 *OutBuf, LOGMMSE_VAR *logMMSE);

const char * logMMSE_denosie_bufall(X_INT16 *InBufall, int32 BufSize,LOGMMSE_VAR *logMMSE,cmd_ln_t *config,int32 threshold,char const *orderfilename);

int noise_estimate(X_INT16 *sigBuf, LOGMMSE_VAR *logMMSE);
int noise_estimate_bufall(X_INT16 *InBufall,int32 BufSize, LOGMMSE_VAR *logMMSE);

#endif
