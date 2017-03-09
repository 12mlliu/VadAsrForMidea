#include "pocketsphinx.h"
#define true 1
#define false 0
/*logd*/
#include <android/log.h>
#define LOG_TAG "asr.c"
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)
char const *ps_decoder_test(cmd_ln_t *config, int16 *data,long total,int32 threshold,char const *orderfilename);
void free_keyphrases(glist_t keyphrases);
int32 ps_seg_threshold_getscore(ps_decoder_t *ps,char const *hyp);
char const *ps_seg_threshold(ps_decoder_t *ps,int32 threshold,char const *orderfilename);
