#include "driver.h"
#include "pg.h"
#include "syscall.h"

//unsigned char *sound_buf;
int pga_handle[1];

int nominal_sample_rate;
int soundcard,usestereo;
int attenuation = 0;
int sampleratedetect = 1;
static int master_volume = 256;

static int stream_playing;
static INT16 *stream_cache_data;
static int stream_cache_len;
static int stream_cache_stereo;

#define NUM_BUFFERS 3	/* raising this number should improve performance with frameskip, */
						/* but also increases the latency. */

static int voice_pos;
static int audio_buffer_length;

/* global sample tracking */
static double samples_per_frame;
static double samples_left_over;
static UINT32 samples_this_frame;


#define SND1_MAXSLOT 16

typedef struct {
	unsigned long channels;
	unsigned long samplerate;
	unsigned long samplecount;
	unsigned long datalength;
	char *wavdata;
	unsigned long rateratio;		// samplerate / 44100 * 0x10000
	unsigned long playptr;
	unsigned long playptr_frac;
	int playloop;
} wavout_wavinfo_t;

wavout_wavinfo_t wavinfo_bg;
wavout_wavinfo_t *wavout_snd0_wavinfo=0;
int wavout_snd0_ready=0;
int wavout_snd0_playend=0;
unsigned long wavout_snd0_playptr=0;
int wavout_snd1_playing[SND1_MAXSLOT];
unsigned long cur_play;
unsigned long cur_nloop;
int wavout_enable=0;

//サウンドバッファ１バンクあたりの容量。４バンクで適当にラウンドロビン
//PGA_SAMPLESの倍数にすること。PGA_SAMPLESと同じだと多分ダメなので注意。 - LCK
#define SOUND_BANKLEN 2048

short sound_buf[SOUND_BANKLEN*4*2];

//44100,chan:2固定
static void wavout_snd0_callback(short *buf, unsigned long reqn)
{
	if (!wavout_enable) {
		memset(buf, 0, reqn*4);
		return;
	}

	unsigned int ptr=cur_play;
	unsigned int nextptr=ptr+reqn;
	if (nextptr>=SOUND_BANKLEN*4) nextptr=0;
	__memcpy4a((unsigned long *)buf, (unsigned long *)&sound_buf[ptr*2], reqn);
//	__memcpy4((unsigned long *)buf, (unsigned long *)&sound_buf[ptr*2], reqn);
	cur_play=nextptr;
}

static void __wavout_snd0_callback(short *_buf, unsigned long _reqn)
{
	static int power[128];
	
	unsigned long i;
	unsigned long ptr,frac,rr,max;
	int channels;
	char *src;
	short *buf=_buf;
	unsigned long reqn=_reqn;
	
	wavout_wavinfo_t *wi=wavout_snd0_wavinfo;

	if (wi==0) {
		wavout_snd0_ready=1;
		memset(buf,0,reqn*4);
		return;
	}
	
	wavout_snd0_ready=0;
	
	ptr=wi->playptr;
	frac=wi->playptr_frac;
	rr=wi->rateratio;
	max=wi->samplecount;
	channels=wi->channels;
	src=wi->wavdata;
	
	cur_nloop=0;
	for (; reqn>0; --reqn) {
		frac+=rr;
		ptr+=(frac>>16);
		cur_play = ptr*4;
		frac&=0xffff;
		if (ptr>=max) {
			if (wi->playloop) {
				ptr=0;
				cur_nloop++;
			} else {
				for (; reqn>0; --reqn) {
					*(buf++)=0;
					*(buf++)=0;
				}
				goto playend;
			}
		}
		if (channels==1) {
			buf[0]=buf[1]=*(short *)(src+ptr*2);
			buf+=2;
		} else {
			buf[0]=*(short *)(src+ptr*4);
			buf[1]=*(short *)(src+ptr*4+2);
			buf+=2;
		}
	}

	//powercalc(_buf);	//単にwaveを出すだけなら不要

	wavout_snd0_playptr=ptr;
	wi->playptr=ptr;
	wi->playptr_frac=frac;
	return;
	
playend:
	wavout_snd0_playend=1;
	return;
}

//return 0 if success
int wavoutInit()
{
	int i;
	
	wavout_enable =0;
	wavout_snd0_wavinfo=0;
	
	for (i=0; i<SND1_MAXSLOT; i++) {
		wavout_snd1_playing[i]=0;
	}

	pgaSetChannelCallback(0,wavout_snd0_callback);
	//pgaSetChannelCallback(1,wavout_snd1_callback);
	return 0;
}

void wavoutStopPlay0()
{
	if (wavout_snd0_wavinfo!=0) {
		while (wavout_snd0_ready) pgWaitV();
		wavout_snd0_wavinfo=0;
		while (!wavout_snd0_ready) pgWaitV();
	}
}

void wavoutStartPlay0(wavout_wavinfo_t *wi)
{
	wavoutStopPlay0();
	while (!wavout_snd0_ready) pgWaitV();
	wavout_snd0_playptr=0;
	wavout_snd0_playend=0;
	wavout_snd0_wavinfo=wi;
	while (wavout_snd0_ready) pgWaitV();
}

int wavoutWaitEnd0()
{
	if (wavout_snd0_wavinfo==0) return -1;
	if (wavout_snd0_wavinfo->playloop) return -1;
	while (!wavout_snd0_playend) pgWaitV();
	return 0;
}


int msdos_init_sound(void)
{
	int i;

	stream_playing = 0;
	stream_cache_data = 0;
	stream_cache_len = 0;
	stream_cache_stereo = 0;

	/* initialize SEAL audio library */
	if( soundcard == 0 || Machine->sample_rate == 0 )
	{
		return 0;
	}

	wavoutInit();
	wavout_enable =1;

	nominal_sample_rate = Machine->sample_rate;

	osd_set_mastervolume(attenuation);	/* set the startup volume */

	return 0;
}


void msdos_shutdown_sound(void)
{
	if( soundcard == 0 || Machine->sample_rate == 0 )
	{
		return;
	}

	wavout_snd0_wavinfo =0x00;
	wavout_enable =0;

}


int osd_start_audio_stream(int stereo)
{
	if( stereo != 0 )
	{
		/* make sure it's either 0 or 1 */
		stereo = 1;
	}

	stream_cache_stereo = stereo;

	/* determine the number of samples per frame */
	samples_per_frame = (double)Machine->sample_rate / (double)Machine->refresh_rate;

	/* compute how many samples to generate this frame */
	samples_left_over = samples_per_frame;
	samples_this_frame = (UINT32)samples_left_over;
	samples_left_over -= (double)samples_this_frame;

	audio_buffer_length = NUM_BUFFERS * samples_per_frame + 20;

	if( Machine->sample_rate == 0 )
	{
		return 0;
	}

//	if (0 <=(pga_handle[0] =sceAudioChReserve(-1,(int)samples_per_frame, 0)))
//		return 0;
//		sceAudioChRelease(pga_handle[0]);

//	if (0x00 ==(sound_buf =malloc(audio_buffer_length *2 *2))) // 16bit,streo
//		return 0;
//	memset(sound_buf, 0 ,audio_buffer_length *2 *2);
	memset(sound_buf, 0 ,sizeof(sound_buf));

	wavinfo_bg.channels =stream_cache_stereo+1;
	wavinfo_bg.samplerate =Machine->sample_rate;
	wavinfo_bg.samplecount=samples_this_frame;
	wavinfo_bg.datalength=sizeof(audio_buffer_length*2 *2);
	wavinfo_bg.wavdata=sound_buf;
	wavinfo_bg.rateratio=((wavinfo_bg.samplerate *0x4000)/11025);
	wavinfo_bg.playptr=0;
	wavinfo_bg.playptr_frac=0;
	wavinfo_bg.playloop=1;

	wavout_snd0_wavinfo=&wavinfo_bg;
	wavout_enable =1;

//	char buftmk[20];
//	sprintf(buftmk, "samples_per_frame[%i]", (int)samples_per_frame);
//	printf_(buftmk);

	stream_playing = 1;
	voice_pos = 0;

	osd_sound_enable( 1 );

	return samples_this_frame;
}

//============================================================
//	sound_update_refresh_rate
//============================================================

void sound_update_refresh_rate(float newrate)
{
	samples_per_frame = (double)Machine->sample_rate / (double)Machine->refresh_rate;
}



void osd_stop_audio_stream(void)
{
	if( soundcard == 0 || Machine->sample_rate == 0 )
	{
		return;
	}

	osd_sound_enable( 0 );

	wavout_snd0_wavinfo =0x00;
	wavout_enable =0;

//	if (0x00 !=sound_buf)
//		free(sound_buf);

//	if (pga_handle[0]!=-1) {
//		sceAudioChRelease(pga_handle[0]);
//		pga_handle[0]=-1;
//	}

	stream_playing = 0;
}

static void updateaudiostream( int throttle )
{
	INT16 *data = stream_cache_data;
	int stereo = stream_cache_stereo;
	int len = stream_cache_len;
//	int buflen;
//	int start,end;
//	INT16 *odata =sound_buf;

	if (!stream_playing)
	{
		/* error */
		return;
	}

//	buflen = audio_buffer_length;
//	start = voice_pos;
//	end = voice_pos + len;
//	if (end > buflen)
//	{
//		end -= buflen;
//	}

//	memcpy(sound_buf, data, len *2 *(stereo+1));
//	__memcpy4a((unsigned long *)odata, (unsigned long *)data, (len /2 *(stereo+1)));

//	wavinfo_bg.playptr=0;				// ポインタをリセット
//	wavinfo_bg.playptr_frac=0;

//	sceAudioOutputPannedBlocking(pga_handle[0], 0x8000, 0x8000, &sound_buf[start*4]);

//	pgcLocate(0,1);
//	pgcPuthex8(start*4);

//	int sound_buf_len = (1024 + 1024 * 0) ;
//	static unsigned int nextbank=1;
//	unsigned int playbank=cur_play/sound_buf_len;
//	if (nextbank!=playbank) {
////		snd_render(&sound_buf[nextbank*sound_buf_len*2],sound_buf_len);
//		if (stereo)
//			__memcpy4a((unsigned long *)&sound_buf[nextbank*sound_buf_len*2], (unsigned long *)data,
//				len);
//		else
//		{
//			INT16 *odata =&sound_buf[nextbank*sound_buf_len*2];
//			for(int i=0;i<len;i++)
//				odata[i*2] =odata[i*2+1] =data[i];
//		}
//		nextbank++;
//		if( (sound_buf_len * (nextbank+1)) > (SOUND_BANKLEN*4) ){ nextbank = 0; }
//	}

	static int cur_write=0;
	if (cur_write>=SOUND_BANKLEN*4) cur_write=0;
	if (cur_play !=cur_write) {
		if (stereo)
			__memcpy4a((unsigned long *)&sound_buf[cur_write*2], (unsigned long *)data, len);
		else
		{
			INT16 *odata =&sound_buf[cur_write*2];
			for(int i=0;i<len;i++)
				odata[i*2] =odata[i*2+1] =data[i];
		}
		cur_write +=len;
	}

//	voice_pos = end;
//	if (voice_pos == buflen)
//	{
//		voice_pos = 0;
//	}
}


int osd_update_audio_stream(INT16 *buffer)
{
	stream_cache_data = buffer;
	stream_cache_len = samples_this_frame;

	/* compute how many samples to generate next frame */
	samples_left_over += samples_per_frame;
	samples_this_frame = (UINT32)samples_left_over;
	samples_left_over -= (double)samples_this_frame;

	return samples_this_frame;
}


int msdos_update_audio( int throttle )
{
	if( soundcard == 0 || Machine->sample_rate == 0 || stream_cache_data == 0 )
	{
		return 0;
	}

	profiler_mark(PROFILER_MIXER);

	updateaudiostream( throttle );

	profiler_mark(PROFILER_END);

	return 1;
}


/* attenuation in dB */
void osd_set_mastervolume(int _attenuation)
{
	float volume;

	if (_attenuation > 0)
	{
		_attenuation = 0;
	}
	if (_attenuation < -32)
	{
		_attenuation = -32;
	}

	attenuation = _attenuation;

 	volume = 256.0;	/* range is 0-256 */
	while (_attenuation++ < 0)
	{
		volume /= 1.122018454;	/* = (10 ^ (1/20)) = 1dB */
	}

	master_volume = volume;

#ifdef USE_SEAL
	ASetAudioMixerValue(AUDIO_MIXER_MASTER_VOLUME,master_volume);
#endif
}


int osd_get_mastervolume(void)
{
	return attenuation;
}


void osd_sound_enable(int enable_it)
{
	if( soundcard == 0 || Machine->sample_rate == 0 )
		return;

	if (enable_it)
	{
//		ASetAudioMixerValue(AUDIO_MIXER_MASTER_VOLUME,master_volume);
		wavout_snd0_wavinfo=&wavinfo_bg;
		wavout_enable =1;
	}
	else
	{
//		ASetAudioMixerValue(AUDIO_MIXER_MASTER_VOLUME,0);
		wavout_snd0_wavinfo =0x00;
		wavout_enable =0;
	}
}
