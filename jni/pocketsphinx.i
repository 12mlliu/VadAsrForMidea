/*pocketsphonx.i by meili
*2017/01/05
*part of original pocketsphinx.i
*/

#if SWIGJAVA
%module PocketSphinx
#endif

/*not sure, maybe can automatically generated some file? .java .class*/
%feature("autodoc","1");

/*question1: look typemaps.i and iterators.i and sphinxbase.i*/
%include typemaps.i
%include iterators.i
%import sphinxbase.i
/*the two typedef for Config and Decoder can be merge as one ? try*/
%{
#ifndef __cplusplus
typedef int bool;
#define true 1
#define false 0
#endif


#include "logMMSE.h"
typedef LOGMMSE_VAR  LogmmseVar;

typedef cmd_ln_t Config;


%}

typedef struct {} LogmmseVar;

%extend LogmmseVar {

    LogmmseVar(){
        LogmmseVar *logmmse;
        logmmse = (LogmmseVar *)malloc(sizeof(LogmmseVar));
        return logmmse;
    }
    ~LogmmseVar() {
        free($self);
    }

    void logmmseinit() {
        logMMSE_Init($self);        
    }
    char const* logmmsedenosebufall(X_INT16 *sigBuf,int32 BufSize,Config *config,int32 threshold,char const *orderfilename){
        char const *hypstr;
        hypstr = logMMSE_denosie_bufall(sigBuf,BufSize,$self,config,threshold,orderfilename);   
        return hypstr;
    }    
    int noiseestimatebufall(X_INT16 *sigBuf,int32 BufSize){
        return noise_estimate_bufall(sigBuf, BufSize,$self);
    }
}
