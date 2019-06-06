/*
 * Elite - The New Kind.
 *
 * Reverse engineered from the BBC disk version of Elite.
 * Additional material by C.J.Pinder.
 *
 * The original Elite code is (C) I.Bell & D.Braben 1984.
 * This version re-engineered in C by C.J.Pinder 1999-2001.
 *
 * email: <christian@newkind.co.uk>
 *
 *
 */

/*
 * sound.c
 */

#include "etnk.h"

#include <stdlib.h>
#include "sound.h"
#include "alg_data.h" 
#include "sdl.h"

#define NUM_SAMPLES 14 

//extern DATAFILE *datafile;

static int sound_on;

#if 0
// FIXME
#define SAMPLE void

struct sound_sample
{
	Uint8 *sample;
	char filename[256];
	int runtime;
	int timeleft;
};

struct sound_sample sample_list[NUM_SAMPLES] =
{
	{NULL, "launch.wav",    32, 0},
	{NULL, "crash.wav",      7, 0},
	{NULL, "dock.wav",      36, 0},
	{NULL, "gameover.wav",  24, 0},
	{NULL, "pulse.wav",      4, 0},
	{NULL, "hitem.wav",		 4, 0},
	{NULL, "explode.wav",	23, 0},
	{NULL, "ecm.wav",		23, 0},
	{NULL, "missile.wav",	25, 0},
	{NULL, "hyper.wav",	    37, 0},
	{NULL, "incom1.wav",	 4, 0},
	{NULL, "incom2.wav",	 5, 0},
	{NULL, "beep.wav",		 2, 0},
	{NULL, "boop.wav",		 7, 0},
};
#endif

static const char *sample_filenames[NUM_SAMPLES] = {
	"launch.wav", "crash.wav", "dock.wav", "gameover.wav", "pulse.wav", "hitem.wav", "explode.wav", "ecm.wav", "missile.wav", "hyper.wav", "incom1.wav", "incom2.wav", "beep.wav", "boop.wav"
};
static const Uint8 *sample_p[NUM_SAMPLES];
static int    sample_s[NUM_SAMPLES];


static SDL_AudioDeviceID audio = 0;


static const Uint8 *playing_pos = NULL;
static const Uint8 *playing_end = NULL;


static void audio_callback ( void *userdata, Uint16 *stream, int len )
{
	for (int i = 0; i < len/2; i++) {
		if (playing_pos) {
			stream[i] = *(Sint16*)playing_pos;
			playing_pos+=2;
			if (playing_pos >= playing_end) {
				playing_pos = NULL;
				puts("AUDIO: end of sample");
			}
		} else {
			stream[i] = 0;
		}
	}
}



void snd_sound_startup (void)
{
	for (int i = 0; i < NUM_SAMPLES; i++)
		datafile_select(sample_filenames[i], &sample_p[i], &sample_s[i]);
	SDL_AudioSpec audio_want, audio_got;
	SDL_memset(&audio_want, 0, sizeof(audio_want));
	audio_want.freq = 44100;
	audio_want.format = AUDIO_S16SYS;
	audio_want.channels = 1;
	audio_want.samples = 1024;
	audio_want.callback = audio_callback;
	audio_want.userdata = NULL;
	audio = SDL_OpenAudioDevice(NULL, 0, &audio_want, &audio_got, 0);
	if (audio) {
		if (audio_want.freq != audio_got.freq || audio_want.format != audio_got.format || audio_want.channels != audio_got.channels) {
			SDL_CloseAudioDevice(audio);    // forget audio, if it's not our expected format :(
			audio = 0;
			fprintf(stderr, "Audio parameter mismatches\n");
		} else {
			printf("AUDIO: initialized (#%d), %d Hz, %d channels, %d buffer sample size.\n", audio, audio_got.freq, audio_got.channels, audio_got.samples);
			playing_pos = NULL;
			SDL_PauseAudioDevice(audio, 0);
		}
	} else
		fprintf(stderr, "Cannot open audio: %s\n", SDL_GetError());


#if 0
	int i;

 	/* Install a sound driver.. */
	sound_on = 1;
	
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, ".") != 0)
	{
		sound_on = 0;
		return;
	}

	/* Load the sound samples... */

	for (i = 0; i < NUM_SAMPLES; i++)
	{
		sample_list[i].sample = load_sample(sample_list[i].filename);
	}
#endif
}
 

void snd_sound_shutdown (void)
{
	if (audio) {
		puts("AUDIO: closing");
		SDL_PauseAudioDevice(audio, 1);
		SDL_CloseAudioDevice(audio);
	}
#if 0
	int i;

	if (!sound_on)
		return;

	for (i = 0; i < NUM_SAMPLES; i++)
	{
		if (sample_list[i].sample != NULL)
		{
			destroy_sample (sample_list[i].sample);
			sample_list[i].sample = NULL;
		}
	}
#endif
}


void snd_play_sample (int sample_no)
{
	puts("FIXME: snd_play_sample() not implemented");
	if (audio == 0 || sample_no >= NUM_SAMPLES) {
		return;
	}
	//playing_sample = sample_no;
	playing_pos = sample_p[sample_no] + 44;	// really lame, we use WAVs as is, without even checking header or anything and assuming that it will work. wow. :-O
	playing_end = sample_p[sample_no] + sample_s[sample_no] - 44;
	//SDL_PauseAudioDevice(audio, 0);
#if 0
	if (!sound_on)
		return;

	if (sample_list[sample_no].timeleft != 0)
		return;

	sample_list[sample_no].timeleft = sample_list[sample_no].runtime;
		
	play_sample (sample_list[sample_no].sample, 255, 128, 1000, FALSE);
#endif
}


void snd_update_sound (void)
{
#if 0
	int i;
	
	for (i = 0; i < NUM_SAMPLES; i++)
	{
		if (sample_list[i].timeleft > 0)
			sample_list[i].timeleft--;
	}
#endif
}


void snd_play_midi (int midi_no, int repeat)
{
	puts("FIXME: snd_play_midi() not implemented");
#if 0
	if (!sound_on)
		return;
	
	switch (midi_no)
	{
		case SND_ELITE_THEME:
			play_midi (datafile[THEME].dat, repeat);
			break;
		
		case SND_BLUE_DANUBE:
			play_midi (datafile[DANUBE].dat, repeat);
			break;
	}
#endif
}


void snd_stop_midi (void)
{
	puts("FIXME: snd_stop_midi() not implemented");
#if 0
	if (sound_on)
		play_midi (NULL, TRUE);
#endif
}
