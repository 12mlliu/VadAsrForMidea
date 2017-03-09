#include "asr.h"
char const *ps_decoder_test(cmd_ln_t *config, int16 *data,long total,int32 threshold,char const *orderfilename)
{
    LOGD("++++INFO: step4-1 ps_decoder_test begin");
    ps_decoder_t *ps;
    char const *hyp;

    ps = ps_init(config);
    ps_start_utt(ps);
    //Test it first with pocketsphinx_decode_raw()

    ps_process_raw(ps, data, total, false, true);
    ps_end_utt(ps);

    //hyp = ps_get_hyp(ps, &score);
    hyp = ps_seg_threshold(ps,threshold,orderfilename);
    ps_free(ps);//should ps_free ps maybe.......when decoder ,use ps_free ,so yes.
    LOGD("++++INFO: step4-1 ps_decoder_test begin");
    return hyp;
}
void free_keyphrases(glist_t keyphrases)
{
        gnode_t *gn;
        for (gn = keyphrases; gn; gn = gnode_next(gn)) {
                char * order = gnode_ptr(gn);
                ckd_free(order);
        }

       // glist_free(keyphrases);
}

char const *
ps_seg_threshold(ps_decoder_t *ps,int32 threshold,char const *orderfilename)
{
    LOGD("++++INFO: step5-1 ps_seg_threshold begin");
    //read the order.txt
    glist_t keyphrases;
    FILE *list_file;
    lineiter_t *li;
    char *line;
    int countall=0;
    if((list_file = fopen(orderfilename,"r"))==NULL){
        printf("failed to open file");
	LOGD("++++INFO: step5-2 ps_seg_threshold end");
        return NULL;
    }
    for(li= lineiter_start_clean(list_file);li;li = lineiter_next(li)){
	countall++;
        if(li->len ==0)
             continue;
        line = li->buf;
        keyphrases = glist_add_ptr(keyphrases,ckd_salloc(line));
    }
    fclose(list_file);
    //read order.txt done

    //threshold
    ps_seg_t *iter = ps_seg_iter(ps);
    char const * hyp=NULL;
    int match_num = 0;
    while (iter != NULL)
    {
        int32 sf, ef, pprob;
        float conf;
        gnode_t *gn;
	int count =0;
        for (gn = keyphrases; gn; gn = gnode_next(gn)) {
		count++;
		if(count > countall){break;}
                char * order = gnode_ptr(gn);
                if (!strcmp(order,ps_seg_word (iter))){
			match_num++;
			if (match_num >1){
				//free_keyphrases(keyphrases);
				//glist_free(keyphrases);
				LOGD("++++INFO: step5-2 ps_seg_threshold end");
				return NULL;}
                        ps_seg_frames (iter, &sf, &ef);
                        pprob = ps_seg_prob (iter, NULL, NULL, NULL);
                        conf = logmath_exp(ps_get_logmath(ps), pprob);
                                if(conf*100 > threshold)
				{hyp = ps_seg_word(iter);}
                        }

        }
        iter = ps_seg_next (iter);
    }
    //free_keyphrases(keyphrases);
    LOGD("++++INFO: step5-2 ps_seg_threshold end");
    return hyp;
}

int32 ps_seg_threshold_getscore(ps_decoder_t *ps,char const *hyp)
{
    LOGD("++++INFO: step6-1 getscore begin");
    //threshold
    //if(!(strcmp(hyp,""))){return 0;}
    if(hyp==NULL){return 0;}
    int32 score =0;
    ps_seg_t *iter = ps_seg_iter(ps);
    while (iter != NULL)
    {
        int32 sf, ef, pprob;
        float conf;
        if (!strcmp(hyp,ps_seg_word (iter))){
                ps_seg_frames (iter, &sf, &ef);
                pprob = ps_seg_prob (iter, NULL, NULL, NULL);
                conf = logmath_exp(ps_get_logmath(ps), pprob);
                score= (int) (conf*100);
                        }

        iter = ps_seg_next (iter);
    }
        LOGD("++++INFO: step6-2 getscore end");
        return score;
}
