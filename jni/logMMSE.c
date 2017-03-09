#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "logMMSE.h"

#define max(a,b) ((a>b)?(a):(b))
#define min(a,b) ((a<b)?(a):(b))


static void DoSigWindowing (X_FLOAT32 *Data, X_FLOAT32 *window, X_INT16 frameLength, X_INT16 FFTLength)
{
  X_INT16 i;

  // windowing
  for (i=0 ; i<frameLength ; i++)
    Data [i] = Data[i] * window [i];

  // zero padding
  for (i=frameLength ; i<FFTLength ; i++)
    Data [i] = 0.0;

  return;
}

double expp(double x)
{
    int m,i,j;
    double s,p,ep,h,aa,bb,w,xx,g,r,q;
    static double t[5]={-0.9061798459,-0.5384693101,0.0,
                         0.5384693101,0.9061798459};
    static double c[5]={0.2369268851,0.4786286705,0.5688888889,
                        0.4786286705,0.2369268851};
    m=1;
    if (x==0) x=1.0e-10;
    if (x<0.0) x=-x;
    r=0.57721566490153286060651;
    q=r+log(x);
    h=x; s=fabs(0.0001*h);
    p=1.0e+35; ep=0.000001; g=0.0;
    while ((ep>=0.0000001)&&(fabs(h)>s))
      { g=0.0;
        for (i=1;i<=m;i++)
          { aa=(i-1.0)*h; bb=i*h;
            w=0.0;
            for (j=0;j<=4;j++)
              { xx=((bb-aa)*t[j]+(bb+aa))/2.0;
                w=w+(exp(-xx)-1.0)/xx*c[j];
              }
            g=g+w;
          }
        g=g*h/2.0;
        ep=fabs(g-p)/(1.0+fabs(g));
        p=g; m=m+1; h=x/m;
      }
    g=q+g;
    return(g);
}

int logMMSE_denosie(X_INT16 *sigBuf, X_INT16 *OutBuf, LOGMMSE_VAR *logMMSE)

{


    X_INT16 i = 0;
    X_INT16 fstage;
    X_FLOAT32 tmp_var       = 0.0;
    X_FLOAT32 vad_decision  = 0.0;
    X_FLOAT32 log_sigma_sum = 0.0;


    X_FLOAT32 *Buf2denoise  = logMMSE->Buf2denoise;
    X_FLOAT32 *old_denosebuf= logMMSE->old_denosebuf;
    Complex   *FFTIn        = logMMSE->FFTIn;
    X_FLOAT32 *spect        = logMMSE->spect;
    X_FLOAT32 *Xk_prev      = logMMSE->Xk_prev;
    X_FLOAT32 *noiseMean    = logMMSE->noiseMean;
    X_FLOAT32 *sig          = logMMSE->sig;
    X_FLOAT32 *gammak       = logMMSE->gammak;
    X_FLOAT32 *ksi          = logMMSE->ksi;
    X_FLOAT32 *log_sigma_k  = logMMSE->log_sigma_k;
    X_FLOAT32 *A            = logMMSE->A;
    X_FLOAT32 *vk           = logMMSE->vk;
    X_FLOAT32 *ei_vk        = logMMSE->ei_vk;
    X_FLOAT32 *hw           = logMMSE->hw;
    X_INT32 *Frame_count   = &(logMMSE->nbFrame);

    X_FLOAT32 aa  = 0.98;
    X_FLOAT32 mu  = 0.98;
    X_FLOAT32 eta = 0.15;
    X_FLOAT32 ksi_min = pow(10,-2.5);

    (*Frame_count) ++;

    for(fstage = 0; fstage < 1; fstage ++)
    {
      if((*Frame_count) == 1)
        {
            for(i = 0; i < FRAME_SHIFT; i ++)
            {
                Buf2denoise[i] = sigBuf[i];
            }
            continue;
        }

        for(i = 0; i < FRAME_SHIFT; i ++)
        {
            Buf2denoise[i + FRAME_SHIFT] = sigBuf[i];
        }

        DoSigWindowing (Buf2denoise, logMMSE->sigWindow, FRAME_LEN, FFT_LEN);
        for(i = 0; i < FFT_LEN; i ++)
        {
            FFTIn[i].real = Buf2denoise[i];
            FFTIn[i].imag = 0.0;
        }



        //fft4(FFTIn, 4);
        fft(FFTIn,FFT_LEN);

        for(i = 0; i < FFT_LEN; i ++)
        {
           spect[i] = FFTIn[i].real * FFTIn[i].real + FFTIn[i].imag * FFTIn[i].imag;
        }



        for(i = 0; i < FFT_LEN; i ++)
        {

            sig[i] = spect[i];
            gammak[i] = min((sig[i]/noiseMean[i]),40);
            //printf("%f ",gammak[i]);
            if(*Frame_count == 2)
            {
                ksi[i] = aa + (1 - aa) * max(gammak[i]-1,0);
            }
            else
            {
                ksi[i] = aa * Xk_prev[i] / noiseMean[i] + (1-aa) * max(gammak[i]-1,0);
                ksi[i] = max(ksi_min,ksi[i]);
                //printf("%f ",Xk_prev[i]);
            }

            log_sigma_k[i] = gammak[i] * ksi[i] / (1 + ksi[i]) - log(1 + ksi[i]);

            log_sigma_sum += log_sigma_k[i];
        }

        for(i = 0; i < FFT_LEN; i ++)
        {
            //printf("%f ",log_sigma_k[i]);
        }
       /* printf("\n");
        printf("\n");*/
        vad_decision = log_sigma_sum / FRAME_LEN;
        if(vad_decision < eta)
        {
            for(i = 0; i < FFT_LEN; i ++)
                noiseMean[i] = mu * noiseMean[i] + (1 - mu) * sig[i];
        }
        for(i = 0; i < FFT_LEN; i ++)
        {
            A[i]       = ksi[i] / (1 + ksi[i]);
            vk[i]      = A[i] * gammak[i];
            //printf("%f ",vk[i]);
            ei_vk[i]   = 0.5 * (-expp(vk[i]));

            hw[i]      = A[i] * exp(ei_vk[i]);
            tmp_var    = sqrt(spect[i]) * hw[i];
            Xk_prev[i] = tmp_var * tmp_var;
            FFTIn[i].real = FFTIn[i].real * hw[i];
            FFTIn[i].imag = FFTIn[i].imag * hw[i];
        }

        //ifft4(FFTIn,4);
        ifft(FFTIn,FFT_LEN);
        for(i = 0; i < FRAME_SHIFT; i ++)
        {
            OutBuf[i] = (X_INT16) (old_denosebuf[i] + FFTIn[i].real);
            //printf("%f ",OutBuf[i]);
            old_denosebuf[i] = FFTIn[FRAME_SHIFT + i].real;
        }


        for(i = 0; i < FRAME_SHIFT; i ++)
        {
            Buf2denoise[i] = sigBuf[i];
        }
    }

    return 0;



}

const char * logMMSE_denosie_bufall(X_INT16 *InBufall,int32 BufSize,LOGMMSE_VAR *logMMSE,cmd_ln_t *config,int32 threshold,char const *orderfilename){
	const char* hyp = NULL;

	X_INT16 *OutBufall;
	X_INT16 *InBuf;
	X_INT16 *OutBuf;

	OutBufall = (X_INT16 *)malloc(sizeof(X_INT16)*BufSize);
	InBuf = (X_INT16 *)malloc(sizeof(X_INT16)*FRAME_SHIFT);
	OutBuf = (X_INT16 *)malloc(sizeof(X_INT16)*FRAME_SHIFT);
	int i=0,j=0;
	
	if ( DATASAPLES != BufSize)
	{LOGD("+++INFO: the BufSize must be equal to DATASAPLES!");
		return hyp;}
	if((BufSize%FRAME_SHIFT)!=0)
	{
		LOGD("+++INFO: the BufSize/FRAME_SHIFT must be equal to 0!");
		return hyp;
	}
	
	for (i=0;i<(BufSize/FRAME_SHIFT);i++)
	{	
		for(j=0;j<FRAME_SHIFT;j++){
			InBuf[j] = InBufall[i*FRAME_SHIFT+j];
		}
		logMMSE_denosie(InBuf,OutBuf,logMMSE);
		for(j=0;j<FRAME_SHIFT;j++){
			OutBufall[i*FRAME_SHIFT+j] = OutBuf[j];
		}
	}
	hyp = VoiceDetectMain(OutBufall,config,threshold,orderfilename);
	
	free(OutBuf);
	free(OutBufall);
	free(InBuf);
	return hyp;
}

int noise_estimate(X_INT16 *sigBuf, LOGMMSE_VAR *logMMSE)
{
    X_INT16 i = 0;

    X_FLOAT32 tmp_var       = 0.0;
    X_FLOAT32 vad_decision  = 0.0;


    X_FLOAT32 *Buf2denoise   = logMMSE->Buf2denoise;
    Complex   *FFTIn        = logMMSE->FFTIn;
    X_FLOAT32 *spect        = logMMSE->spect;
    X_FLOAT32 *noiseMean    = logMMSE->noiseMean;
    X_INT32 *Frame_count   = &(logMMSE->nbFrame);

    (*Frame_count) ++;


    for(i = 0; i < FRAME_LEN; i ++)
    {
        Buf2denoise[i] = sigBuf[i];
    }
    DoSigWindowing (Buf2denoise, logMMSE->sigWindow, FRAME_LEN, FFT_LEN);//add Hamming window
    for(i = 0; i < FFT_LEN; i ++)
    {
        FFTIn[i].real = Buf2denoise[i];
        FFTIn[i].imag = 0.0;
    }

    fft4(FFTIn, 4);//fft
    //fft(FFTIn,128)

    for(i = 0; i < FFT_LEN; i ++)
    {
        spect[i] = FFTIn[i].real * FFTIn[i].real + FFTIn[i].imag * FFTIn[i].imag;
    }

    if((*Frame_count) < 7)
    {
        for(i = 0; i < FFT_LEN; i ++)
        {
            noiseMean[i] += sqrt(spect[i]);
        }

       //(*Frame_count) = 0;

    }

    else
    {
        for(i = 0; i < FFT_LEN; i ++)
        {
            noiseMean[i] /= 6;
            noiseMean[i]  = noiseMean[i] * noiseMean[i];
            //printf("%f ",noiseMean[i]);
        }
       /* printf("\n");
        printf("\n");*/
        (*Frame_count) = 0;
    }


    return 0;



}

int noise_estimate_bufall(X_INT16 *InBufall,int32 BufSize, LOGMMSE_VAR *logMMSE)
{
	
	X_INT16 *InBuf;
	InBuf = (X_INT16 *)malloc(sizeof(X_INT16)*FRAME_LEN);
	
	if(FRAME_LEN*7 > BufSize)
	{
		LOGD("+++INFO: The BufSize must be longer than FRAME_LEN*7");
		return -1;
	}
	
	int i=0,j=0;
	for (i=0;i<7;i++){
		for(j=0;j<FRAME_LEN;j++){
			InBuf[j] = InBufall[j+i*FFT_LEN];
		}
		noise_estimate(InBuf,logMMSE);
	}
	
	free(InBuf);
	return 1;
}
void logMMSE_Init(LOGMMSE_VAR *logMMSEVar)
{
  X_INT16 i, j;

  logMMSEVar->SampFreq = samplRate;
  logMMSEVar->nbFrame  = 0;

  for (i=0 ; i < FFT_LEN ; i++)
    {
      logMMSEVar->Buf2denoise[i]  = 0.0;
      logMMSEVar->FFTIn[i].real  = 0.0;
      logMMSEVar->FFTIn[i].imag  = 0.0;
      logMMSEVar->spect[i]       = 0.0;
      logMMSEVar->noiseMean[i]   = 0.0;
      logMMSEVar->Xk_prev[i]     = 0.0;
      logMMSEVar->sig[i]         = 0.0;
      logMMSEVar->gammak[i]      = 0.0;
      logMMSEVar->ksi[i]         = 0.0;
      logMMSEVar->log_sigma_k[i] = 0.0;
      logMMSEVar->A[i]           = 0.0;
      logMMSEVar->vk[i]          = 0.0;
      logMMSEVar->ei_vk[i]       = 0.0;
      logMMSEVar->hw[i]          = 0.0;
    }


  for (i=0 ; i < FRAME_SHIFT ; i++)
    logMMSEVar->old_denosebuf[i] = 0.0;





  /*--------
   * ns_tmp
   *--------*/
  // Hamming window for spectrum estimation
  for (i = 0 ; i < FRAME_LEN ; i++)
    logMMSEVar->sigWindow[i] = 0.54 - 0.46 * cos ((PIx2 *  i ) / (X_FLOAT32) (FRAME_LEN));

}


/*
 * FFT Algorithm
 * === Inputs ===
 * x : complex numbers
 * N : nodes of FFT. @N should be power of 2, that is 2^(*)
 * === Output ===
 * the @x contains the result of FFT algorithm, so the original data
 * in @x is destroyed, please store them before using FFT.
 */

int fft(Complex *x, int lenforfft)
{
    int i,j,l,k,ip;
    static int M = 0;
    static int le,le2;
    static float sR,sI,tR,tI,uR,uI;

    M = (int)(log(lenforfft) / log(2));

    /*
     * bit reversal sorting
     */
    l = lenforfft / 2;
    j = l;
    //BitReverse(x,x,N,M);
    for (i=1; i<=lenforfft-2; i++) {
        if (i < j) {
            tR = x[j].real;
            tI = x[j].imag;
            x[j].real = x[i].real;
            x[j].imag = x[i].imag;
            x[i].real = tR;
            x[i].imag = tI;
        }
        k = l;
        while (k <= j) {
            j = j - k;
            k = k / 2;
        }
        j = j + k;
    }

    /*
     * For Loops
     */
    for (l=1; l<=M; l++) {   /* loop for ceil{log2(N)} */
        le = (int)pow(2,l);
        le2 = (int)(le / 2);
        uR = 1;
        uI = 0;
        sR = cos(PI / le2);
        sI = -sin(PI / le2);
        for (j=1; j<=le2; j++) {   /* loop for each sub DFT */
            //jm1 = j - 1;
            for (i=j-1; i<=lenforfft-1; i+=le) {  /* loop for each butterfly */
                ip = i + le2;
                tR = x[ip].real * uR - x[ip].imag * uI;
                tI = x[ip].real * uI + x[ip].imag * uR;
                x[ip].real = x[i].real - tR;
                x[ip].imag = x[i].imag - tI;
                x[i].real += tR;
                x[i].imag += tI;
            }  /* Next i */
            tR = uR;
            uR = tR * sR - uI * sI;
            uI = tR * sI + uI *sR;
        } /* Next j */
    } /* Next l */

    return 0;
}

/*
 * Inverse FFT Algorithm
 * === Inputs ===
 * x : complex numbers
 * N : nodes of FFT. @N should be power of 2, that is 2^(*)
 * === Output ===
 * the @x contains the result of FFT algorithm, so the original data
 * in @x is destroyed, please store them before using FFT.
 */
int ifft(Complex *x, int lenforifft)
{
    int k = 0;

    for (k=0; k<=lenforifft-1; k++) {
        x[k].imag = -x[k].imag;
    }

    fft(x, lenforifft);    /* using FFT */

    for (k=0; k<=lenforifft-1; k++) {
        x[k].real = x[k].real / lenforifft;
        x[k].imag = -x[k].imag / lenforifft;
    }

    return 0;
}



int BitReverse(int src, int size)
{
	int tmp = src;
	int des = 0;
	int i;

	for (i=size-1; i>=0; i--)
	{
		des = ((tmp & 0x3) << (i*2)) | des;
		tmp = tmp >> 2;
	}
	return des;
}

void reverse_idx(Complex *in,int log4_N)
{
	int i;
	int NN = 1 << (log4_N*2);

	Complex * temp;
	temp = malloc(NN * sizeof(Complex));
	if(!temp)
	{
		printf("malloc failed!\n");
		exit(0);
	}

	for(i = 0; i < NN;i++)
	{
		int idx;
		idx = BitReverse(i,log4_N);
		temp[idx].real = in[i].real;
		temp[idx].imag = in[i].imag;
	}

	for(i = 0; i < NN; i++)
	{
		in[i].real = temp[i].real;
		in[i].imag = temp[i].imag;
	}

	free(temp);
}

void fft_ifft_4_common(Complex *in,Complex * win,int log4_N,int reverse)
{
	int NN = (1 << log4_N * 2);
	int i,j,k;
	int span = 1;
	int n = NN >> 2;
	float wr,wi;
	int widx;
	Complex temp1,temp2,temp3,temp4;
	int idx1,idx2,idx3,idx4;
	int **cof;

	for(i = 0;i < log4_N; i++)
	{
		for(j = 0; j < n; j++)
		{
			widx = 0;

			idx1 = j * span * 4;
			idx2 = idx1 + span;
			idx3 = idx2 + span;
			idx4 = idx3 + span;
			for(k = 0; k < span; k++)
			{

				temp1.real = in[idx1 + k].real;
				temp1.imag = in[idx1 + k].imag;
				temp2.real = win[widx].real * in[idx2 + k].real - win[widx].imag * in[idx2 + k].imag;
				temp2.imag = win[widx].imag * in[idx2 + k].real + win[widx].real * in[idx2 + k].imag;
				temp3.real = win[widx * 2].real * in[idx3 + k].real -win[widx * 2].imag * in[idx3 + k].imag;
				temp3.imag = win[widx * 2].imag * in[idx3 + k].real + win[widx * 2].real * in[idx3 + k].imag;
				temp4.real = win[widx * 3].real * in[idx4 + k].real -win[widx * 3].imag * in[idx4 + k].imag;
				temp4.imag = win[widx * 3].imag * in[idx4 + k].real + win[widx * 3].real * in[idx4 + k].imag;

				in[idx1 + k].real = temp1.real + temp3.real;
				in[idx1 + k].imag = temp1.imag + temp3.imag;
				in[idx2 + k].real = temp1.real - temp3.real;
				in[idx2 + k].imag = temp1.imag - temp3.imag;
				in[idx3 + k].real = temp2.real + temp4.real;
				in[idx3 + k].imag = temp2.imag + temp4.imag;
				in[idx4 + k].real = temp2.real - temp4.real;
				in[idx4 + k].imag = temp2.imag - temp4.imag;

				temp1.real = in[idx1 + k].real + in[idx3 + k].real;
				temp1.imag = in[idx1 + k].imag + in[idx3 + k].imag;
				if(reverse == 0)
				{
					temp2.real = in[idx2 + k].real + in[idx4 + k].imag;
					temp2.imag = in[idx2 + k].imag - in[idx4 + k].real;
				}
				else
				{
					temp2.real = in[idx2 + k].real - in[idx4 + k].imag;
					temp2.imag = in[idx2 + k].imag + in[idx4 + k].real;
				}
				temp3.real = in[idx1  +k].real - in[idx3 + k].real;
				temp3.imag = in[idx1 + k].imag - in[idx3 + k].imag;

				if(reverse == 0)
				{
					temp4.real = in[idx2 + k].real - in[idx4 + k].imag;
					temp4.imag = in[idx2 + k].imag + in[idx4 + k].real;
				}
				else
				{
					temp4.real = in[idx2 + k].real + in[idx4 + k].imag;
					temp4.imag = in[idx2 + k].imag - in[idx4 + k].real;
				}

				in[idx1 + k].real = temp1.real;
				in[idx1 + k].imag = temp1.imag;
				in[idx2 + k].real = temp2.real;
				in[idx2 + k].imag = temp2.imag;
				in[idx3 + k].real = temp3.real;
				in[idx3 + k].imag = temp3.imag;
				in[idx4 + k].real = temp4.real;
				in[idx4 + k].imag = temp4.imag;

				widx += n;
			}
		}
		n >>= 2;
		span <<= 2;
	}
}

void fft4(Complex *in,int log4_N)
{
	Complex *win;
	int NN = 1 << (log4_N*2);
	int i;

	win = malloc((3*NN/4 - 2) * sizeof(Complex));
	if(!win)
	{
		printf("malloc failed!\n");
		exit(0);
	}

	reverse_idx(in,log4_N);

	for(i = 0; i < (3*NN/4-2); i++)
	{
		win[i].real = cos(2*pi*i/(float)NN);
		win[i].imag = -sin(2*pi*i/(float)NN);
	}

	fft_ifft_4_common(in,win,log4_N,0);

	free(win);
}

void ifft4(Complex *in,int log4_N)
{
	int NN = 1 << (log4_N * 2);
	Complex *win;
	int i;

	win = malloc((3*NN/4 - 2) * sizeof(Complex));
	if(!win)
	{
		printf("malloc failed!\n");
		exit(0);
	}

	reverse_idx(in,log4_N);

	for(i = 0; i < (3*NN/4-2); i++)
	{
		win[i].real = cos(2*pi*i/(float)NN);
		win[i].imag = sin(2*pi*i/(float)NN);
	}

	fft_ifft_4_common(in,win,log4_N,1);

	for(i = 0; i < NN; i++)
	{
		in[i].real /= (float)NN;
		in[i].imag /= (float)NN;
	}

	free(win);
}

